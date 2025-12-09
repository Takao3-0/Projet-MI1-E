gnuplot << EOF
set terminal pngcairo size 800,600
set output "histogram.png"
set style data histograms
plot "Usine.txt" using 2:xtic(1) title "Donnes"
EOF
