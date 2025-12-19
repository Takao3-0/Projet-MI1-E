#!/bin/bash

awk -F ';' '$1=="-" && $2!="-" && $3!="-" && $4!="-" && $5!="-" {print $2 ";" $3 ";" $4 ";" $5}' $1 > SourceL.txt
awk -F ';' '$1=="-" && $2!="-" && $3=="-" && $4!="-" && $5=="-" {print $2 ";" $4}' $1 > Usine.txt

./wildwater "$1" leaks "$3" Usine.txt SourceL.txt