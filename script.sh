#!/bin/bash

START=$(date +%s%3N)

if [ -f $1 ] && [ "$2" = "histo" ] && [ "$3" = "max" ] && [ ! $4 ];then
bash max.sh $1  
elif [ -f $1 ] && [ "$2" = "histo" ] && [ "$3" = "src" ] && [ ! $4 ]; then
bash src.sh $1
elif [ -f $1 ] && [ "$2" = "histo" ] && [ "$3" = "real" ] && [ ! $4 ]; then
bash real.sh $1
#elif pour leaks

elif [ -f $1 ] && [ "$2" = "leaks" ] && [ -n "$3" ] && [ -z "$4" ]; then
	awk -F ';' '$1=="-" && $2!="-" && $3!="-" && $4!="-" && $5!="-" {print $2 ";" $3 ";" $4 ";" $5}' $1 > SourceL.txt
	awk -F ';' '$1=="-" && $2!="-" && $3=="-" && $4!="-" && $5=="-" {print $2 ";" $4}' $1 > Usine.txt

	./wildwater "$1" leaks "$3" Usine.txt SourceL.txt

else
	echo "Argument incorrect"
fi

END=$(date +%s%3N)
echo "Durée : $((END-START)) ms"
exit 0


