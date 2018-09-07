#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include "evolucion_diferencial.h"

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

s_ind_ed * genera_ind_ed(int dim, int numG, int numH) {
  s_ind_ed *ind = malloc(sizeof(s_ind_ed));

  ind->ind = malloc(sizeof(double)*dim);
  ind->dim = dim;
  ind->eval = DBL_MAX;

  ind->numG = numG;
  ind->numH = numH;

  ind->evalG = numG > 0 ? malloc(sizeof(double)*numG) : NULL;
  ind->evalH = numH > 0 ? malloc(sizeof(double)*numH) : NULL;

  ind->sumResG = 0;
  ind->sumResH = 0;

  return ind; 
}

s_ind_ed * genera_ind_ed_rand(int dim, int numG, int numH, double *ini, double *fin) {
  s_ind_ed *ind = genera_ind_ed(dim, numG, numH);

  for(int i =0; i < dim; i++ ) {
    ind->ind[i] = ini[i] + (((double) rand())/RAND_MAX)*(fin[i]-ini[i]);

    ind->ind[i] = ind->ind[i] < ini[i] ? ini[i] : ind->ind[i];
    ind->ind[i] = ind->ind[i] > fin[i] ? fin[i] : ind->ind[i];
  }

  return ind;
}

void libera_individuo_ed(s_ind_ed *ind) {
  free(ind->ind);

  if (ind->numG > 0) free(ind->evalG);
  if (ind->numH > 0) free(ind->evalH);

  free(ind);
}

void imprime_individuo_ed(s_ind_ed *ind) {
  printf("#[ " );

  for(int i=0; i < ind->dim; i++) {
    printf("%g, ", ind->ind[i]);
  }

  printf("]\n");

  printf("#f: %g\n", ind->eval);

  if (ind->numG > 0) {
    for(int i=0; i < ind->numG; i++) {
      printf("#\tg%d:%g \n", i+1, ind->evalG[i] );
    }
    printf("#Sum Total g: %g \n", ind->sumResG);
  }

  if (ind->numH > 0) {
    for(int i=0; i < ind->numH; i++) {
      printf("#\th%d:%g \n", i+1, ind->evalH[i] );
    }
    printf("#Sum Total h: %g \n", ind->sumResH);
  }

  printf("#Suma total Violacion: %g \n", ind->sumResG + ind->sumResH );
  
}

s_ind_ed ** genera_poblacion_inicial(int tamPob, int dim, int numG, int numH,
  double *ini, double *fin) {

  s_ind_ed **pob = malloc(sizeof(s_ind_ed *)*tamPob);

  for(int i =0; i < tamPob; i++) {
    pob[i] = genera_ind_ed_rand(dim, numG, numH, ini, fin);
  }

  return pob;
}

void libera_poblacion_ed(s_ind_ed **pob, int tamPob) {

  for(int i =0; i < tamPob; i++) {
    libera_individuo_ed(pob[i]);
  }

  free(pob);
}

int es_factible(s_ind_ed *ind) {
  return ( ind->numG == 0 || ind->sumResG == 0) 
    && ( ind->numH == 0 || ind->sumResH == 0);
}

/* Torneo de Factibilidad */
int compara_individuos(const void * a, const void * b) {

  s_ind_ed *ind1 = *((s_ind_ed **) a);
  s_ind_ed *ind2 = *((s_ind_ed **) b);

  int res = 0;

  if (es_factible(ind1) && es_factible(ind2)) {
    res = ind1->eval < ind2->eval ? -1 : 1;
    res = ind1->eval == ind2->eval ? 0 : res;
  } else if (es_factible(ind1)) {
    res = -1;
  } else if (es_factible(ind2)) {
    res = 1;
  } else {
    res = ind1->sumResG+ind1->sumResH < (ind2->sumResG+ind2->sumResH) ? -1 : 1;
    res = ind1->sumResG+ind1->sumResH == (ind2->sumResG+ind2->sumResH) ? 0 : res;
  }

  return res;
}

void copiar_individuo(s_ind_ed *src, s_ind_ed *dst) {
  dst->dim = src->dim;
  dst->eval = src->eval;
  for(int i=0; i < src->dim; i++) {
    dst->ind[i] = src->ind[i];
  }

  dst->numG = src->numG;
  dst->sumResG = src->sumResG;
  for(int i=0; i < src->numG; i++) {
    dst->evalG[i] = src->evalG[i];
  }
  dst->numH = src->numH;
  dst->sumResH = src->sumResH;
  for(int i=0; i < src->numH; i++ ) {
    dst->evalH[i] = src->evalH[i];
  }
}

void evalua_individuo(s_ind_ed *ind, ApFunObj f, ApFunRes g, ApFunRes h, 
  double epsilon, int actualizarEval) {

  if (actualizarEval) {
    ind->sumResG = 0.0;
    // evaluar funcion objetivo
    ind->eval = f(ind->ind, ind->dim);

    // evaluar restricciones
    if (ind->numG > 0) g(ind->ind, ind->dim, ind->evalG, ind->numG);
    if (ind->numH > 0) h(ind->ind, ind->dim, ind->evalH, ind->numH);

    for (int i =0; i < ind->numG; i++) {
      ind->sumResG += ind->evalG[i] <= 0 ? 0 : ind->evalG[i];
    }
  }

  ind->sumResH = 0.0;
  for(int i=0; i < ind->numH; i++) {
    ind->sumResH +=  fabs(ind->evalH[i]) <= epsilon ? 0 : fabs(ind->evalH[i]) - epsilon ;
  }

}

