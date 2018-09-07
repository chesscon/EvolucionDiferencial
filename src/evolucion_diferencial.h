#ifndef EVOLUCION_DIFERENCIAL_H
#define EVOLUCION_DIFERENCIAL_H

#include <gsl/gsl_rng.h>

typedef struct {
  double *ind;
  int dim;
  int numG;
  int numH;
  double *evalG;
  double *evalH;
  double eval;

  double sumResG;
  double sumResH;
} s_ind_ed;

typedef struct {
  s_ind_ed *ind;
  int totalEvals;
  int totalGens;

  int genBest;
} s_resultado_ed;

//#define MAX(x, y) (((x) > (y)) ? (x) : (y))
//#define MIN(x, y) (((x) < (y)) ? (x) : (y))

typedef double (*ApFunObj)(double *, int);
typedef void (*ApFunRes)(double *, int, double *, int);

s_ind_ed * genera_ind_ed(int dim, int numG, int numH);

s_ind_ed * genera_ind_ed_rand(int dim, int numG, int numH, double *ini, double *fin);

void libera_individuo_ed(s_ind_ed *ind);

void imprime_individuo_ed(s_ind_ed *ind);

s_ind_ed ** genera_poblacion_inicial(int tamPob, int dim, int numG, int numH,
  double *ini, double *fin);

void libera_poblacion_ed(s_ind_ed **pob, int tamPob);

int es_factible(s_ind_ed *ind1);

int compara_individuos(const void * a, const void * b);

void copiar_individuo(s_ind_ed *src, s_ind_ed *dst);

void evalua_individuo(s_ind_ed *ind, ApFunObj f, ApFunRes g, ApFunRes h, 
  double epsilon, int actualizarEval);

s_resultado_ed evolucion_diferencial(int tamPob, int dim, int numG, int numH,
  double CR, double F, double epsilonIni, double p,
  int maxEval, double *ini, double *fin, 
  ApFunObj fObj, ApFunRes g, ApFunRes h, gsl_rng *r);

#endif