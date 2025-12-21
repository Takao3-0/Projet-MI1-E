#!/bin/bash

make clean
make 

LC_ALL=C awk -F ';' -v OFS=';' '$1=="-" && $2!="-" && $3!="-" && $4!="-" && $5!="-" {print $2, $3, $4, $5}' "$1" > SourceL.txt

SOURCE="code.c"
EXECUTABLE="wildwater"
OUT="returnreal.txt"

CMD=(./wildwater "$1" histo real SourceL.txt)

if [ ! -f "$EXECUTABLE" ]; then
    echo "L'exécutable $EXECUTABLE n'existe pas. Compilation en cours..."
    gcc "$SOURCE" -o "$EXECUTABLE"

    if [ $? -ne 0 ]; then
        echo "Erreur : compilation échouée. Arrêt du script."
        exit 1
    fi
    echo "Compilation réussie."
fi
#VAL1=$(date +%s%3N)
#valgrind --leak-check=full --show-leak-kinds=all "${CMD[@]}"
#VAL2=$(date +%s%3N)
#echo "Execution du C avec verification des fuites avec Valgrind: $((VAL2 - VAL1)) ms"
CURRENT1=$(date +%s%3N)
./wildwater "$1" histo real SourceL.txt
CURRENT2=$(date +%s%3N)

echo "Durée d'execution du C: $((CURRENT2 - CURRENT1)) ms"
CODE_RETOUR=$?

if [ $CODE_RETOUR -eq 0 ]; then
    echo "Le programme s'est exécuté correctement."

else
    echo "Le programme a échoué avec le code retour $CODE_RETOUR."
    exit $CODE_RETOUR
fi

sort -t';' -k2,2g "$OUT" > real_sorted.tmp

head -n 50 real_sorted.tmp > real_50_small.tmp
tail -n 10 real_sorted.tmp > real_10_big.tmp

gnuplot << EOF
set datafile separator ";"
set terminal pngcairo size 1800,900
set style fill solid 1.0
set boxwidth 0.8
set grid ytics
set xtics rotate by -45

# 50 plus petites usines
set output "real_50_small.png"
set title "REAL - 50 plus petites usines"
set xlabel "Usines"
set ylabel "Volume capté (M.m3/an)"
plot "real_50_small.tmp" using 2:xtic(1) with boxes notitle

# 10 plus grandes usines
set output "real_10_big.png"
set title "REAL - 10 plus grandes usines"
set xlabel "Usines"
set ylabel "Volume capté (M.m3/an)"
plot "real_10_big.tmp" using 2:xtic(1) with boxes notitle
EOF

rm -f real_sorted.tmp real_50_small.tmp real_10_big.tmp

echo "Histogrammes générés : real_50_small.png / real_10_big.png"

make cleanexec