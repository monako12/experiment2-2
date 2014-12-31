#!/bin/sh
./bp_mo_exor 1000 | grep iteration | awk '{print $3 $6}' | sed '$d' | sed 's:,: :g' | sed '$d' > seed1000.txt
./bp_mo_exor 2000 | grep iteration | awk '{print $3 $6}' | sed '$d' | sed 's:,: :g' | sed '$d' > seed2000.txt
./bp_mo_exor 3000 | grep iteration | awk '{print $3 $6}' | sed '$d' | sed 's:,: :g' | sed '$d' > seed3000.txt
./bp_mo_exor 4000 | grep iteration | awk '{print $3 $6}' | sed '$d' | sed 's:,: :g' | sed '$d' > seed4000.txt
./bp_mo_exor 5000 | grep iteration | awk '{print $3 $6}' | sed '$d' | sed 's:,: :g' | sed '$d' > seed5000.txt
./bp_mo_exor 6000 | grep iteration | awk '{print $3 $6}' | sed '$d' | sed 's:,: :g' | sed '$d' > seed6000.txt
./bp_mo_exor 7000 | grep iteration | awk '{print $3 $6}' | sed '$d' | sed 's:,: :g' | sed '$d' > seed7000.txt
./bp_mo_exor 8000 | grep iteration | awk '{print $3 $6}' | sed '$d' | sed 's:,: :g' | sed '$d' > seed8000.txt
./bp_mo_exor 9000 | grep iteration | awk '{print $3 $6}' | sed '$d' | sed 's:,: :g' | sed '$d' > seed9000.txt
./bp_mo_exor 10000 | grep iteration | awk '{print $3 $6}' | sed '$d' | sed 's:,: :g' | sed '$d' > seed10000.txt

cat << EOF | gnuplot
set xlabel "Iterations"
set ylabel "Errors"
plot "seed1000.txt" w l , "seed2000.txt" w l , "seed3000.txt" w l
rep "seed4000.txt" w l , "seed5000.txt" w l , "seed6000.txt" w l
rep "seed7000.txt" w l , "seed8000.txt" w l , "seed9000.txt" w l
rep "seed10000.txt" w l 
set table "average.table"
rep "" smooth unique title "average"
unset table
EOF

cat average.table | grep -A 50 -n average | awk '{print $2" "$3" "$4}' | sed '1d' | sed '1d' > average_ultimate.txt

# echo "plot \"average_ultimate.txt\" w l" | gnuplot 
cat << EOF | gnuplot
set xlabel "Iterations"
set ylabel "Errors"
set xrange[0:120]
plot "average_ultimate.txt" w l
