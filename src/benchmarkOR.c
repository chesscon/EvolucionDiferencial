#include <math.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include "benchmarkOR.h"


s_data obtener_funciones(int numFun) {
  s_data res;
  res.f = NULL;
  res.g = NULL;
  res.h = NULL;

  switch(numFun) {
    case 1:
      res.f = g1_f;
      res.g = g1_g;
      break;
    case 2:
      res.f = g2_f;
      res.g = g2_g;
      break;
    case 3:
      res.f = g3_f;
      res.h = g3_h;
      break;
    case 4:
      res.f = g4_f;
      res.g = g4_g;
      break;
    case 5:
      res.f = g5_f;
      res.g = g5_g;
      res.h = g5_h;
      break;
    case 6:
      res.f = g6_f;
      res.g = g6_g;
      break;
    case 7:
      res.f = g7_f;
      res.g = g7_g;
      break;
    case 8:
      res.f = g8_f;
      res.g = g8_g;
      break;
    case 9:
      res.f = g9_f;
      res.g = g9_g;
      break;
    case 10:
      res.f = g10_f;
      res.g = g10_g;
      break;
    case 11:
      res.f = g11_f;
      res.h = g11_h;
      break;
    case 12:
      res.f = g12_f;
      res.g = g12_g;
      break;
    case 13:
      res.f = g13_f;
      res.h = g13_h;
      break;
  }

  return res;
}

s_data leer_datos_funcion(char *nombre_archivo, int numFun) {
  FILE *in = fopen(nombre_archivo, "r");

  s_data res = obtener_funciones(numFun);

  int tmp = fscanf(in, "%d", &(res.dim));
  tmp = fscanf(in, "%d", &(res.numG));
  tmp = fscanf(in, "%d", &(res.numH));

  res.ini = malloc(sizeof(double)*res.dim);
  res.fin = malloc(sizeof(double)*res.dim);
  res.opt = NULL;
  /*res.opt = malloc(sizeof(double)*dim);

  for(int i =0; i < res.dim; i++) {
    tmp = fscanf(in, "%lf", &(res.opt[i]));
  }*/

  tmp = fscanf(in, "%lf", &res.valOpt);

  for(int i =0; i < res.dim; i++) {
    tmp = fscanf(in, "%lf", &(res.ini[i]) );
    tmp = fscanf(in, "%lf", &(res.fin[i]) );
  }
  fclose(in);

  return res;
}

double g1_f(double *x, int n) {
  double res=0;

  double sum1 = 0;
  double sum2 = 0;

  for(int i=0; i<4; i++) {
    sum1 +=x[i];
    sum2 +=x[i]*x[i];
  }
  sum1 *= 5;
  sum2 *= 5;

  res = sum1 - sum2;
  sum1=0;
  for(int i=4; i < 13; i++) {
    sum1 += x[i];
  }

  res -= sum1;

  return res;
}

void g1_g(double *x, int n, double *g, int m) {
  g[0] = 2*x[0]  + 2*x[1] + x[9] + x[10] - 10;
  g[1] = 2*x[0]  + 2*x[2] + x[9] + x[11] - 10;
  g[2] = 2*x[1]  + 2*x[2] + x[10] + x[11] - 10;
  g[3] = -8*x[0] + x[9];
  g[4] = -8*x[1] + x[10];
  g[5] = -8*x[2] + x[11];
  g[6] = -2*x[3] - x[4] + x[9];
  g[7] = -2*x[5] - x[6] + x[10];
  g[8] = -2*x[7] - x[8] + x[11];
}

double g2_f(double *x, int n) {
  double res = 0;

  double sum1= 0;
  double sum2=0;
  double prod1 = 1;

  double cos_xi = 0;
  double cos2_xi = 0;

  for(int i=0; i < n; i++) {
    cos_xi = cos(x[i]);
    cos2_xi = cos_xi*cos_xi;

    sum1 += cos2_xi*cos2_xi;
    prod1 *= cos2_xi;
    sum2 += (i+1)*x[i]*x[i];
  }

  sum2 = sqrt(sum2);

  res = sum1 -2*prod1;
  res /= sum2 != 0 ? sum2 : 1;

  return -fabs(res);
}

void g2_g(double *x, int n, double *g, int m) {
  double sum = 0;
  double prod = 1;

  for(int i=0; i < n; i++) {
    sum += x[i];
    prod *= x[i];
  }


  g[0] = 0.75 - prod;
  g[1] = sum-7.5*n;
}

