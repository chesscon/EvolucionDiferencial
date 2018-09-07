/* Benchmar Optimizacion con Restricciones */
#ifndef BECNHMARK_OR
#define SYMBOL BECNHMARK_OR

typedef double (*fptr)(double *, int);
typedef void (*gptr)(double *, int, double *, int);
typedef void (*hptr)(double *, int, double *, int);

typedef struct {
  int dim;
  int numG;
  int numH;
  double * opt;
  double valOpt;
  double * ini;
  double *fin;

  fptr f;
  gptr g;
  hptr h;
} s_data;

s_data obtener_funciones(int numFun);

s_data leer_datos_funcion(char *nombre_archivo, int numFun);

double g1_f(double *x, int n);
void g1_g(double *x, int n, double *g, int m);

double g2_f(double *x, int n);
void g2_g(double *x, int n, double *g, int m);

double g3_f(double *x, int n);
void g3_h(double *x, int n, double *h, int m);

double g4_f(double *x, int n);
void g4_g(double *x, int n, double *g, int m);

double g5_f(double *x, int n);
void g5_g(double *x, int n, double *g, int m);
void g5_h(double *x, int n, double *h, int m);

double g6_f(double *x, int n);
void g6_g(double *x, int n, double *g, int m);

double g7_f(double *x, int n);
void g7_g(double *x, int n, double *g, int m);

double g8_f(double *x, int n);
void g8_g(double *x, int n, double *g, int m);

double g9_f(double *x, int n);
void g9_g(double *x, int n, double *g, int m);

double g10_f(double *x, int n);
void g10_g(double *x, int n, double *g, int m);

double g11_f(double *x, int n);
void g11_h(double *x, int n, double *h, int m);

double g12_f(double *x, int n);
void g12_g(double *x, int n, double *g, int m);

double g13_f(double *x, int n);
void g13_h(double *x, int n, double *h, int m); 

#endif