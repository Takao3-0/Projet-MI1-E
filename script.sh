#!/bin/bash


if [ -f $1 ] && [ "$2" = "histo" ] && [ "$3" = "max" ];then
bash max.sh $1  
elif [ -f $1 ] && [ "$2" = "histo" ] && [ "$3" = "src" ]; then
bash src.sh $1
# elif [ -f $1 ] && [ "$2" = "histo" ] && [ "$3" = "real" ]; then
#bash real.sh $1
#elif pour leaks

else
	echo "Argument incorrect"
fi


