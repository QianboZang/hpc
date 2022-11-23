set terminal postscript color
set output "time2.ps"
set style data linespoints
set style line 1 linetype 1
set style line 2 linetype 2

set title "Execution Times"
set xlabel "Number of Threads (t)"
set ylabel "walltime (s)"
set grid
set xrange [1:20]

plot    "terminal_seq200000000" using ($0+1):3 title "Serial" with linespoints,\
        "terminal_omp200000000" using ($0+1):3 title "Parallel" with linespoints