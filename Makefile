all: Quicksort QuicksortOpenMP

Quicksort: Quicksort.cpp
	g++ -fopenmp Quicksort.cpp -o Quicksort

QuicksortOpenMP: QuicksortOpenMP.c
	gcc -fopenmp QuicksortOpenMP.c -o QuicksortOpenMP

PSRS: PSRS.c
	gcc -fopenmp PSRS.c -o PSRS -lm

PSRS_MPI: PSRS_MPI.c
	gcc -fopenmp PSRS_MPI.c -o PSRS_MPI
	

clean:
	rm -rf *.o Quicksort
	rm -rf *.o QuicksortOpenMP
	rm -rf *.o PSRS
	 
