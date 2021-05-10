#include <stdio.h>
#include <omp.h>
#ifndef NTHREADS
#define NTHREADS 1 // Do not modify!
#endif


int main () {

    static long steps       = 100000000;
    static long MULTIPLIER  = 1366;
    static long ADDEND      = 150889;
    static long PMOD        = 714025;
    long random_last        = PMOD/ADDEND;
    double random_low       = -1;
    double random_hi        = 1;
    double  r               = 1.0;

    long random_next;
    double ret_val;
    long i;
    double pi, x, y, dist;
    double start, end;
    long int total = 0;

    start = omp_get_wtime();

    #pragma omp parallel for
    for(i=0;i<steps; i++) {

        random_next = (MULTIPLIER  * random_last + ADDEND)% PMOD;
        random_last = random_next;
        x = ((double)random_next/(double)PMOD)*(random_hi-random_low)+random_low;

        random_next = (MULTIPLIER  * random_last + ADDEND)% PMOD;
        random_last = random_next;
        y = ((double)random_next/(double)PMOD)*(random_hi-random_low)+random_low;

        dist = x*x + y*y;

        if (dist <= r*r) {
            #pragma omp atomic
            total++;
        }
    }

    end = omp_get_wtime();
    pi = 4.0 * ((double)total/(double)steps);
    printf("i is %f \n\n", pi);
    printf("Elapsed time for Monte Carlo %f\n\n",end-start);

    return 0;
}
