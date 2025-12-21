#!/bin/bash

awk -F';' -v OFS=';' '$4=="-" && $1!="-" && $2!="-" && $3!="-" && $5!="-" {print $2, $3, "-", $5}' "$1" > Facility.txt
NomUsine=$2
if awk -F';' -v usine="$NomUsine" '$5=="-" && $2==usine { exit 0 } END { exit 1 }' "$1"; then
echo "Usine existante"
#./wildwater "$1" rajouter les fichier pour alex
else 
	echo "Nom d'usine incorrect"
fi




