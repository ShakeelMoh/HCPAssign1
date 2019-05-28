#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAXCHAR 1000
// A utility function to swap two elements
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

/* This function takes last element as pivot, places 
   the pivot element at its correct position in sorted 
    array, and places all smaller (smaller than pivot) 
   to left of pivot and all greater elements to right 
   of pivot */
int partition(int arr[], int low, int high)
{
    int pivot = arr[high]; // pivot
    int i = (low - 1);     // Index of smaller element

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

/* The main function that implements QuickSort 
 arr[] --> Array to be sorted, 
  low  --> Starting index, 
  high  --> Ending index */
void quickSort(int arr[], int low, int high)
{
    if (low < high)

    {
        /* pi is partitioning index, arr[p] is now 
           at right place */
        int pi = partition(arr, low, high);

#pragma omp task default(none) firstprivate(arr, low, pi)
        {
            quickSort(arr, low, pi - 1);
        }
#pragma omp task default(none) firstprivate(arr, high, pi)
        {
            quickSort(arr, pi + 1, high);
        }

        // Separately sort elements before
        // partition and after partition
        /*
#pragma omp parallel sections
        {
#pragma omp section
            {
                quickSort(arr, low, pi - 1);
            }
#pragma omp section
            {
                quickSort(arr, pi + 1, high);
            }
        }
        */
    }
}

/* Function to print an array */
void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
}

// Driver program to test above functions
int main()
{

    //Misc information
    //omp_set_num_threads(1);
    //int threads = omp_get_num_threads();
    //printf("Number of threads: %d", threads);

    FILE *fp;
    char str[MAXCHAR];
    char const *filename = "./100000Ints.txt";
    int size; //Size of array
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Couldn't open file %s", filename);
        return 1;
    }

    int c = 0;
    while (fgets(str, MAXCHAR, fp) != NULL)
    {
        if (c == 0)
        {
            size = atoi(str);
            printf("Size of array: %d \n", size);
            c++;
        }
    }
    fclose(fp);

    fp = fopen(filename, "r");

    int arr[size]; // = {0};
    c = 0;
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
            //printf("%s", str);
            //printf("Yo %s", arr);
            c++;
        }
    }

    fclose(fp);

    //int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    double startTime, endTime, runTime;

    //{
    //Start timer
    startTime = omp_get_wtime();

    omp_set_dynamic(0); // Explicitly disable dynamic teams
    omp_set_num_threads(2);

    int threads = omp_get_max_threads();
    printf("MAX THREADS: %d", threads);

//#pragma omp parallel
#pragma omp parallel default(none) shared(arr, n)

    {
        //int threads = omp_get_num_threads();
        //printf("Number of threads: %d", threads);
#pragma omp single nowait
        {
            quickSort(arr, 0, n - 1);
        }
    }
    //End timer
    endTime = omp_get_wtime();

    //Run time
    runTime = endTime - startTime;

    printf("Sorted array: ");

    printf("Time taken: %f", runTime);

    //printArray(arr, n);
    //}

    return 0;
}
