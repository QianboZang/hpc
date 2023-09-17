#!/bin/bash
for np in {3..20}
do
    mpiexec -n $np python main.py 1024 100 0.005 verbose >> 1024
done