double g3_f(double *x, int n) {
  double res = pow(sqrt(n), n);

  double prod = 1;
  for(int i =0; i < n; i++) {
    prod *= x[i];
  }

  res *= prod;

  return -res;
}

void g3_h(double *x, int n, double *h, int m) {
  h[0] = 0;
  for(int i =0; i < n; i++) {
    h[0] += x[i]*x[i];
  }
  h[0] -= 1;
}

double g4_f(double *x, int n) {
  double res=0;
  x--;

  res = (5.3578547*x[3]*x[3])
    + (0.8356891*x[1]*x[5])
    + (37.293239*x[1])
    - 40792.141; 

  return res;
}

void g4_g(double *x, int n, double *g, int m) {
  x--;
  g--;

  g[1] = 85.334407 + (0.0056858*x[2]*x[5]) + (0.0006262*x[1]*x[4]) - (0.0022053*x[3]*x[5]) - 92;

  g[2] = -85.334407 - (0.0056858*x[2]*x[5]) - (0.0006262*x[1]*x[4]) + (0.0022053*x[3]*x[5]);

  g[3] = 80.51249 + (0.0071317*x[2]*x[5]) + (0.0029955*x[1]*x[2]) + (0.0021813*x[3]*x[3]) - 110;

  g[4] = -80.51249 - (0.0071317*x[2]*x[5]) - (0.0029955*x[1]*x[2]) - (0.0021813*x[3]*x[3]) + 90;

  g[5] = 9.300961 + (0.0047026*x[3]*x[5]) + (0.0012547*x[1]*x[3]) + (0.0019085*x[3]*x[4]) - 25;

  g[6] = -9.300961 - (0.0047026*x[3]*x[5]) - (0.0012547*x[1]*x[3]) - (0.0019085*x[3]*x[4]) + 20;

}

double g5_f(double *x, int n) {
  double res = 0;

  res += 3*x[0];
  res += 0.000001*(x[0]*x[0]*x[0]);
  res += 2*x[1];
  res += (0.000002/3)*(x[1]*x[1]*x[1]);

  return res;
}

void g5_g(double *x, int n, double *g, int m) {
  g[0] = -x[3] + x[2] - 0.55;
  g[1] = -x[2] + x[3] - 0.55;
}

void g5_h(double *x, int n, double *h, int m) {
  h[0] = 1000*sin(-x[2]-0.25) + 1000*sin(-x[3]-0.25) + 894.8 - x[0];
  h[1] = 1000*sin(x[2]-0.25) + 1000*sin(x[2]-x[3]-0.25) + 894.8 - x[1];
  h[2] = 1000*sin(x[3]-0.25) + 1000*sin(x[3]-x[2]-0.25) + 1294.8;
}

double g6_f(double *x, int n) {
  double res=0;

  double p1 = (x[0]-10);

  res = p1*p1*p1;

  p1 = (x[1]-20);

  res += p1*p1*p1;  

  return res;
}

void g6_g(double *x, int n, double *g, int m) {
  g[0] = -(x[0]-5)*(x[0]-5) - (x[1]-5)*(x[1]-5) + 100;
  g[1] = (x[0]-6)*(x[0]-6) + (x[1]-5)*(x[1]-5) - 82.81;
}

double g7_f(double *x, int n) {
  double res=0;

  res += x[0]*x[0] + x[1]*x[1] + x[0]*x[1] - 14*x[0];
  res += -16*x[1] + (x[2]-10)*(x[2]-10) + 4*(x[3]-5)*(x[3]-5);
  res += (x[4]-3)*(x[4]-3) + 2*(x[5]-1)*(x[5]-1);
  res += 5*x[6]*x[6] + 7*(x[7]-11)*(x[7]-11);
  res += 2*(x[8]-10)*(x[8]-10) + (x[9]-7)*(x[9]-7) + 45;

  return res;
}

void g7_g(double *x, int n, double *g, int m) {
  g[0] = -105 + 4*x[0] + 5*x[1] - 3*x[6] + 9*x[7];

  g[1] = 10*x[0] - 8*x[1] - 17*x[6] + 2*x[7];

  g[2] = -8*x[0] + 2*x[1] + 5*x[8] - 2*x[9] - 12;

  g[3] = 3*(x[0]-2)*(x[0]-2) + 4*(x[1]-3)*(x[1]-3) + 2*x[2]*x[2] - 7*x[3]-120;

  g[4] = 5*x[0]*x[0] + 8*x[1] + (x[2]-6)*(x[2]-6) - 2*x[3] - 40;

  g[5] = x[0]*x[0] + 2*(x[1]-2)*(x[1]-2) - 2*x[0]*x[1] + 14*x[4] - 6*x[5];

  g[6] = 0.5*(x[0]-8)*(x[0]-8) + 2*(x[1]-4)*(x[1]-4) + 3*x[4]*x[4] - x[5] - 30;

  g[7] = -3*x[0] + 6*x[1] + 12*(x[8]-8)*(x[8]-8) - 7*x[9];
}