s_resultado_ed evolucion_diferencial(int tamPob, int dim, int numG, int numH,
  double CR, double F, double epsilonIni, double p,
  int maxEval, double *ini, double *fin, 
  ApFunObj fObj, ApFunRes g, ApFunRes h, gsl_rng *r) {

  int i;
/*  double x = 0, y = 0, dx, dy;

  printf("%g %g\n", x, y);

  for (i = 0; i < 10; i++)
    {
      gsl_ran_dir_2d (r, &dx, &dy);
      x += dx; y += dy; 
      printf("%g %g\n", x, y);
    }*/

  // Paso 1: Generar poblacion inicial:
  s_ind_ed **pob = genera_poblacion_inicial(tamPob, dim, numG, numH, ini, fin);

  s_ind_ed **hijos = genera_poblacion_inicial(tamPob, dim, numG, numH, ini, fin);

  s_ind_ed **tmpPob;

  int genBest = 0;

  int indBest = 0;
  double evalBest = DBL_MAX;
//  s_ind_ed *best = NULL;

  double epsilon = epsilonIni;

  int totalFactibles = 0;

//  best = pob[0];

  // Paso 2: Evaluar poblacion inicial:
  for(int i =0; i < tamPob; i++) {
    evalua_individuo(pob[i], fObj, g, h, epsilon, 1);
    if (es_factible(pob[i])) totalFactibles++;
    if (compara_individuos(&pob[i], &pob[indBest]) < 0) indBest = i;
  }

  //printf("#Num Fatibles inicial: %d \n", totalFactibles );

  int numIt = 0;
  int numEval = tamPob;

  int pBest = (int)(tamPob*p);
  pBest = pBest < 1 ? 2 : pBest;

  int r1=0;
  int r2=0;
  int r3=0;

  int jrand=0;
  double auxRand = 0;

  s_ind_ed *nuevo = genera_ind_ed(dim, numG, numH);
  double *tmpInd;

  int genFac = 0;

  while (numEval < maxEval) {

    qsort(pob, tamPob, sizeof(s_ind_ed *), compara_individuos);

    totalFactibles = 0;
    for(int i =0; i < tamPob && numEval < maxEval; i++) {

      indBest = 0;

      // generamos tres posiciones aleatorias
      r1 = rand() % tamPob;
      while (r1 == i) {
        r1 = rand() % tamPob;
      }

      r2 = rand() % tamPob;
      while (r2 == i || r2 == r1) {
        r2 = rand() % tamPob;
      }

      r3 = rand() % pBest;
      while (r3 == i || r3 == r1 || r3 == r2) {
        r3 = rand() % pBest;
      }

      jrand = rand() % dim;

      for(int j=0; j < dim; j++) {
        auxRand = ((double)rand())/RAND_MAX;
        if (auxRand <= CR || j==jrand) {
          nuevo->ind[j] = pob[i]->ind[j] 
            + F*(pob[r3]->ind[j]-pob[i]->ind[j])
            + F*(pob[r1]->ind[j] - pob[r2]->ind[j] );
        } else {
          nuevo->ind[j] = pob[i]->ind[j];
        }

        nuevo->ind[j] = nuevo->ind[j] < ini[j] ? ini[j] : nuevo->ind[j];
        nuevo->ind[j] = nuevo->ind[j] > fin[j] ? fin[j] : nuevo->ind[j];

      }
      // Evaluamos al nuevo individuo:
      evalua_individuo(nuevo, fObj, g, h, epsilon, 1);
      numEval++;

      tmpInd = hijos[i]->ind;

      if (compara_individuos(&nuevo, &pob[i]) < 0) {
        copiar_individuo(nuevo, hijos[i]);

        if (compara_individuos(&nuevo, &pob[indBest]) < 0) {
          genBest = numIt;
        }

      } else {
        copiar_individuo(pob[i], hijos[i]);
      }
      if (es_factible(hijos[i])) totalFactibles++;
    }

    // Reemplazar a toda la poblacion;
    tmpPob = pob;
    pob = hijos;
    hijos = tmpPob;

    if (totalFactibles > (tamPob*0.10)) {
      genFac++;

      //if (genFac > tamPob*0.1) {
        genFac = 0;
        epsilon *= 0.95;
      //}
    } else {
      genFac = 0;
    }

    totalFactibles = 0;
    indBest = 0;
    for(int i =0; i < tamPob; i++) {
      evalua_individuo(pob[i], fObj, g, h, epsilon, 0);
      if (es_factible(pob[i])) totalFactibles++;
      if (compara_individuos(&pob[i], &pob[indBest]) < 0 ) indBest = i;
    }

    /*printf("gen %d eps %g tFac %d bestEval %g STV %g \n", 
      numIt, epsilon, totalFactibles, pob[indBest]->eval, 
      pob[indBest]->sumResG + pob[indBest]->sumResH );*/
  
    numIt++;
  }

  s_ind_ed *bestED = genera_ind_ed(dim, numG, numH);
  copiar_individuo(pob[indBest], bestED);

  libera_poblacion_ed(pob, tamPob);
  libera_individuo_ed(nuevo);
  libera_poblacion_ed(hijos, tamPob);

  s_resultado_ed resultado; 
  resultado.ind = bestED;
  resultado.totalEvals = numEval;
  resultado.totalGens = numIt;
  resultado.genBest = genBest;

  return resultado;
}