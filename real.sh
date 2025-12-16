#!/bin/bash

awk -F ';' '$1=="-" && $2!="-" && $3!="-" && $4!="-" && $5!="-" {print $2 ";" $3 ";" $4 ";" $5}' $1 > Real.txt
#appeler le c et avoir un ficier avec que 2 valeur #changer le "Real.txt" l.12
gnuplot << EOF
set datafile separator ";"
set terminal pngcairo size 800,600
set output "histogram_real.png"
set title "historeal"
set ylabel "k.m^3.year^{-1}"
set style data histograms
set style fill solid 1.0 border -1
plot "Real.txt" using 2:xtic(1) title "Donnes"
EOF

echo "Histogramme généré : histogram_real.png"
