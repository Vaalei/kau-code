#include "analyze.h"
#include "algorithm.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

//
// Private
//

// Fill array with random numbers for an apporcimate average
void fill_random(int *a, int n)
{
    for (int i = 0; i < n; i ++)
    {
        int r = rand()%n;
        a[i] = r;
    }
}

// Fill array with sorted values in ascending order
void fill_sorted_asc(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        *(a+i) = i;
    }
}
// Fill array with sorted values in descending order
void fill_sorted_desc(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        a[i] = n-i;
    }
}
// Fill array with best case scenario for quicksort
void fill_quicksort_best_case(int *a, int n)
{
    if (n <= 1)
	{
		return;
	}
    int mid = n/2;
    swap(&a[mid], &a[n-1]);
    fill_quicksort_best_case(a, mid);
    fill_quicksort_best_case(a + mid, n - mid - 1);
}

// Temp
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

//
// Public
//
void benchmark(const algorithm_t a, const case_t c, result_t *buf, int n)
{
    srand(time(NULL));
    int v;
    time_t start;
    time_t end;
    for (int i = 0; i < n; i++)
    {

        int size = pow(2,(9+i));
        int mid = size/2;
        int *array = malloc(size*sizeof(int));
        
        switch (c)
        {
            case best_t:
                switch (a)
                {
                    case quick_sort_t:
                        fill_sorted_asc(array, size);
                        fill_quicksort_best_case(array, size);
                        break;

                    case binary_search_t:
                        v = array[mid];
                        fill_sorted_asc(array, size);

                    case linear_search_t:
                        v = array[0];
                        fill_sorted_asc(array, size);
            
                    default:
                        fill_sorted_asc(array, size);
                        break;
                }
                break;

            case worst_t:
                switch (a)
                {
                    case binary_search_t:
                        v = 0;
                        fill_sorted_asc(array, size);
                        break;
                    
                    case linear_search_t:
                        v = array[n-1];
                        fill_sorted_asc(array, size);
                        break;
                    
                    default:
                        fill_sorted_desc(array, size);
                        break;
                }
            
            case average_t:
                switch (a)
                {
                    case binary_search_t:
                    case linear_search_t:
                        v = rand() % n;
                        fill_sorted_asc(array, size);
                        break;
                    
                    default:
                        fill_random(array, size);
                        break;
                }

                
        }
        // Temp
        //printArray(array, size);
        time(&start);
        switch (a)
        {
            case bubble_sort_t:
                bubble_sort(array, size);
                break;
            case insertion_sort_t:
                insertion_sort(array, size);
                break;
            case quick_sort_t:
                quick_sort(array, size);
                break;
            case linear_search_t:
                linear_search(array, size, v);
                break;
            case binary_search_t:
                binary_search(array, size, v);
                break;
            default:
                break;
        }
        time(&end);
        buf[i].time = difftime(start, end);
        buf[i].size = size;

        free(array);
    }
}
