#!/bin/bash

LC_ALL=C awk -F ';' '$1=="-" && $2!="-" && $3!="-" && $4!="-" && $5!="-" {print $2 ";" $3 ";" $4}' $1 > Source.txt 

echo "Début d'execution du C:"
CURRENT1=$(date +%s%3N)
./wildwater "$1" histo src Source.txt
CURRENT2=$(date +%s%3N)

echo "Durée d'execution du C: $((CURRENT2 - CURRENT1)) ms"