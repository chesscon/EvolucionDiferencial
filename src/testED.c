#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <time.h>
#include "evolucion_diferencial.h"
#include "funciones_objetivo.h"
#include "f_utiles.h"
#include "benchmarkOR.h"

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

int main(int argc, char **argv) {
  
  unsigned int seed = time(NULL);
  srand(seed);

  const gsl_rng_type * T;
  gsl_rng * r;

  gsl_rng_env_setup();

  T = gsl_rng_default;
  r = gsl_rng_alloc (T);

  gsl_rng_set (r, seed);

  int tmpRand = rand();

  int numFun = atoi(argv[1]);
  int tamPob = atoi(argv[2]);
  int maxEval = atoi(argv[4]);

  char *nombre_archivo = argv[3];
  double epsilonIni = atof(argv[5]);
  double p = atof(argv[6]);

  int dimG = 0;
  int dimH = 0;

  double CR = atof(argv[7]);
  double F = atof(argv[8]);
  int numReps = argc > 9 ? atoi(argv[9]) : 10;

  s_data datFun = leer_datos_funcion(nombre_archivo, numFun);


//  printf("Ejecutando algoritmo para la funcion: %d \n", numFun );
  printf("#Parametros: \n");
  printf("#tamanio Poblacion: %d , dimension: %d \n", tamPob, datFun.dim );
  printf("#num max de Evals: %d \n", maxEval );
//  printf("intervalo de busqueda: [%g, %g] \n", ini, fin );
  printf("#CR: %g, F: %g \n", CR, F );
  printf("#Total de Repeticiones: %d \n", numReps );

//  double ratioExito = 0;

/********* ******* */
  //for( CR=0.1; CR <= 0.91; CR+= 0.1) {
  //  for( F=0.1; F <= 0.2; F+=0.1) {
      printf("#\n#------------------------------------------------\n");
      printf("#\n#CR: %g, F: %g \n", CR, F );     

      s_resultado_ed res[numReps];
      double numEvals[numReps];
      double mejorEvals[numReps];

      double generacionBest[numReps];

      double minMejorEval = DBL_MAX;
      double maxMejorEval = -DBL_MAX;

      for(int i=0; i < numReps; i++) {
        //printf("\n#%d ", i);

        res[i] = evolucion_diferencial( tamPob, 
          datFun.dim, datFun.numG, datFun.numH,
          CR, F, epsilonIni, p, maxEval,
          datFun.ini, datFun.fin, 
          datFun.f, datFun.g, datFun.h, r);

        numEvals[i] = res[i].totalEvals;
        mejorEvals[i] = res[i].ind->eval;
        generacionBest[i] = res[i].genBest;

        minMejorEval = mejorEvals[i] < minMejorEval ? mejorEvals[i] : minMejorEval;
        maxMejorEval = mejorEvals[i] > maxMejorEval ? mejorEvals[i] : maxMejorEval;

        //ratioExito += val_abs(res[i].ind->eval) <= tolerF ? 1 : 0;

        
        //printf("#\n#Mejor individuo encontrado (en la generacion %d): \n", res[i].genBest);
        //imprime_individuo_ed(res[i].ind);
      }

      /* Calcula Estadisticas */
      double promedioEvals = calcula_promedio(numEvals, numReps);
      double promedioMejorRes = calcula_promedio(mejorEvals, numReps);
      double medianaMejorRes = calcula_mediana(mejorEvals, numReps);

      double promedioGeneracionBest = calcula_promedio(generacionBest, numReps);

      double desvEstEvals = calcula_desv_est_muest(numEvals, numReps);
      double desvEstMejEvals = calcula_desv_est_muest(mejorEvals, numReps);

    //  ratioExito /= numReps;
    //  ratioExito *= 100;

      printf("#\n#promedio del total de Evals: %g \n", promedioEvals);
      printf("#Desviacion Estandar del total de Evals: %g \n", desvEstEvals);

      printf("#\n#promedio de las mejores Evals: %g \n", promedioMejorRes);
      printf("#mediana de las mejores Evals: %g \n", medianaMejorRes);
      printf("#Desviacion Estandar de las mejores Evals: %g \n", desvEstMejEvals);

      printf("#\n#promedio de la generacion del Mejor: %g \n", promedioGeneracionBest);

      printf("#Min valor de mejor Evaluacion alcanzada: %e %g \n", minMejorEval, minMejorEval );
      printf("#Max valor de mejor Evaluacion alcanzada: %e %g \n", maxMejorEval, maxMejorEval );


    //  printf("\nPorcentaje de Exito: %g \n", ratioExito);

      for(int i =0; i < numReps; i++) {
        libera_individuo_ed(res[i].ind);
      }

  //  } // END F
  //} // END CR

  free(datFun.ini);
  free(datFun.fin);

  gsl_rng_free (r);

  return 0;
}