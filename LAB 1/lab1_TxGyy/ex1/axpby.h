#ifndef AXPBY_H
#define AXPBY_H

#define MEGA 1000000        // 10^6
#define GIGA 1000000000     // 10^9

void axpby(double* x, double* y, double a, double b, int n);
void axpby_openmp(double* x, double* y, double a, double b, int n);
void axpby_openmp_nofor(double* x, double* y, double a, double b, int n);
void print_stats(double start, double end, long int data_size);

#endif