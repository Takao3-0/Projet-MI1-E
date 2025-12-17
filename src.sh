#!/bin/bash

awk -F ';' '$1=="-" && $2!="-" && $3!="-" && $4!="-" && $5!="-" {print $2 ";" $3 ";" $4}' $1 > Source.txt 
awk -F ';' '$1=="-" && $2!="-" && $3=="-" && $4!="-" && $5=="-" {print $2 ";" $4}' $1 > Usine.txt

./wildwater "$1" histo src Usine.txt Source.txt