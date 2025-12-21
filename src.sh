#!/bin/bash

make clean
make

OUT="returnsrc.txt"
LC_ALL=C awk -F ';' '$1=="-" && $2!="-" && $3!="-" && $4!="-" && $5!="-" {print $2 ";" $3 ";" $4}' $1 > Source.txt 

SOURCE="code.c"
EXECUTABLE="wildwater"


if [ ! -f "$EXECUTABLE" ]; then
    echo "L'exécutable $EXECUTABLE n'existe pas. Compilation en cours..."
    gcc "$SOURCE" -o "$EXECUTABLE"

    if [ $? -ne 0 ]; then
        echo "Erreur : compilation échouée. Arrêt du script."
        exit 1
    fi
    echo "Compilation réussie."
fi

VAL1=$(date +%s%3N)
valgrind --leak-check=full --show-leak-kinds=all ./wildwater "$1" histo src Source.txt
VAL2=$(date +%s%3N)
echo "Verification fuite avec Valgrind: $((VAL2 - VAL1)) ms"
CODE_RETOUR=$?


if [ $CODE_RETOUR -eq 0 ]; then
    echo "Le programme s'est exécuté correctement."

else
    echo "Le programme a échoué avec le code retour $CODE_RETOUR."
    exit $CODE_RETOUR
fi

sort -t';' -k2,2g "$OUT" > src_sorted.tmp

head -n 50 src_sorted.tmp > src_50_small.tmp
tail -n 10 src_sorted.tmp > src_10_big.tmp

gnuplot << EOF
set datafile separator ";"
set terminal pngcairo size 1800,900
set style fill solid 1.0
set boxwidth 0.8
set grid ytics
set xtics rotate by -45

# 50 plus petites usines
set output "src_50_small.png"
set title "SRC - 50 plus petites usines"
set xlabel "Usines"
set ylabel "Volume capté (M.m3/an)"
plot "src_50_small.tmp" using 2:xtic(1) with boxes notitle

# 10 plus grandes usines
set output "src_10_big.png"
set title "SRC - 10 plus grandes usines"
set xlabel "Usines"
set ylabel "Volume capté (M.m3/an)"
plot "src_10_big.tmp" using 2:xtic(1) with boxes notitle
EOF

rm -f src_sorted.tmp src_50_small.tmp src_10_big.tmp

echo "Histogrammes générés : src_50_small.png / src_10_big.png"

make cleanexec