#!/bin/bash
start=$(date +%s%N)

if [ -f $1 ] && [ "$2" = "histo" ] && [ "$3" = "max" ] && [ ! $4 ];then
bash max.sh $1  
elif [ -f $1 ] && [ "$2" = "histo" ] && [ "$3" = "src" ] && [ ! $4 ]; then
bash src.sh $1
elif [ -f $1 ] && [ "$2" = "histo" ] && [ "$3" = "real" ] && [ ! $4 ]; then
bash real.sh $1
elif [ -f $1 ] && [ "$2" = "leaks" ] && [ -n "$3" ];then
bash leaks.sh $1 "$3"
else
	echo "Argument incorrect"
fi

end=$(date +%s%N)
echo "Temps écoulé : $(( (end - start)/1000000 )) ms"

