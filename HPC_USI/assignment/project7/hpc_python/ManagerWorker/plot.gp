set title "Executed Time"
set xlabel "Number of threads"
set ylabel "Time"
set grid

set terminal postscript color "Helvetica" 14
set output "pic100.ps"
set xrange [1:16]
set grid

plot "out_100" using 1:4 title "time" with linespoints