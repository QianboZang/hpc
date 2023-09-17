set terminal postscript color
set output "time1024.ps"
set style data linespoints
set style line 1 linetype 1
set style line 2 linetype 2

set title "Execution Times of Mandel(1024 x 1024)"
set xlabel "Number of Threads (t)"
set ylabel "Total Time (s)"
set grid
set xrange [1:30]

plot "terminal_omp1024" using ($0+1):3 title "Parallel" with linespoints, \
     "terminal_seq1024" using ($0+1):3 title "Sequence" with linespoints