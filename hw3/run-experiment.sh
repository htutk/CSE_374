#!/bin/bash

# Alex Htut
# CSE_374 | HW_3
# run-experiment.sh
# 04/24/2019

# throws an error if exactly 2 args
# are not given
if [ $# -ne 2 ]; then
  echo "Error: takes 2 filenames args"
  exit 1
fi

# throws an error if the second file
# given does not exist
if [ ! -e $2 ]; then
  echo "Error: $2 does not exist"
  exit 1
fi

inputFile=$2
outputFile=$1

NUM=1
totalline="$(wc -l < $inputFile)"

# use while to iterate over each line
# in inputFile
while [ $NUM -le $totalline ]; do
  currentline="$(sed "${NUM}q;d" $inputFile)"
  echo "Performing byte-size measurement on $currentline"
  byte="$(./perform-measurement.sh $currentline)"
  if [ $byte -eq 0 ]; then
    echo "...failure"
  else
    echo "...successful"
    echo "$NUM $currentline $byte" >> $outputFile 
  fi 

  NUM=$((NUM+1))
done

exit 0
