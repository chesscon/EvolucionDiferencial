#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include "algoritmo_genetico.h"
#include "f_utiles.h"

s_individuo * genera_inidividuo(int dim, int nBits, double ini, double fin) {
  s_individuo *ind = malloc(sizeof(s_individuo));

  int tamTotal = dim*nBits;

  ind->x = malloc(sizeof(int)*tamTotal);

  ind->dim = dim;
  ind->nBits = nBits;

  ind->ini = ini;
  ind->fin = fin;

  ind->eval = DBL_MAX;

  return ind;
}

s_individuo * genera_inidividuo_rand(int dim, int nBits, double ini, double fin) {
  s_individuo *ind = genera_inidividuo(dim, nBits, ini, fin);

  int tamTotal = nBits*dim;

  for(int i=0; i < tamTotal; i++) {
    ind->x[i] = rand() % 2;
  }

  return ind;
}

int cmp_ind(const void * a, const void * b) {
  s_individuo *ind_a = *(s_individuo **) a;
  s_individuo *ind_b = *(s_individuo **) b;

  if (ind_a->eval > ind_b->eval ) return 1;
  if (ind_a->eval < ind_b->eval ) return -1;
  return 0;
}

void imprime_individuo(s_individuo *ind) {
  int k=0;
  printf("%g [ ",ind->eval);
  double delta = (ind->fin - ind->ini) / ( pow(2.0, ind->nBits) - 1);
  printf("[%g, %g], delta: %g, nBits: %d \n", ind->ini, ind->fin, delta, ind->nBits );
  printf("delta: %e \n",delta );
  double aux = 0;
  for(int i=0; i<ind->dim; i++) {
    aux = binario_a_decimal(ind->x + i*ind->nBits, ind->nBits  );
    printf("\n%e (", ind->ini + aux*delta);

    for(int j=0; j< ind->nBits; j++) {
      printf("%d ", ind->x[k]);
      k++;
    }
    printf("), ");
  }
  printf("]\n");
}

void libera_individuo(s_individuo *ind) {
  free(ind->x);
  free(ind);
}

s_individuo ** init_poblacion(int tamPob, int dim, int nBits, double ini, double fin) {
  s_individuo **pob = malloc(sizeof(s_individuo *)*tamPob);
  for(int i=0; i < tamPob; i++) {
    pob[i] = genera_inidividuo_rand(dim, nBits, ini, fin);
  }

  return pob;
}

void libera_poblacion(s_individuo **pob, int tamPob) {

  for(int i =0; i < tamPob; i++) {
    libera_individuo(pob[i]);
  }

  free(pob);
}

double * decodifica_individuo(s_individuo *ind) { 

  double *x = malloc(sizeof(double)*ind->dim);

  double aux = 0;
  double delta = (ind->fin - ind->ini)/ (pow(2, ind->nBits) - 1);

  for(int i =0; i <  ind->dim; i++) {
    aux = binario_a_decimal(ind->x + i*ind->nBits, ind->nBits  );
    //printf("%g, ", ind->ini + aux*delta);

    x[i] = ind->ini + aux*delta;
  }

  return x;

}

double evalua_individuo(s_individuo *ind, double (*f)(double *, int) ) {
  double *x = decodifica_individuo(ind);

  ind->eval = f(x, ind->dim);

  free(x);

  return ind->eval;
}

/* devuelve el indice del individuo con la mejor evaluacion */
int evalua_poblacion(s_individuo **pob, int tamPob, double(*f)(double *, int) ) {

  double bestEval = DBL_MAX;
  int bestInd = 0;

  double aux = 0;
  for(int i =0; i < tamPob; i++) {
    aux = evalua_individuo(pob[i], f);

    if (aux < bestEval) {
      bestEval = aux;
      bestInd = i;
    }
  }

  return bestInd;
}

/* Cruza individuos utilizando un punto de cruza, elegido de manera aleatoria */
s_individuo ** cruza_individuos_1(s_individuo *p1, s_individuo *p2, double pc) {
  s_individuo **hijos = malloc(sizeof(s_individuo *)*2);
  hijos[0] = genera_inidividuo(p1->dim, p1->nBits, p1->ini, p1->fin);
  hijos[1] = genera_inidividuo(p2->dim, p2->nBits, p2->ini, p2->fin);

  int tamTotal = p1->dim*p1->nBits;

  int ptoCruza = rand() % tamTotal;

  double tmpRand = rand();
  tmpRand /= RAND_MAX;

  if (tmpRand < pc) {
    for(int i=0; i < ptoCruza; i++) {
      hijos[0]->x[i] = p1->x[i];
      hijos[1]->x[i] = p2->x[i];
    }

    for(int i=ptoCruza; i < tamTotal; i++) {
      hijos[0]->x[i] = p2->x[i];
      hijos[1]->x[i] = p1->x[i];
    }
  } else {
    for(int i=0; i < tamTotal; i++) {
      hijos[0]->x[i] = p1->x[i];
      hijos[1]->x[i] = p2->x[i];
    }
  }

  return hijos;
}

