#!/bin/bash

# Alex Htut
# CSE_374 | HW_3
# perform-measurement.sh
# 04/24/2019

# throws an error if exactly 1 arg
# is not given
if [ $# -ne 1 ]; then
  echo "Error: must provide a single URL" 1>&2
  exit 1
fi

url=$1

mkdir ./tmp/
cd ./tmp/

wget -q --timeout=1 --tries=2 $url

# count the number of files in tmp/
# if 0 -> error
num_of_file="$(ls -1 | wc -l)"

if [ $num_of_file -eq 1 ]; then
  echo "$(wc -c < ./*)"
elif [ $num_of_file -eq 0 ]; then
  echo "0"
fi

cd ../
rm -r ./tmp/

exit 0

