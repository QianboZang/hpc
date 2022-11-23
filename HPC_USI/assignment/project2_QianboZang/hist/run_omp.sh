#!/bin/bash
for t in {1..25}
do
    export OMP_NUM_THREADS=$t
    ./hist_omp >> terminal_omp
done