#!/bin/bash

awk -F ';' '$1=="-" && $2!="-" && $3=="-" && $4!="-" && $5=="-" {print $2 ";" $4}' wildwater.dat > Usine.txt

awk -F ';' '$1=="-" && $2!="-" && $3!="-" && $4!="-" && $5!="-" {print $2 ";" $3 ";" $4}' wildwater.dat > Source.txt

awk -F ';' '$1=="-" && $2!="-" && $3!="-" && $4!="-" && $5!="-" {print $2 ";" $3 ";" $4 ";" $5}' wildwater.dat > Real.txt


