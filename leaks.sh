#!/bin/bash

NomUsine="$2"
if grep -q "^.*;$NomUsine;.*;.*;-$" "$1"; then
    echo "Usine existante"
    awk -F';' -v OFS=';' -v usine="$NomUsine" '($1==usine || $2==usine) && $4=="-" && $5!="" {print $1, $2, $3, "-", $5 > "Facility.txt"} $1=="-" && $2!="" && $3!="" && $4!="" && $5!="" {print $2, $3, $4, $5 > "SourceL.txt"}' "$1"
	./wildwater "$1" leaks "$NomUsine" Facility.txt SourceL.txt
else
    echo "Nom d'usine incorrect"
fi
