#!/bin/bash
for np in {1..4}
do
    mpirun -np $np --bind-to none ./main 1024 100 0.005 >> 1024_2
done
