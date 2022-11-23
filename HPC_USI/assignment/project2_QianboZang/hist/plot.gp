set terminal postscript color
set output "time10000000.ps"
set style data linespoints
set style line 1 linetype 1
set style line 2 linetype 2

set title "Execution Times"
set xlabel "Number of Threads (t)"
set ylabel "walltime (s)"
set grid
set xrange [1:20]

plot    "terminal_seq10000000" using ($0+1):2 title "Serial" with linespoints,\
        "terminal_omp10000000" using ($0+1):2 title "Parallel" with linespoints