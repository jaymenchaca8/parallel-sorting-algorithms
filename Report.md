# Parallel Computing CSCE 435 Group 4 Project

## 1a. Group members _(due 10/27)_
1. Giovanni Benitez
2. Logan Bostick
3. Samuel Mahan
4. Jay Menchaca

## 1b. Group Logistics

Primary communication form will be a group chat in GroupMe, secondary will be meetings via Zoom.

---

## 2a. Project topic _(due 11/3)_

A comparison of different sorting algorithms and how well they parallelize across GPU & CPU.



## 2b. Project Description (due 11/3)

We will be testing three different sorting algorithms to see how they strongly & weakly scale.

- Parallel Bubble Sort (MPI)
- Parallel Bubble Sort (MPI + CUDA)
- Parallel Merge Sort (MPI)
- Parallel Merge Sort (MPI + CUDA)
- Parallel Hyper Quick Sort (MPI)
- Parallel Hyper Quick Sort (MPI + CUDA)

---

## 3a. Pseudocode for each algorithm and implementation _(due 11/12)_

Parallel Bubble Sort  
```
Let p = the number of processes
Let n = number of elements to be sorted

Implementation where p < n (cost optimal - more than one element per process) 

Compare-split operation (performed between two processes with sorted blocks): 
1. Each process sends its block size = n/p to the other process. 
2. Each process merges the received block with its own block and only retains the appropriate half of the merged block (smaller process keeps lower block, larger process keeps the upper block). 

Note: Time required to merge two sorted blocks of n/p elements is O(n/p) 
Note: Time required for communication between the processes is O(n/p)  


Sorting Code

1. Store all input elements in an array.
2. Distribute the elements to n processes. There are p blocks distributed to the p process. Each block is of size n/p. 
3. Each process sorts its blocks elements with local sort (use the best sequential sort - quicksort or mergesort algorithm for this step (maybe std::sort?)) 
4. Odd or Even phase (start on even then alternate): 

Odd phase: Processes with an odd index in array execute the compare-split operation with even index process (to the right), processes with an even index in array  execute the compare-split operation with odd index process (to the left).

Even phase: Processes with an odd index in array execute the compare-split operation with even index process (to the left), processes with an even index in array  execute the compare-split operation with odd index process (to the right).

5. Repeat step 4 for p times - there will be p/2 Odd phases and p/2 Even phases. The values will be sorted after this. 

Source: A. Grama, A. Gupta, G. Karypis, and V. Kumar, Introduction to Parallel Computing, Second Edition 
``` 


Parallel Merge Sort with parallel recursion
```
1. Array of elements to be sorted, with a given high and low range
2. Check for multiple elements in array
3. Find midpoint of array
4. Fork a merge sort with first half (low to mid)
5. Merge sort with second half (mid to high)
6. Join
7. Merge
```

Parallel Merge Algorithm
```
1. Two or more arrays
2. A new empty array
3. Compare head of each array while all are not empty
4. Append head of array with smallest value to the new array; drop the head of the compared array
5. Return new array 

Source: Cormen, Thomas H.; Leiserson, Charles E.; Rivest, Ronald L.; Stein, Clifford (2009) [1990]. Introduction to Algorithms (3rd ed.). MIT Press and McGraw-Hill.
```



Parallel Hyper Quick Sort
```
1. Assume n numbers and p processes
2. Each process gets n/p consecutive elements
3. Select pivot
4. Broadcast pivot to every process
5. Set a greater than list in each process
6. Set a less than list in each process
7. For entry in list:
    If the entry < pivot
        Add entry to less than list
    Else:
        Add entry to greater than list.
8. Send the less than list to x processes
    Where x = floor(length of the list * (p / n + 0.5))
9. Send Greater than list to y processes
    Where y = p - x
10. Go till each process has one block 
11. Low is what is returned from x processes 
12. High is what is returned from y processes

Source: http://www.cas.mcmaster.ca/~nedialk/COURSES/4f03/Lectures/quicksort.pdf 

```
## 3b. _due 11/12_ Evaluation plan - what and how will you measure and compare

For example:
- Effective use of a GPU (play with problem size and number of threads)
- Strong scaling to more nodes (same problem size, increase number of processors)
- Weak scaling (increase problem size, increase number of processors)

---

## 4. _due 11/19_ Performance evaluation

Include detailed analysis of computation performance, communication performance.

Include figures and explanation of your analysis.

![alt text](image.jpg)

## 5. _due 12/1_ Presentation, 5 min + questions

- Power point is ok

## 6. _due 12/8_ Final Report

Example [link title](https://) to preview _doc_.