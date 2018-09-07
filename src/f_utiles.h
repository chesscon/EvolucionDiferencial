#ifndef F_UTILES_H
#define F_UTILES_H

int binario_a_decimal(int *x, int n);

double val_abs(double val);

int cmp_int(const void * a, const void * b);

int cmp_dbl(const void * a, const void * b);

double calcula_promedio(double *arr, int n);

double calcula_mediana(double *arr, int n);

double calcula_desv_est_muest(double *arr, int n);

double calcula_minimo(double *arr, int n);

double calcula_maximo(double *arr, int n);

#endif