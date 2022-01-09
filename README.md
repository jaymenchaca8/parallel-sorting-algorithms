# csce435project
## Fall 2021 - Team 4

Merge MPI

	module load intel/2020b
	
	mpicc -o mpi_merge.exe mpi.c

	mpirun -np #n ./mpi_merge.exe #a.txt #s #t
	
		#n - number of threads
		#a.txt - text file with array list (see python files for how it is generated)
		#s - size of array
		#t - input type (see batch files)
	
	(For grace job)   sbatch mpi.grace_job 

	(For all data sets)    bash batchScriptMPI.sh

Merge CUDA
	
	module load CUDA

	nvcc cuda.cu -o cuda_merge

	./cuda_merge #a.txt #b #n #s #t

		#a.txt - text file with array list (see python files for how it is generated)
		#b - number of blocks
		#n - number of threads in a block
		#s - size of array
		#t - input type (see batch files)

	(For grace job)   sbatch cuda.grace_job 

	(For all data sets)    bash batchScriptCUDA.sh