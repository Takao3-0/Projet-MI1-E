#!/bin/bash

awk -F';' -v OFS=';' '$1=="-" && $2!="" && $3!="" && $4!="" && $5!="" {print $2, $3, $4 > "Source.txt"; print $2, $3, $4, $5 > "SourceL.txt"}' "$1"

SOURCE="code.c"
EXECUTABLE="wildwater"
make 

if [ ! -f "$EXECUTABLE" ]; then
    echo "L'exécutable $EXECUTABLE n'existe pas. Compilation en cours..."
    gcc "$SOURCE" -o "$EXECUTABLE"

    if [ $? -ne 0 ]; then
        echo "Erreur : compilation échouée. Arrêt du script."
        exit 1
    fi
    echo "Compilation réussie."
fi
./wildwater "$1" histo all Source.txt SourceL.txt

CODE_RETOUR=$?

if [ $CODE_RETOUR -eq 0 ]; then
    echo "Le programme s'est exécuté correctement."

else
    echo "Le programme a échoué avec le code retour $CODE_RETOUR."
    exit $CODE_RETOUR
fi

sort -t';' -k2,2n returnall.txt > alltrie.txt

gnuplot << EOF
set datafile separator ";"
set terminal pngcairo size 1920,1080
set title "histoall"
set ylabel "k.m^3.year^{-1}"
set style data histograms
set style fill solid 1.0 border -1
set xtics rotate by 60 right

set output "histogram_all50.png"
plot "< head -n 50 alltrie.txt" using 2:xtic(1) title "Donnees"

set output "histogram_all10.png"
plot "< tail -n 10 alltrie.txt" using 2:xtic(1) title "Donnees"
EOF

echo "Histogrammes générés : histogram_all10.png et histogram_all50.png"



sort -t';' -k2,2n returnall.txt > alltrie.txt

gnuplot << EOF
set datafile separator ";"
set terminal pngcairo size 1920,1080
set title "histoall"
set xlabel "Usines"
set ylabel "Volumes (M.m3/an)"
set style data histograms
set style histogram rowstacked
set style histogram clustered gap 1
set style fill solid 1.0 border -1
set boxwidth 0.7
set grid ytics
set key outside
set xtics rotate by 60 right
set style line 1 lc rgb "#00AA00"  # max -> vert
set style line 2 lc rgb "#FF0000"  # src -> rouge
set style line 3 lc rgb "#0000FF"  # real -> bleu


set output "histogram_all50.png"
plot "< tail -n 50 alltrie.txt" using 2:xtic(1) title "Max" ls 1, \ "" using 3 title "Perdu" ls 2, \ "" using 4 title "Traitée" ls 3

set output "histogram_all10.png"
plot "< head -n 10 alltrie.txt" using 2:xtic(1) title "Max" ls 1, \ "" using 3 title "Perdu" ls 2, \ "" using 4 title "Traitée" ls 3
EOF
