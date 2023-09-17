set terminal postscript color
set output "speed1024.ps"
set style data linespoints
set style line 1 linetype 1
set style line 2 linetype 2

set title "Speed(1024 x 1024)"
set xlabel "Number of Threads (t)"
set ylabel "Speed (MFlop/ss)"
set grid
set xrange [1:30]

plot "terminal_omp1024" using ($0+1):6 title "Parallel" with linespoints, \
     "terminal_seq1024" using ($0+1):6 title "Sequence" with linespoints