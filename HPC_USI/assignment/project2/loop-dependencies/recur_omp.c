#include "walltime.h"
#include <math.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int N = 2000000000;
    double up = 1.00000001;
    double Sn = 1.00000001;
    int n;
    /* allocate memory for the recursion */
    double *opt = (double *)malloc((N + 1) * sizeof(double));

    if (opt == NULL)
        die("failed to allocate problem size");

    double time_start = wall_time();
    // TODO: YOU NEED TO PARALLELIZE THIS LOOP
    #pragma omp parallel for shared(opt) lastprivate(Sn)
    for (n = 0; n <= N; ++n) {
        // when n=0, Sn = up^(1) = up^(n+1)
        Sn = pow(up, n+1);
        opt[n] = Sn; 
    }

    printf("Parallel RunTime: %f seconds\n", wall_time() - time_start);
    printf("Final Result Sn    :  %.17g \n", Sn);

    double temp = 0.0;
    for (n = 0; n <= N; ++n) {
        temp += opt[n] * opt[n];
    }
    printf("Result ||opt||^2_2 :  %f\n", temp / (double)N);
    printf("\n");
}
