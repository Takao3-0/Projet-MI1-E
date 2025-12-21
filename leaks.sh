#!/bin/bash

awk -F';' -v OFS=';' -v usine="$NomUsine" '($1==usine || $2==usine) && $4=="-" && $5!="" {print $1, $2, $3, "-", $5 > "Facility.txt"} $1=="-" && $2!="" && $3!="" && $4!="" && $5!="" {print $2, $3, $4, $5 > "SourceL.txt"}' "$1"

NomUsine=$2
if if grep -q "^.*;$NomUsine;.*;.*;-$" "$1"; then
    echo "Usine existante"
	#./wildwater "$1" rajouter les fichier pour alex
else
    echo "Nom d'usine incorrect"
fi
