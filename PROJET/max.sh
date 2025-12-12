#!/bin/bash
if [ "$1" = "wildwater.dat" ] && [ "$2" = "histo" ] && [ "$3" = "max" ] || [ "$3" = "src" ];then
if [ "$1" = "wildwater.dat" ] && [ "$2" = "histo" ] && [ "$3" = "max" ]; then

gnuplot << EOF
set datafile separator ";"
set terminal pngcairo size 800,600
set output "histogram.png"
set title "histomax"
set style data histograms
set style fill solid 1.0 border -1
plot "Usine.txt" using 2:xtic(1) title "Donnes"
EOF

echo "Histogramme généré : histogram.png"

fi


if [ "$1" = "wildwater.dat" ] && [ "$2" = "histo" ] && [ "$3" = "src" ]; then

gnuplot << EOF
set datafile separator ";"
set terminal pngcairo size 800,600
set output "histogram.png"
set title "histomax"
set style data histograms
set style fill solid 1.0 border -1
plot "Usine.txt" using 2:xtic(1) title "Donnes"
EOF

echo "Histogramme généré : histogram.png"

fi

else
	echo "Argument incorrect"
fi
