all: Quicksort QuicksortOpenMP

Quicksort: Quicksort.cpp
	g++ -fopenmp Quicksort.cpp -o Quicksort

QuicksortOpenMP: QuicksortOpenMP.c
	gcc -fopenmp QuicksortOpenMP.c -o QuicksortOpenMP

PSRS: PSRS.c
	gcc -fopenmp PSRS.c -o PSRS -lm

	

clean:
	rm -rf *.o Quicksort
	rm -rf *.o QuicksortOpenMP
	rm -rf *.o PSRS
	 