/* Cruza individuos utilizando dos puntos de cruza, elegidos de manera aleatoria */
s_individuo ** cruza_individuos_2(s_individuo *p1, s_individuo *p2, double pc) {
  s_individuo **hijos = malloc(sizeof(s_individuo *)*2);
  hijos[0] = genera_inidividuo(p1->dim, p1->nBits, p1->ini, p1->fin);
  hijos[1] = genera_inidividuo(p2->dim, p2->nBits, p2->ini, p2->fin);

  int tamTotal = p1->dim*p1->nBits;

  int ptoCruza1 = rand() % tamTotal;
  int ptoCruza2 = rand() % tamTotal;

  int aux;
  if (ptoCruza2 < ptoCruza1) {
    aux = ptoCruza2;
    ptoCruza2 = ptoCruza1;
    ptoCruza1 = aux;
  }


  double tmpRand = rand();
  tmpRand /= RAND_MAX;

  if (tmpRand < pc) {

    for(int i=0; i < ptoCruza1; i++) {
      hijos[0]->x[i] = p1->x[i];
      hijos[1]->x[i] = p2->x[i];
    }

    for(int i=ptoCruza1; i < ptoCruza2; i++) {
      hijos[0]->x[i] = p2->x[i];
      hijos[1]->x[i] = p1->x[i];
    }

    for(int i=ptoCruza2; i < tamTotal; i++) {
      hijos[0]->x[i] = p1->x[i];
      hijos[1]->x[i] = p2->x[i];
    }

  } else { // copiamos los padres a los hijos
    for(int i=0; i < tamTotal; i++) {
      hijos[0]->x[i] = p1->x[i];
      hijos[1]->x[i] = p2->x[i];
    }
  }

  return hijos;
}

void muta_individuo(s_individuo *ind, double pm) {

  double numAle = 0;

  int tamTotal = ind->dim*ind->nBits;

  for(int i=0; i < tamTotal; i++) {
    numAle = rand();
    numAle /= RAND_MAX;
    ind->x[i] = numAle < pm ? 1 - ind->x[i] : ind->x[i];
  }
}


/* Seleccion de padres por torneo binario */
void seleciona_padres(s_individuo **pob,  int tamPob, s_individuo **p1, s_individuo **p2) {

  // Seleccionamos de manera aleatoria dos individuos y elegimos
  // al que tenga mejor aptitud como padre 1 (p1). Repetimos para p2

  int auxRand1 = rand() % tamPob;
  int auxRand2 = rand() % tamPob;

  if (pob[auxRand1]->eval < pob[auxRand2]->eval) { 
    *p1 = pob[auxRand1];
  } else {
    *p1 = pob[auxRand2];
  }

  auxRand1 = rand() % tamPob;
  auxRand2 = rand() % tamPob;

  if (pob[auxRand1]->eval < pob[auxRand2]->eval) { 
    *p2 = pob[auxRand1];
  } else {
    *p2 = pob[auxRand2];
  }  

}

