#!/bin/bash

START=$(date +%s%3N)

if [ -f $1 ] && [ "$2" = "histo" ] && [ "$3" = "max" ] && [ ! $4 ];then
bash max.sh $1
elif [ -f $1 ] && [ "$2" = "histo" ] && [ "$3" = "src" ] && [ ! $4 ]; then
bash src.sh $1
elif [ -f $1 ] && [ "$2" = "histo" ] && [ "$3" = "real" ] && [ ! $4 ]; then
bash real.sh $1
#elif pour leaks

elif [ -f "$1" ] && [ "$2" = "leaks" ] && [ -n "$3" ]; then

	#LC_ALL=C awk -F ';' '$1=="-" && $2!="-" && $3!="-" && $4!="-" && $5!="-" {print $2 ";" $3 ";" $4 ";" $5}' "$1" > SourceL.txt

	#NomUsine="$3"
	#LC_ALL=C awk -F ';' -v usine="$NomUsine" '{for(i=1;i<=5;i++) gsub(/\r/,"",$i)}($1==usine && $2!="-" && $3!="-" && $4=="-" && $5!="-" )|| ($1=="-" && $2==usine && $3!="-" && $4=="-" && $5!="-" ){print $1 ";" $2 ";" $3 ";" $4 ";" $5}' "$1" > Facility.txt


	if LC_ALL=C grep -qF -- "$3" "$1"; then
		echo "Usine existante"
		LC_ALL=C awk -F ';' '$1=="-" && $2!="-" && $3!="-" && $4!="-" && $5!="-" {print $2 ";" $3 ";" $4 ";" $5}' "$1" > SourceL.txt

		NomUsine="$3"
		LC_ALL=C awk -F ';' -v usine="$NomUsine" '{for(i=1;i<=5;i++) gsub(/\r/,"",$i)}($1==usine && $2!="-" && $3!="-" && $4=="-" && $5!="-" )|| ($1=="-" && $2==usine && $3!="-" && $4=="-" && $5!="-" ){print $1 ";" $2 ";" $3 ";" $4 ";" $5}' "$1" > Facility.txt
		CURRENT1=$(date +%s%3N)
		#valgrind --leak-check=full --show-leak-kinds=all \
    	./wildwater "$1" leaks "$3" Facility.txt SourceL.txt
		CURRENT2=$(date +%s%3N)
		echo "Durée d'execution du C: $((CURRENT2 - CURRENT1)) ms"
	else
    	echo "Nom d'usine incorrect"
	fi
else
	echo "Argument incorrect"
fi

END=$(date +%s%3N)
echo "Durée : $((END-START)) ms"
exit 0


