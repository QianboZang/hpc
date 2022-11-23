#!/bin/bash
for t in {1..24}
do
    export OMP_NUM_THREADS=$t
    ./dotProduct >> terminal
done