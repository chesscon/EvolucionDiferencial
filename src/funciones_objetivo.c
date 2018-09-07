#include <math.h>
#include "funciones_objetivo.h"

double sphere(double *x, int n) {
  double res = 0;

  for(int i=0; i < n; i++) {
    res += x[i]*x[i];
  }

  return res;
}

double ellipsoid(double *x, int n) {
  double res = 0;

  for(int i=0; i < n; i++) {
    res += pow(10, 6*( (i) / (n-1) ) )*x[i]*x[i];
  }

  return res;
}

double zakharov(double *x, int n) {
  double res = 0;

  double aux = 0;
  for(int i=0; i < n; i++) {
    res += x[i]*x[i];
    
    aux += 0.5*(i+1)*x[i];
  }

  res += aux*aux;
  res += aux*aux*aux*aux;

  return res;
}

double rosenbrock(double *x, int n) {
  double res = 0;

  for(int i=0; i < n-1; i++) {
    res += (1-x[i])*(1-x[i]);
    res += 100*(x[i+1]-x[i]*x[i])*(x[i+1]-x[i]*x[i]);
  }
  return res;
}

double ackley(double *x, int n) {
  double res = 0;

  double aux1=0;
  double aux2=0;

  for(int i =0; i< n; i++) {
    aux1 += x[i]*x[i];
    aux2 += cos(2*M_PI*x[i]);
  }

  res += -20*exp(-0.2*sqrt(aux1/n));
  res -= exp(aux2/n);
  res += 20 + M_E;

  return res;
}

double griewangk(double *x, int n) {
  double res=0;

  double aux1=0;
  double aux2=1;

  for(int i =0; i < n; i++) {
    aux1 += (x[i]*x[i])/4000;
    aux2 *= cos(x[i]/sqrt(i+1));
  }

  res = aux1 - aux2 + 1;

  return res;
}

double rastrigin(double *x, int n) {
  double res= 10*n;

  for(int i =0; i < n; i++) {
    res += x[i]*x[i] - 10*cos(2*M_PI*x[i]);
  }

  return res;
}