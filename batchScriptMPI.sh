#!/bin/bash

# BaSH Script File for CSCE 435 Parallel Computing
# Team 4
# Fall 2021

# Number of of processes / cores 
# 1, 2, 4, 8, 16 ......

# Sorting Alg
# 0 Bubble (MPI)
# 1 Buffle (CUDA)
# 2 Merge (MPI)
# 3 Merge (CUDA)
# 4 HQuick (MPI)
# 5 HQuick (CUDA)


# Input type
# 0 Random
# 1 1% Perturb
# 2 Already Sorted
# 3 Reversed


# Input size
# 0 65,536 (2^16)
# 1 1,048,576 (2^20)
# 2 16,777,216 (2^24)
# Values > 2 are pending inital data review
# 3 268,435,456 (2^28)
# 4 4,294,967,296 (2^32)

# Total time, Calculation Time, Communication Time

# Variables
Alg=2
Input0=0
Input1=1
Input2=2
Input3=3

#Size0=1024
#Size1=2048
#Size2=4096
Size0=65536
Size1=1048576
Size2=16777216
Size3=268435456
Size4=4294967296

for cores in 1 2 4 8
  do
    for sampleSize in $Size0 $Size1 $Size2
      do
        echo "Threads: "$cores" Elements: "$sampleSize
        mpirun -np $cores ./mpi_merge.exe rand_$sampleSize.txt $sampleSize 0 >& output.p$cores.s$sampleSize.0
        mpirun -np $cores ./mpi_merge.exe one_perturb_$sampleSize.txt $sampleSize 1 >& output.p$cores.s$sampleSize.1
        mpirun -np $cores ./mpi_merge.exe sorted_$sampleSize.txt $sampleSize 2 >& output.p$cores.s$sampleSize.2
        mpirun -np $cores ./mpi_merge.exe reverse_$sampleSize.txt $sampleSize 3 >& output.p$cores.s$sampleSize.3
      done
  done

