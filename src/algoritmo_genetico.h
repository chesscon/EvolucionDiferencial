#ifndef ALGORITMO_GENETICO_H
#define ALGORITMO_GENETICO_H

#define ESQ_COMODIN 3

typedef struct {
  int *x;
  int dim;
  int nBits;

  double ini;
  double fin;

  double eval;
} s_individuo;

typedef struct {
  s_individuo *ind;
  int totalEvals;
  int totalGens;
} s_resultado_ag;

s_individuo * genera_inidividuo(int dim, int nBits, double ini, double fin);

s_individuo * genera_inidividuo_rand(int dim, int nBits, double ini, double fin);

int cmp_ind(const void * a, const void * b);

void imprime_individuo(s_individuo *ind);

void libera_individuo(s_individuo *ind);

s_individuo ** init_poblacion(int tamPob, int dim, int nBits, double ini, double fin);

void libera_poblacion(s_individuo **pob, int tamPob);

double * decodifica_individuo(s_individuo *ind);

double evalua_individuo(s_individuo *ind, double (*f)(double *, int) );

/* devuelve el indice del individuo con la mejor evaluacion */
int evalua_poblacion(s_individuo **pob, int tamPob, double(*f)(double *, int) );

void seleciona_padres(s_individuo **pob,  int tamPob, s_individuo **p1, s_individuo **p2);

s_individuo ** cruza_individuos_1(s_individuo *p1, s_individuo *p2,  double pc);

s_individuo ** cruza_individuos_2(s_individuo *p1, s_individuo *p2,  double pc);

void muta_individuo(s_individuo *ind, double pm);

s_resultado_ag algoritmo_genetico( int tamPob, int dim, int nBits,
  int maxEval, double tolerF, double ini, double fin, double pc, int tipoCruza,
  double (*f)(double *, int) );

double calcular_promedio_evalucion_pob(s_individuo **pob, int tamPob);

int es_instancia_esquema(s_individuo *ind, s_individuo *esq );

int cuenta_instancias_esquema(s_individuo **pob, int tamPob,  s_individuo *esq);

#endif