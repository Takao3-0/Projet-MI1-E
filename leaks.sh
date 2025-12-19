#!/bin/bash

awk -F ';' '$1!="-" && $2!="-" && $3!="-" && $4=="-" && $5!="-" {print $2 ";" $3 ";" $4 ";" $5}' $1 > Facility.txt

NomUsine=$2
resultat=$(awk -F ';' -v usine="$NomUsine" '$5=="-" && $2==usine { print "Usine existe" }' "$1") 
if [ "$resultat" = "Usine existe" ];then
echo "Usine existante"
#./wildwater "$1" rajouter les fichier pour alex
else 
	echo "Nom d'usine incorrect"
fi
