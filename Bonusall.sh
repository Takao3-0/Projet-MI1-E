#!/bin/bash

make clean
make 

LC_ALL=C awk -F ';' '$1=="-" && $2!="-" && $3!="-" && $4!="-" && $5!="-" {print $2 ";" $3 ";" $4}' $1 > Source.txt 
LC_ALL=C awk -F ';' -v OFS=';' '$1=="-" && $2!="-" && $3!="-" && $4!="-" && $5!="-" {print $2, $3, $4, $5}' "$1" > SourceL.txt
LC_ALL=C awk -F ';' '$1=="-" && $2!="-" && $3=="-" && $4!="-" && $5=="-" {print $2 ";" $4}' $1 > Usine.txt

SOURCE="code.c"
EXECUTABLE="wildwater"
OUT="returnall.txt"

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
#valgrind --leak-check=full --show-leak-kinds=all ./wildwater "$1" histo all Usine.txt SourceL.txt Source.txt
#VAL2=$(date +%s%3N)
#echo "Execution du C avec verification des fuites avec Valgrind: $((VAL2 - VAL1)) ms"
CURRENT1=$(date +%s%3N)
./wildwater "$1" histo real SourceL.txt
CURRENT2=$(date +%s%3N)

#echo "Durée d'execution du C: $((CURRENT2 - CURRENT1)) ms"
CODE_RETOUR=$?

if [ $CODE_RETOUR -eq 0 ]; then
    echo "Le programme s'est exécuté correctement."

else
    echo "Le programme a échoué avec le code retour $CODE_RETOUR."
    exit $CODE_RETOUR
fi


sort -t';' -k2,2g "$OUT" > Ball_sorted.tmp

# On calcule: Bleu=REAL, Rouge=SRC-REAL, Vert=MAX-SRC
awk -F';' -v OFS=';' '
  $2 ~ /^[0-9.]+$/ && $3 ~ /^[0-9.]+$/ && $4 ~ /^[0-9.]+$/ {
    bleu=$4;
    rouge=$3-$4;
    vert=$2-$3;
    if (rouge < 0) rouge=0;
    if (vert  < 0) vert=0;
    print $1, bleu, rouge, vert
  }' Ball_sorted.tmp > Ball_stack.tmp

head -n 50 Ball_stack.tmp > Ball_50_small.tmp
tail -n 10 Ball_stack.tmp > Ball_10_big.tmp


gnuplot << 'EOF'
set datafile separator ";"
set terminal pngcairo size 1800,900
set style data histograms
set style histogram rowstacked
set style fill solid 1.0 border -1
set boxwidth 0.8
set grid ytics
set key outside
set xtics rotate by -45

# 50 plus petites
set output "Ball_50_small.png"
set title "ALL - 50 plus petites usines"
set xlabel "Usines"
set ylabel "Volumes (M.m3/an)"
plot "Ball_50_small.tmp" using 2:xtic(1) title "Traité ", \
     ""                 using 3           title "Perdu", \
     ""                 using 4           title "Inutilisé (Vol. Max)"

# 10 plus grandes
set output "Ball_10_big.png"
set title "ALL - 10 plus grandes usines"
plot "Ball_10_big.tmp" using 2:xtic(1) title "Traité (REAL)", \
     ""                using 3           title "Perdu", \
     ""                using 4           title "Inutilisé (Vol. Max)"
EOF


rm -f Ball_sorted.tmp Ball_stack.tmp Ball_50_small.tmp Ball_10_big.tmp
echo "Histogrammes générés : Ball_50_small.png / Ball_10_big.png"
