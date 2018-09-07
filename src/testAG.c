#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <time.h>
#include "algoritmo_genetico.h"
#include "funciones_objetivo.h"
#include "f_utiles.h"

int main(int argc, char **argv) {
  
  srand(time(NULL));
  int tmpRand = rand();

  int numFun = atoi(argv[1]);
  int tamPob = atoi(argv[2]);
  int dim = atoi(argv[3]);
  int nBits = atoi(argv[4]);
  int maxEval = atoi(argv[5]);

  double tolerF = atof(argv[6]);
  double ini = atof(argv[7]);
  double fin = atof(argv[8]);

  double pc = atof(argv[9]);
  int tipoCruza = atoi(argv[10]);
  int numReps = argc > 11 ? atoi(argv[11]) : 11;

  double (*f)(double *, int);

  switch(numFun) {
    case ELLIPSOID:
      f = ellipsoid;
      break;
    case ZAKHAROV:
      f = zakharov;
      break;
    case ROSENBROCK:
      f = rosenbrock;
      break;
    case ACKLEY:
      f = ackley;
      break;
    case GRIEWANGK:
      f = griewangk;
      break;
    case RASTRIGIN:
      f = rastrigin;
      break;
    case SPHERE:
    default:
      f = sphere;
      break;
  }

  printf("Ejecutando algoritmo para la funcion: %d \n", numFun );
  printf("Parametros: \n");
  printf("tamanio Poblacion: %d , dimension: %d , num Bits: %d \n", tamPob, dim, nBits );
  printf("num max de Evals: %d, toler func: %g \n", maxEval, tolerF);
  printf("intervalo de busqueda: [%g, %g] \n", ini, fin );
  printf("probabilidad de cruza: %g \n", pc );

  double delta = (fin - ini)/ (pow(2, nBits) - 1);

  printf("Delta1: %g \n", delta);

  s_resultado_ag res[numReps];
  double numEvals[numReps];
  double mejorEvals[numReps];

  double minMejorEval = DBL_MAX;
  double maxMejorEval = DBL_MIN;

  double ratioExito = 0;

  for(int i=0; i < numReps; i++) {
    printf("\n%d ", i);
    res[i] = algoritmo_genetico( tamPob, dim, nBits, maxEval, tolerF, 
      ini, fin, pc, tipoCruza, f);

    numEvals[i] = res[i].totalEvals;
    mejorEvals[i] = res[i].ind->eval;

    minMejorEval = mejorEvals[i] < minMejorEval ? mejorEvals[i] : minMejorEval;
    maxMejorEval = mejorEvals[i] > maxMejorEval ? mejorEvals[i] : maxMejorEval;

    ratioExito += val_abs(res[i].ind->eval) <= tolerF ? 1 : 0;

    
    printf("Mejor individuo encontrado: \n");
    imprime_individuo(res[i].ind);
  }

  /* Calcula Estadisticas */
  double promedioEvals = calcula_promedio(numEvals, numReps);
  double promedioMejorRes = calcula_promedio(mejorEvals, numReps);
  double medianaMejorRes = calcula_mediana(mejorEvals, numReps);

  double desvEstEvals = calcula_desv_est_muest(numEvals, numReps);
  double desvEstMejEvals = calcula_desv_est_muest(mejorEvals, numReps);

  ratioExito /= numReps;
  ratioExito *= 100;

  printf("\npromedio del total de Evals: %g \n", promedioEvals);
  printf("Desviacion Estandar del total de Evals: %g \n", desvEstEvals);

  printf("\npromedio de las mejores Evals: %g \n", promedioMejorRes);
  printf("mediana de las mejores Evals: %g \n", medianaMejorRes);
  printf("Desviacion Estandar de las mejores Evals: %g \n", desvEstMejEvals);

  printf("Min valor de mejor Evaluacion alcanzada: %g \n", minMejorEval );
  printf("Max valor de mejor Evaluacion alcanzada: %g \n", maxMejorEval );


  printf("\nPorcentaje de Exito: %g \n", ratioExito);


  for(int i =0; i < numReps; i++) {
    libera_individuo(res[i].ind);
  }

  return 0;
}