#!/bin/bash
for t in {1..10}
do
    export OMP_NUM_THREADS=$t
    mpirun -np 1 --bind-to none ./main 1024 1024 100 0.01 >> 1024_1
done