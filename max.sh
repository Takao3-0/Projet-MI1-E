#!/bin/bash

awk -F ';' '$1=="-" && $2!="-" && $3=="-" && $4!="-" && $5=="-" {print $2 ";" $4}' $1 > Usine.txt

gnuplot << EOF
set datafile separator ";"
set terminal pngcairo size 800,600
set output "histogram_max.png"
set title "histomax"
set ylabel "k.m^3.year^{-1}"
set style data histograms
set style fill solid 1.0 border -1
plot "Usine.txt" using 2:xtic(1) title "Donnees"
EOF

echo "Histogramme généré : histogram_max.png"
