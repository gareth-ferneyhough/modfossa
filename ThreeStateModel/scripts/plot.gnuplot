# Plot solution

#set terminal epslatex size 5in,3in
#set output "channel_plot.tex"
set grid
set format y "%.1f"
set format x "%.0f"
set title "pC1(red), pC2(blue), pO(green)
set xlabel "Time (ms)"
set ylabel "Prob"
set nokey

plot "result.txt" using 1 with lines lw 1, "result.txt" using 2 with lines lw 1 linecolor rgb "blue", "result.txt" using 3 with lines lw 1 linecolor rgb "green"

pause -1