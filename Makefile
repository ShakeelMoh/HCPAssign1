all: Quicksort QuicksortOpenMP PSRS Quicksort_MPI PSRS_MPI

#OpenMP Algorithms

Quicksort: Quicksort.cpp
	g++ -fopenmp Quicksort.cpp -o Quicksort

QuicksortOpenMP: QuicksortOpenMP.c
	gcc -fopenmp QuicksortOpenMP.c -o QuicksortOpenMP

PSRS: PSRS.c
	gcc -fopenmp PSRS.c -o PSRS -lm

#MPI Algorithms

Quicksort_MPI: Quicksort_MPI.c
	mpicc -std=c99 -fopenMP Quicksort_MPI.c Quicksort_MPI

PSRS_MPI: PSRS_MPI.c
	mpicc -fopenmp PSRS_MPI.c -o PSRS_MPI
	

clean:
	rm -rf *.o Quicksort
	rm -rf *.o QuicksortOpenMP
	rm -rf *.o PSRS
	rm -rf *.o Quicksort_MPI
	rm -rf *.o PSRS_MPI
	 
