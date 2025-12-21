#!/bin/bash

awk -F';' -v OFS=';' '$1=="-" && $2!="" && $3!="" && $4!="" && $5!="" {print $2, $3, $4 > "Source.txt" print $2, $3, $4, $5 > "SourceL.txt"}' "$1"

./wildwater "$1" histo all Source.txt SourceL.txt


