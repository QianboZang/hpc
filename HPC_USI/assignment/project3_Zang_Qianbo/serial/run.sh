#!/bin/bash
for t in {1..24}
do
    # export OMP_NUM_THREADS=$t
    ./main 64 100 0.005 >> t_ser
done