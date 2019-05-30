#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <math.h>
#include <mpi.h>

int partition(int* x, int first, int last);
void quicksort(int* x, int first, int last);
void quicksort_parallel(int* x, int size);
void quicksortMPI(int* globaldata, int size);
void sortArray(int size, char* filename);
void printArray(int* x, int size);

int main(argc, argv)
     int argc;
     char *argv[];
{

  FILE *fp;
  char str[MAXCHAR];
  char const *filename = "./1000000Ints.txt";
  int size; //Size of array
  fp = fopen(filename, "r");

  if (fp == NULL)
  {
      printf("Couldn't open file %s", filename);
      return 1;
  }

  while (fgets(str, MAXCHAR, fp) != NULL)
  {

      size = atoi(str);
      printf("Size of array: %d \n", size);
      break;
  }

  fclose(fp);

  fp = fopen(filename, "r");

  //Initialize array on heap
  long long arr[size]; // = {0};

  //For checking purposes
  int c = 0;
  int skip = 0;

  while (fgets(str, MAXCHAR, fp) != NULL)
  {
      if (skip == 0)
      {
          skip++;
      }
      else
      {
          arr[c] = atoi(str);
          c++;
      }
  }
  printf("Lines read: %d\n", c);
  fclose(fp);

  int n = sizeof(arr) / sizeof(arr[0]);
  n = size;

  double startTime, endTime, runTime;

  //omp_set_dynamic(0); // Explicitly disable dynamic teams
  //omp_set_num_threads(4);

  int threads = omp_get_max_threads();
  printf("NUM THREADS: %d \n", threads);

	MPI_Init(&argc, &argv);
  quicksortMPI(arr, size);
  //sortArray(atoi(argv[1]), argv[2]);

  return 0;
}

void sortArray(int size, char* filename)
{
    int value;
    int tmp=0;

    int* globaldata = (int*) malloc(size* sizeof(int));
    FILE *inp;

    inp = fopen (filename,"r");

    for(int i = 0; i < size; i++) {
        fscanf (inp, "%d\n", &tmp);
        globaldata[i] = tmp;
    }
    fclose (inp);



quicksortMPI(globaldata, size);

    free(globaldata);
}

void printArray(int* x, int size) {
    for(int i = 0; i < size; i++)
    {
        printf("%d ", x[i]);
    }

    printf("\n");
}

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition (int* arr, int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high- 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quicksort(int* arr, int low, int high)
{
    if(low < high)
    {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

void quicksortMPI(int* globaldata, int size)
{
  int rank, localsize, processes;
  int* localdata = NULL;
  double start, end, duration;

  MPI_Comm_size(MPI_COMM_WORLD, &processes);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

if(rank == 0) {
start = MPI_Wtime();
}

  localsize = size/processes;
  localdata = (int*) malloc (localsize* sizeof(int));

  MPI_Scatter (globaldata, localsize, MPI_INT, localdata,
              localsize, MPI_INT, 0, MPI_COMM_WORLD);

  quicksort(localdata, 0, localsize-1);

  MPI_Gather (localdata, localsize, MPI_INT	, globaldata,
             localsize, MPI_INT, 0, MPI_COMM_WORLD);

  free(localdata);

   if(rank == 0) {
	end = MPI_Wtime();
    	duration = end-start;
    	printf("Time taken: %f\n", size, duration);
}

  MPI_Finalize ();
}
