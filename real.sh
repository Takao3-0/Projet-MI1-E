#!/bin/bash

LC_ALL=C awk -F ';' '$1=="-" && $2!="-" && $3!="-" && $4!="-" && $5!="-" {print $2 ";" $3 ";" $4 ";" $5}' $1 > SourceL.txt

echo "Début d'execution du C:"
CURRENT1=$(date +%s%3N)
valgrind --leak-check=full --show-leak-kinds=all \
valgrind --leak-check=full --show-leak-kinds=all \
./wildwater "$1" histo real SourceL.txt
CURRENT2=$(date +%s%3N)

echo "Durée d'execution du C: $((CURRENT2 - CURRENT1)) ms"