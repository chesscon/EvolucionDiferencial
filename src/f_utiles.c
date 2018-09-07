#include <math.h>
#include <stdlib.h>
#include <float.h>
#include "f_utiles.h"

int binario_a_decimal(int *x, int n) {
  int res=0;
  int exponente = 1;
  for(int i=0; i < n; i++) {
    res += x[i]*exponente;
    exponente *= 2;
  }

  return res;
}

double val_abs(double val) {
  return val < 0 ? -val : val;
}


int cmp_int (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int cmp_dbl (const void * a, const void * b) {
   return ( *((double*)a) - *((double*)b) );
}

double calcula_promedio(double *arr, int n) {
  double prom = 0;

  for(int i=0; i< n; i++) {
    prom += arr[i];
  }

  prom /= n;

  return prom;
}

double calcula_mediana(double *arr, int n) {
  qsort(arr, n, sizeof(double), cmp_dbl);

  double mediana = 0;

  if (n%2==0 && n > 1) {
    mediana = (arr[(n/2)-1] + arr[(n/2)])/2;
  } else {
    mediana = arr[(n/2)];
  }

  return mediana;
}

double calcula_desv_est_muest(double *arr, int n) {

  double des_est = 0;

  double prom = calcula_promedio(arr, n);

  for(int i =0; i < n; i++) {
    des_est += ( arr[i] - prom )*( arr[i] - prom );
  }

  des_est /= n > 1 ? (n-1) : 1;

  des_est = sqrt(des_est);

  return des_est;
}

double calcula_minimo(double *arr, int n) {
  double min = DBL_MAX;

  for(int i=0; i< n; i++) {
    min = arr[i] < min ? arr[i] : min;
  }

  return min;
}

double calcula_maximo(double *arr, int n) {
  double max = DBL_MIN;

  for(int i=0; i< n; i++) {
    max = arr[i] > max ? arr[i] : max;
  }

  return max;
}