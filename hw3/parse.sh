#!/bin/bash

# Alex Htut
# CSE_374 | HW_3
# parse.sh
# 04/24/2019

# throws an error if exactly 2 args
# are not given
if [ $# -ne 2 ]; then
  echo "Error: please provide two files; 1st for output; 2nd for input"
  exit 1
fi

# throws an error if the second file
# does not exist
if [ ! -e $2 ]; then
  echo "Error: $2 does not exits."
  exit 1
fi

outFile=$1
inFile=$2

# grep the urls from inFile
urls="$(grep '<strong><a href="\(.*\)">.*' $inFile)"
echo "$urls" > $outFile

# use HTMLs tags to identify the appropriate urls
sed -i 's_.*<a href="__g' $outFile 
sed -i 's_">.*__g' $outFile

exit 0
