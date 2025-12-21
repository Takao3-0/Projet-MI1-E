#!/bin/bash

awk -F ';' -v OFS=';' '$1=="-" && $5=="-"  {print $2, $4}' $1 > Usine.txt

sort -t';' -k2,2n Usine.txt > Usinetrie.txt


gnuplot << EOF
set datafile separator ";"
set terminal pngcairo size 1920,1080
set title "histomax"
set xlabel "Usines"
set ylabel "Volumes (M.m3/an)"
set style data histograms
set key outside
set grid ytics
set style fill solid 1.0 border -1
set xtics rotate by 60 right

set output "histogram_max50.png"
plot "< head -n 50 Usinetrie.txt" using 2:xtic(1) title "Max"

set output "histogram_max10.png"
plot "< tail -n 10 Usinetrie.txt" using 2:xtic(1) title "Max"
EOF

echo "Histogrammes générés : histogram_max10.png et histogram_max50.png"
