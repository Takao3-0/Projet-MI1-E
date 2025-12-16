#!/bin/bash

awk -F ';' '$1=="-" && $2!="-" && $3!="-" && $4!="-" && $5!="-" {print $2 ";" $3 ";" $4 ";" $5}' $1 > Real.txt

./wildwater script.sh $1 histo real Real.txt

gnuplot << EOF
set datafile separator ";"
set terminal pngcairo size 800,600
set output "histogram_real.png"
set title "historeal"
set ylabel "k.m^3.year^{-1}"
set style data histograms
set style fill solid 1.0 border -1
plot "returnreal.txt" using 2:xtic(1) title "Donnes"
EOF

echo "Histogramme généré : histogram_real.png"
