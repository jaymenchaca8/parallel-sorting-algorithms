#!/bin/bash

# BaSH Script File for CSCE 435 Parallel Computing
# Team 4
# Fall 2021
# Used to create mulitple arrays

for size in 65536 1048576 16777216
  do
    python randomGenerator.py -n $size -o rand_$size.txt -r $size
    python onePercentPerturb.py -n $size -o one_perturb_$size.txt -r $size
    python sortedGenerator.py -n $size -o sorted_$size.txt -r $size
    python reverseSortedGenerator.py -n $size -o reverse_$size.txt -r $size
  done