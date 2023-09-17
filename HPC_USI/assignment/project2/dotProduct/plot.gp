set terminal postscript color
set output "time1000000000.ps"
set style data linespoints
set style line 1 linetype 1
set style line 2 linetype 2
set style line 3 linetype 3

set title "Execution Times of Dot Product"
set xlabel "Number of Threads (t)"
set ylabel "walltime (s)"
set grid
set xrange [1:25]

plot    "terminal1000000000" using ($0+1):5 title "Serial Execution" with linespoints,\
        "terminal1000000000" using ($0+1):17 title "Reduction Pragma Parallel" with linespoints,\
        "terminal1000000000" using ($0+1):23 title "Critical Pragma Parallel" with linespoints
