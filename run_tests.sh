#!/bin/bash

FILES=$(find . -name "*.col")

N_TIMES=$1

make

printf "file,rand,ldf,snt,lnt\n" >out.csv

for f in $FILES
do
  echo "Processing file $f..."
  printf "%s," "$(basename $f)"	>>out.csv
  ./tp $f $N_TIMES >>out.csv
done
