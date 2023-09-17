set title "Efficent"
set xlabel "Number of Processes (p)"
set ylabel "Rate"
set grid
set yrange [0.48: 1.1]

set terminal postscript color "Helvetica" 14
set output "eff.ps"

plot "result2" using 1:4 title "result" with linespoints, \