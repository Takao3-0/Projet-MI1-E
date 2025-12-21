#!/bin/bash

awk -F ';' -v OFS=';' '$1=="-" && $2!="-" && $3=="-" && $4!="-" && $5=="-" {print $2, $4}' $1 > Usine.txt

gnuplot << EOF
set datafile separator ";"
set terminal pngcairo size 1920,1080
set output "histogram_max50.png"
set title "histomax"
set ylabel "k.m^3.year^{-1}"
set style data histograms
set style fill solid 1.0 border -1
set xtics rotate by 60 right
plot "< sort -t';' -k2,2n Usine.txt 2>/dev/null | head -n 50" using 2:xtic(1) title "Donnees"
EOF


gnuplot << EOF
set datafile separator ";"
set terminal pngcairo size 1920,1080
set output "histogram_max10.png"
set title "histomax"
set ylabel "k.m^3.year^{-1}"
set style data histograms
set style fill solid 1.0 border -1
set xtics rotate by 60 right
plot "< sort -t';' -k2,2n Usine.txt 2>/dev/null | tail -n 10" using 2:xtic(1) title "Donnees"
EOF

echo "Histogrammes générés : histogram_max10.png et histogram_max50.png"
