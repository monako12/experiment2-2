set xlabel "iteration"
set ylabel "error"
set title "Error transition per iteration on BP-NN"
set terminal svg
set output "result-seed100.svg"
plot "result-seed100.data" with line
