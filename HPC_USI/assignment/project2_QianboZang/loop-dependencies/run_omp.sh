#!/bin/bash
for t in {3..20}
do
    export OMP_NUM_THREADS=$t
    ./recur_omp >> terminal_omp
done