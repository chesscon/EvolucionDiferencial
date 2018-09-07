#ifndef FUNCIONES_OBJETIVO_H
#define FUNCIONES_OBJETIVO_H

#define SPHERE 1
#define ELLIPSOID 2
#define ZAKHAROV 3
#define ROSENBROCK 4
#define ACKLEY 5
#define GRIEWANGK 6
#define RASTRIGIN 7

double sphere(double *x, int n);

double ellipsoid(double *x, int n);

double zakharov(double *x, int n);

double rosenbrock(double *x, int n);

double ackley(double *x, int n);

double griewangk(double *x, int n);

double rastrigin(double *x, int n);

#endif