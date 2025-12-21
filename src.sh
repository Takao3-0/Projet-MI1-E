#!/bin/bash

awk -F ';' -v OFS=';' '$1=="-" && $2!="-" && $3!="-" && $4!="-" && $5!="-" {print $2, $3, $4}' "$1" > Source.txt 

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

./wildwater "$1" histo src Source.txt
CODE_RETOUR=$?


if [ $CODE_RETOUR -eq 0 ]; then
    echo "Le programme s'est exécuté correctement."

else
    echo "Le programme a échoué avec le code retour $CODE_RETOUR."
    exit $CODE_RETOUR
fi

sort -t';' -k2,2n returnsrc.txt > srctrie.txt

gnuplot << EOF
set datafile separator ";"
set terminal pngcairo size 1920,1080
set title "histosrc"
set xlabel "Usines"
set ylabel "Volumes (M.m3/an)"
set style data histograms
set key outside
set grid ytics
set style fill solid 1.0 border -1
set xtics rotate by 60 right

set output "histogram_src50.png"
plot "< head -n 50 srctrie.txt" using 2:xtic(1) title "Volume"

set output "histogram_src10.png"
plot "< tail -n 10 srctrie.txt" using 2:xtic(1) title "Volume"
EOF

echo "Histogrammes générés : histogram_src10.png et histogram_src50.png"

