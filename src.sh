#!/bin/bash

awk -F ';' '$1=="-" && $2!="-" && $3!="-" && $4!="-" && $5!="-" {print $2 ";" $3 ";" $4}' $1 > Source.txt 
awk -F ';' '$1=="-" && $2!="-" && $3=="-" && $4!="-" && $5=="-" {print $2 ";" $4}' $1 > Usine.txt

./wildwater script.sh $1 histo src Usine.txt

gnuplot << EOF
set datafile separator ";"
set terminal pngcairo size 800,600
set output "histogram_src.png"
set title "histosrc"
set ylabel "k.m^3.year^{-1}"
set style data histograms
set style fill solid 1.0 border -1
plot "returnsrc.txt" using 2:xtic(1) title "Donnes" 
EOF

echo "Histogramme généré : histogram_src.png"
