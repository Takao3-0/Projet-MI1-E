#!/bin/bash

awk -F ';' '$2!="-" && $3!="-" && $4=="-" && $5!="-" {print $2 ";" $3 ";" $4 ";" $5}' "$1" > Facility.txt

NomUsine=$2

echo "Nom d'usine recherche :$2 "
resultat=$(awk -F ';' -v usine="$NomUsine" '$2==usine { print "Usine existe"; exit }' "$1")

if [ "$resultat" = "Usine existe" ]; then
    echo "Usine existante"
    ./wildwater "$1" leaks "$3" Facility.txt SourceL.txt
else 
    echo "Nom d'usine incorrect"
fi
