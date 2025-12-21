#!/bin/bash

make clean
make 

OUT="returnmax.txt"

LC_ALL=C awk -F ';' '$1=="-" && $2!="-" && $3=="-" && $4!="-" && $5=="-" {print $2 ";" $4}' $1 > Usine.txt

VAL1=$(date +%s%3N)
valgrind --leak-check=full --show-leak-kinds=all ./wildwater "$1" histo max Usine.txt
#./wildwater "$1" histo max Usine.txt
VAL2=$(date +%s%3N)
echo "Verification fuite avec Valgrind: $((VAL2 - VAL1)) ms"


sort -t';' -k2,2g "$OUT" > max_sorted.tmp

head -n 50 max_sorted.tmp > max_50_small.tmp
tail -n 10 max_sorted.tmp > max_10_big.tmp

gnuplot << EOF
set datafile separator ";"
set terminal pngcairo size 1800,900
set style fill solid 1.0
set boxwidth 0.8
set grid ytics
set xtics rotate by -45

# 50 plus petites usines
set output "max_50_small.png"
set title "MAX - 50 plus petites usines"
set xlabel "Usines"
set ylabel "Volume capté (M.m3/an)"
plot "max_50_small.tmp" using 2:xtic(1) with boxes notitle

# 10 plus grandes usines
set output "max_10_big.png"
set title "MAX - 10 plus grandes usines"
set xlabel "Usines"
set ylabel "Volume capté (M.m3/an)"
plot "max_10_big.tmp" using 2:xtic(1) with boxes notitle
EOF

rm -f max_sorted.tmp max_50_small.tmp max_10_big.tmp

echo "Histogrammes générés : max_50_small.png / max_10_big.png"
