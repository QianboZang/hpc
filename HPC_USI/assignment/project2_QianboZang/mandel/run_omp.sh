for t in {1..30}
do
    export OMP_NUM_THREADS=$t
    ./mandel_omp >> terminal_omp
done