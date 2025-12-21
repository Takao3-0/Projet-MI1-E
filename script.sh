#!/bin/bash

START=$(date +%s%3N)

if [ -f $1 ] && [ "$2" = "histo" ] && [ "$3" = "max" ] && [ ! $4 ];then
bash max.sh $1
elif [ -f $1 ] && [ "$2" = "histo" ] && [ "$3" = "src" ] && [ ! $4 ]; then
bash src.sh $1
elif [ -f $1 ] && [ "$2" = "histo" ] && [ "$3" = "real" ] && [ ! $4 ]; then
bash real.sh $1
elif [ -f $1 ] && [ "$2" = "histo" ] && [ "$3" = "all" ] && [ ! $4 ]; then
bash Bonusall.sh $1
#elif pour leaks

elif [ -f "$1" ] && [ "$2" = "leaks" ] && [ -n "$3" ]; then

	#LC_ALL=C awk -F ';' '$1=="-" && $2!="-" && $3!="-" && $4!="-" && $5!="-" {print $2 ";" $3 ";" $4 ";" $5}' "$1" > SourceL.txt

	#NomUsine="$3"
	#LC_ALL=C awk -F ';' -v usine="$NomUsine" '{for(i=1;i<=5;i++) gsub(/\r/,"",$i)}($1==usine && $2!="-" && $3!="-" && $4=="-" && $5!="-" )|| ($1=="-" && $2==usine && $3!="-" && $4=="-" && $5!="-" ){print $1 ";" $2 ";" $3 ";" $4 ";" $5}' "$1" > Facility.txt


	if LC_ALL=C grep -qF -- "$3" "$1"; then

		make clean
		make
		echo "Usine existante"
		LC_ALL=C awk -F ';' '$1=="-" && $2!="-" && $3!="-" && $4!="-" && $5!="-" {print $2 ";" $3 ";" $4 ";" $5}' "$1" > SourceL.txt
		NomUsine="$3"
		LC_ALL=C awk -F ';' -v usine="$NomUsine" '{for(i=1;i<=5;i++) gsub(/\r/,"",$i)}($1==usine && $2!="-" && $3!="-" && $4=="-" && $5!="-" )|| ($1=="-" && $2==usine && $3!="-" && $4=="-" && $5!="-" ){print $1 ";" $2 ";" $3 ";" $4 ";" $5}' "$1" > Facility.txt

		VAL1=$(date +%s%3N)
		#valgrind --leak-check=full --show-leak-kinds=all ./wildwater "$1" leaks "$3" Facility.txt SourceL.txt
		./wildwater "$1" leaks "$3" Facility.txt SourceL.txt
		VAL2=$(date +%s%3N)
		echo "Execution du C + verification fuite avec Valgrind: $((VAL2 - VAL1)) ms"

	else
		make clean

    	echo "Nom d'usine incorrect"
		echo "$3;-1" >> returnleaks.dat
	fi
else
	echo "Argument incorrect"
fi

END=$(date +%s%3N)
echo "Durée : $((END-START)) ms"
exit 0


