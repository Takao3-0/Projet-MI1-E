#!/bin/bash

awk -F ';' -v OFS=';' '$1=="-" && $2!="-" && $3!="-" && $4!="-" && $5!="-" {print $2, $3, $4, $5}' "$1" > SourceL.txt

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

./wildwater "$1" histo real SourceL.txt
CODE_RETOUR=$?

if [ $CODE_RETOUR -eq 0 ]; then
    echo "Le programme s'est exécuté correctement."

else
    echo "Le programme a échoué avec le code retour $CODE_RETOUR."
    exit $CODE_RETOUR
fi

sort -t';' -k2,2n returnreal.txt > realtrie.txt

gnuplot << EOF
set datafile separator ";"
set terminal pngcairo size 1920,1080
set title "historeal"
set xlabel "Usines"
set ylabel "Volumes (M.m3/an)"
set style data histograms
set key outside
set grid ytics
set style fill solid 1.0 border -1
set xtics rotate by 60 right

set output "histogram_real50.png"
plot "< head -n 50 realtrie.txt" using 2:xtic(1) title "Volume réel"

set output "histogram_real10.png"
plot "< tail -n 10 realtrie.txt" using 2:xtic(1) title "Volume réel"
EOF

echo "Histogrammes générés : histogram_real10.png et histogram_real50.png"
