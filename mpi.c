#include <stdio.h>
#include <mpi.h>
#include <time.h>
#include <stdlib.h>

#define ARRAY_SIZE 16;

//void launch_kernel();

void merge(int *A, int *B, int left, int mid, int right){
    int h = left;
    int i = left;
    int j = mid + 1;
    int iter;
    
    while((h <= mid) && (j <= right)){
        if(A[h] <= A[j]){
            B[i] = A[h];
            h++;
        }
        else{
            B[i] = A[j];
            j++;
        }
        i++;
    }
    
    if(mid < h){
        for(iter = j; iter <= right; iter++){
            B[i] = A[iter];
            i++;
        }
    }
    else{
        for(iter = h; iter <= mid; iter++){
            B[i] = A[iter];
            i++;
        }
    }
    
    for(iter = left; iter <= right; iter++){
        A[iter] = B[iter];
    }
}

void mergeSort(int *A, int *B, int left, int right){
    int mid;
    
    if(left < right){
        mid = (left + right) / 2;
        mergeSort(A, B, left, mid);
        mergeSort(A, B, (mid + 1), right);
        merge(A, B, left, mid, right);
    }
}

int main(argc, argv)
int argc;
char **argv;
{
    double commTime = 0;
    double gathTime = 0;
    double totTime = 0;
    
    int arraySize = ARRAY_SIZE;
    int arrayType = 0;
    
    if(argc == 4){                  //.exe file arraysize arraytype
        arraySize = atoi(argv[2]);
        arrayType = atoi(argv[3]);
    }
    else{
        printf("args not right");
        exit(-1);
    }
    
    int* unsortedArray = malloc(arraySize * sizeof(int));
    
    //scan file and collect array
    FILE *file = fopen(argv[1],"r");
    
    fscanf(file, "%d", &arraySize);
    
    for(int i = 0; i < arraySize; i++){
        fscanf(file, "%d", &unsortedArray[i]);
    }
    
    fclose(file);
    file = NULL;
    
    //create array of random numbers
    /*
    srand(time(NULL));
    for(int i = 0; i < arraySize; i++){
        unsortedArray[i] = rand() % arraySize;
        printf("%d ", unsortedArray[i]);
    }
    printf("\n");
    */
    
   int rank, size;
   MPI_Init(&argc,&argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   
   int splitSize = arraySize/size;
   
   //send equal chunks of the unsorted array 
   int* splitArray = malloc(splitSize * sizeof(int));
   
   //sorting starts here
   //comm starts
   if(rank == 0){
       totTime = MPI_Wtime();
       commTime = MPI_Wtime();
   }
   
   MPI_Scatter(unsortedArray, splitSize, MPI_INT, splitArray, splitSize, MPI_INT, 0, MPI_COMM_WORLD);
   
   if(rank == 0){
       commTime = MPI_Wtime() - commTime;
   }
   //comm ends
   
   //print to see how the numbers are divided up
   /*
   for(int i = 0; i < splitSize; i++){
       printf("(%d, %d) ", splitArray[i], rank);
   }
   printf("\n");
   */
   
   int* tempArray = malloc(splitSize * sizeof(int));
   mergeSort(splitArray, tempArray, 0, splitSize - 1);
   
   int* sortedArray = NULL;
   
   if(rank == 0){
       sortedArray = malloc(arraySize * sizeof(int));
       gathTime = MPI_Wtime();
   }
   
   //get all split arrays back into a single array
   //comm starts
   MPI_Gather(splitArray, splitSize, MPI_INT, sortedArray, splitSize, MPI_INT, 0, MPI_COMM_WORLD);
   
   if(rank == 0){
       gathTime = MPI_Wtime() - gathTime;
   }
   //comm ends
   //collect the last merge sort
   if(rank == 0){
       int* bArray = malloc(arraySize * sizeof(int));
       mergeSort(sortedArray, bArray, 0, arraySize - 1);
       
       totTime = MPI_Wtime() - totTime;
       commTime = commTime + gathTime;
       //sorting finishes here
       
       /*
       for(int i = 0; i < arraySize; i++){
           printf("%d ", sortedArray[i]);
       }
       printf("\n");
       */
       //number of processes
       printf("%d, ", size);
       //algorithm - merge mpi -> 2
       printf("%d, ", 2);
       //array type
       printf("%d, ", arrayType);
       //array size
       printf("%d, ", arraySize);
       //total time
       printf("%f, ", totTime); //in seconds
       //communication time
       printf("%f ", commTime);
       printf("\n");
       
       free(sortedArray);
       free(bArray);
   }
   
   free(unsortedArray);
   free(splitArray);
   free(tempArray);
   
   //launch_kernel();
   MPI_Barrier(MPI_COMM_WORLD);
   MPI_Finalize();
   return 0;
}

