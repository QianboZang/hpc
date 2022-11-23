set terminal postscript color
set output "parsim1024.ps"
set style data linespoints
set style line 1 linetype 1
set style line 2 linetype 2

set title "Performance"
set xlabel "Number of Threads (t)"
set ylabel "running time (s)"
set grid
set xrange [1:24]

plot    "t_sim1024" using ($0+1):3 title "Simd" with linespoints,\
        "t_par1024" using ($0+1):3 title "Parallel" with linespoints