s_resultado_ag algoritmo_genetico( int tamPob, int dim, int nBits,
  int maxEval, double tolerF, double ini, double fin, double pc, int tipoCruza,
  double (*f)(double *, int) ) {

//  printf("Ejecutando AG....\n");

  int numEvals = 0;
  s_individuo **pob = init_poblacion(tamPob, dim, nBits, ini, fin);
  int indBestEval = evalua_poblacion(pob, tamPob, f);
  double bestEval = pob[indBestEval]->eval;
  numEvals += tamPob;

  double promEvalPob = calcular_promedio_evalucion_pob(pob, tamPob);

  int totalHijos = tamPob;

//  printf("Total de Hijos: %d \n", totalHijos );

  s_individuo **hijos = malloc(sizeof(s_individuo *)*totalHijos);
  s_individuo **tmp_hijos;
  s_individuo *tmp_best;

  double bestHijo = 0;
  int indBestEvalHijo = 0;

  double pm = (1.0)/(dim*nBits);

  int numHijos = 0;

  s_individuo *p1 = NULL;
  s_individuo *p2 = NULL;

  int numGeneracion =0;

  printf("Generacion\tPromedio\tMejor\n");
//  printf("%d\t%g\t%e\n",numGeneracion, promEvalPob, bestEval );

  int numInstancias[4];
  numInstancias[0] = 0;
  numInstancias[1] = 0;
  numInstancias[2] = 0;
  numInstancias[3] = 0;

  // 00*****************
  s_individuo *esq0 = genera_inidividuo(1, nBits, ini, fin);

  // 11*****************
  s_individuo *esq1 = genera_inidividuo(1, nBits, ini, fin);

  // 0**********1
  s_individuo *esq2 = genera_inidividuo(1, nBits, ini, fin);

  // 1********0
  s_individuo *esq3 = genera_inidividuo(1, nBits, ini, fin);

  for(int i =0; i < nBits; i++) {
    esq0->x[i] = ESQ_COMODIN;
    esq1->x[i] = ESQ_COMODIN;
    esq2->x[i] = ESQ_COMODIN;
    esq3->x[i] = ESQ_COMODIN;
  }
  esq0->x[0] = 0;
  esq0->x[1] = 0;
  esq1->x[0] = 1;
  esq1->x[1] = 1;
  esq2->x[0] = 0;
  esq2->x[nBits-1] = 1;
  esq3->x[0] = 1;
  esq3->x[nBits-1] = 0;

  printf("%d\t%d\t%d\t%d\t%d\n", numGeneracion, cuenta_instancias_esquema(pob, tamPob,  esq0), 
      cuenta_instancias_esquema(pob, tamPob,  esq1), cuenta_instancias_esquema(pob, tamPob,  esq2),
      cuenta_instancias_esquema(pob, tamPob,  esq3) );

  while(numEvals < maxEval && val_abs(bestEval) > tolerF ) {

    numGeneracion++;

    double tmpRand = 0;

    numHijos = 0;
    while (numHijos < totalHijos && (numEvals + numHijos ) < maxEval  ) {
      // SELECIONA PADRES
      seleciona_padres(pob, tamPob, &p1, &p2);

      tmpRand = ( (double) rand())/RAND_MAX;

      // CRUZA (genera hijos)
      if (tipoCruza == 1) {
        tmp_hijos = cruza_individuos_1(p1, p2, pc);
      } else {
        tmp_hijos = cruza_individuos_2(p1, p2, pc);
      }
      hijos[numHijos] = tmp_hijos[0];

      // MUTACION (hijos)
      muta_individuo(hijos[numHijos], pm);

      numHijos++;

      if (numHijos < totalHijos) {
        hijos[numHijos] = tmp_hijos[1];
        muta_individuo(hijos[numHijos], pm);
        numHijos++;
      } else {
        libera_individuo(tmp_hijos[1]);
      }
      free(tmp_hijos);
    }

    // EVALUA HIJOS
    indBestEvalHijo = evalua_poblacion(hijos, numHijos, f);
    bestHijo = hijos[indBestEvalHijo]->eval;
//    printf("bestEval hijo: %g \n", bestHijo );

    numEvals += numHijos;

    // REEMPLAZAMIENTO

    // Si los hijos no superan al mejor de la pob, se agrega en la sig generacion:
    if (bestEval < bestHijo ) {
      tmp_best = pob[indBestEval];
      pob[indBestEval] = hijos[0];
      hijos[0] = tmp_best;
      indBestEval = 0;
    } else {
      indBestEval = indBestEvalHijo;
      bestEval = bestHijo;
    }

    for(int i=0; i < tamPob; i++) {
      libera_individuo(pob[i]);
      pob[i] = hijos[i];
      //printf("Sustituyando... k: %d= %g, i:%d \n", k, hijos[k]->eval, i  );
    }
    promEvalPob = calcular_promedio_evalucion_pob(pob, tamPob);

//    printf("%d\t%g\t%e\n",numGeneracion, promEvalPob, bestEval );

    printf("%d\t%d\t%d\t%d\t%d\n", numGeneracion, cuenta_instancias_esquema(pob, tamPob,  esq0), 
      cuenta_instancias_esquema(pob, tamPob,  esq1), cuenta_instancias_esquema(pob, tamPob,  esq2),
      cuenta_instancias_esquema(pob, tamPob,  esq3) );

  }

//  printf("bestEval encontrado: %g \n", bestEval );
//  printf("Total de Evals: %d \n", numEvals );
//  printf("Total Generaciones: %d \n", numGeneracion );

//  printf("Eval Ind[0]: %g \n", pob[0]->eval);

  tmp_best = pob[0];
  pob[0] = pob[indBestEval];
  pob[indBestEval] = tmp_best;

  s_individuo *best = pob[0];

  for(int i=1; i < tamPob; i++) {
    libera_individuo(pob[i]);
  }
  free(hijos);

  libera_individuo(esq0);
  libera_individuo(esq1);
  libera_individuo(esq2);
  libera_individuo(esq3);

  s_resultado_ag resultado; 
  resultado.ind = best;
  resultado.totalEvals = numEvals;
  resultado.totalGens = numGeneracion;

  printf("%d %d %g \n", numEvals, numGeneracion, best->eval );

  free(pob);
  return resultado;
}

double calcular_promedio_evalucion_pob(s_individuo **pob, int tamPob) {

  double promedio = 0;

  for(int i =0; i < tamPob; i++) {
    promedio += pob[i]->eval;
  }

  promedio /= tamPob;

  return promedio;
}

int es_instancia_esquema(s_individuo *ind, s_individuo *esq ) {
  int es_esq = 1;

  int tamTotal = esq->nBits*esq->dim;

  for(int i=0; i < tamTotal; i++) {
    if (esq->x[i] == ESQ_COMODIN || esq->x[i] == ind->x[i] ) continue;
    
//    printf("\npos: %d, esq=%d, ind=%d \n",i, esq->x[i], ind->x[i] );
    es_esq = 0;
    break;
  }

  return es_esq;
}

int cuenta_instancias_esquema(s_individuo **pob, int tamPob,  s_individuo *esq) {
  int numInst = 0;

  for(int i=0; i < tamPob; i++) {
    numInst += es_instancia_esquema(pob[i], esq);
  }

  return numInst;
}