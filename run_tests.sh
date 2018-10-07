#!/bin/bash

FILES=$(find . -name "*.col")

N_TIMES=$1

make

for f in $FILES
do
  echo "Processing file $f..."
  ./tp $f $N_TIMES	
  echo -e "\n"
done