double g8_f(double *x, int n) {
  double res = 0;

  double s1 = sin(2*M_PI*x[0]);

  res += s1*s1*s1*sin(2*M_PI*x[1]);

  double den = x[0]*x[0]*x[0]*(x[0]+x[1]);

  res /= den != 0 ? den : 1;

  return -res;
}

void g8_g(double *x, int n, double *g, int m) {
  g[0] = x[0]*x[0] - x[1] + 1;

  g[1] = 1 - x[0] + (x[1]-4)*(x[1]-4);
}

double g9_f(double *x, int n) {
  double res=0;

  res += (x[0]-10)*(x[0]-10) + 5*(x[1]-12)*(x[1]-12);
  res += x[2]*x[2]*x[2]*x[2] + 3*(x[3]-11)*(x[3]-11);
  res += 10*x[4]*x[4]*x[4]*x[4]*x[4]*x[4];
  res += 7*x[5]*x[5] + x[6]*x[6]*x[6]*x[6];
  res += -4*x[5]*x[6] - 10*x[5] - 8*x[6];

  return res;
}

void g9_g(double *x, int n, double *g, int m) {
  g[0] = -127 + 2*x[0]*x[0] + 3*x[1]*x[1]*x[1]*x[1] + x[2]
    + 4*x[3]*x[3] + 5*x[4];

  g[1] = -282 + 7*x[0] + 3*x[1] + 10*x[2]*x[2]*x[2] + x[3] - x[4];

  g[2] = -196 + 23*x[1] + x[2]*x[2]*x[2] + 6*x[5]*x[5] - 8*x[6];

  g[3] = 4*x[0]*x[0] + x[1]*x[1] - 3*x[0]*x[1] + 2*x[2]*x[2] + 5*x[5] - 11*x[6];
}

double g10_f(double *x, int n) {
  return (x[0] + x[1] + x[2]);
}

void g10_g(double *x, int n, double *g, int m) {
  g[0] = -1 + 0.0025*(x[3]+x[5]);

  g[1] = -1 + 0.0025*(x[4]+x[6]-x[3]);

  g[2] = -1 + 0.01*(x[7]-x[4]);

  g[3] = -x[0]*x[5] + 833.33252*x[3] + 100*x[0] - 83333.333;

  g[4] = -x[1]*x[6] + 1250*x[4] + x[1]*x[3] - 1250*x[3];

  g[5] = -x[2]*x[7] + 1250000 + x[2]*x[4] - 2500*x[4];
}

double g11_f(double *x, int n) {
  return (x[0]*x[0] + (x[1]-1)*(x[1]-1) );
}

void g11_h(double *x, int n, double *h, int m) {
  h[0] = x[1] - x[0]*x[0];
}

double g12_f(double *x, int n) {
  double res=0;

  res = (100-(x[0]-5)*(x[0]-5) - (x[1]-5)*(x[1]-5) -(x[2]-5)*(x[2]-5))/100.0;

  return -res;
}

void g12_g(double *x, int n, double *g, int m) {
  double valMin = DBL_MAX; 
  double valTmp = 0;

  for(double p=1; p <=9; p++) {
    for(double q=1; q <=9; q++) {
      for(double r=1; r <=9; r++) {
        valTmp = (x[0]-p)*(x[0]-p) + (x[1]-q)*(x[1]-q) + (x[2]-r)*(x[2]-r) - 0.0625;
        valMin = valTmp < valMin ? valTmp : valMin;
      }
    }
  }

  g[0] = valMin;
}

double g13_f(double *x, int n) {
  return exp(x[0]*x[1]*x[2]*x[3]*x[4]);
}

void g13_h(double *x, int n, double *h, int m) {
  h[0] = x[0]*x[0] + x[1]*x[1] + x[2]*x[2] + x[3]*x[3] + x[4]*x[4] - 10;

  h[1] = x[1]*x[2] - 5*x[3]*x[4];

  h[2] = x[0]*x[0]*x[0] + x[1]*x[1]*x[1] + 1;
}