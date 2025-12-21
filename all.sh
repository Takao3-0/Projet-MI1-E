#!/bin/bash

awk -F';' -v OFS=';' '$1=="-" && $2!="" && $3!="" && $4!="" && $5!="" {print $2, $3, $4 > "Source.txt" print $2, $3, $4, $5 > "SourceL.txt"}' "$1"

./wildwater "$1" histo all Source.txt SourceL.txt


gnuplot << EOF
set datafile separator ";"
set terminal pngcairo size 1920,1080
set output "histogram_all50.png"
set title "histoall"
set ylabel "k.m^3.year^{-1}"
set style data histograms
set style fill solid 1.0 border -1
set xtics rotate by 60 right
plot "< sort -t';' -k2,2n returnall.txt 2>/dev/null | head -n 50" using 2:xtic(1) title "Donnees"
EOF

gnuplot << EOF
set datafile separator ";"
set terminal pngcairo size 1920,1080
set output "histogram_all10.png"
set title "histoall"
set ylabel "k.m^3.year^{-1}"
set style data histograms
set style fill solid 1.0 border -1
set xtics rotate by 60 right
plot "< sort -t';' -k2,2n returnall.txt 2>/dev/null | tail -n 10" using 2:xtic(1) title "Donnees"
EOF

echo "Histogrammes générés : histogram_all10.png et histogram_all50.png"
