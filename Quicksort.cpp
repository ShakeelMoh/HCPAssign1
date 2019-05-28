#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
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

    //Time constructs
    double total_time;
    clock_t start, end;

    //Reading from file
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

    int *arr = new int[size];

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

            //printf("%d", arr[c]);
            //printf("%s", str);
            //printf("Yo %s", arr);
            c++;
        }
    }
    printf("Lines read: %d\n", c);
    fclose(fp);

    //int arr[] = {10, 7, 8, 9, 1, 5};

    int n = sizeof(arr) / sizeof(arr[0]);
    n = size;
    //start = clock();

    double startTime, endTime, runTime;

    //omp_set_dynamic(0); // Explicitly disable dynamic teams
    //omp_set_num_threads(4);

    int threads = omp_get_max_threads();
    printf("NUM THREADS: %d \n", threads);

    //Start timer
    startTime = omp_get_wtime();

    quickSort(arr, 0, n - 1);

    endTime = omp_get_wtime();
    runTime = endTime - startTime;

    //printf("Start time %d\n", startTime);
    //printf("End time %d\n", endTime);
    //end = clock();

    //printf("Start: %d, End: %d", start, end);
    //total_time = ((double)(end - start)) / CLK_TCK;
    //printf("Total time: %d \n", total_time);
    printf("Run time: %f \n", runTime);
    printf("Sorted array!");

    if (n < 10000000)
    {
        //printArray(arr, size);
    }
    else
    {
        printf("\nDone!");
    }
    //delete[] arr;
    return 0;
}
