#include "analyze.h"
#include "algorithm.h"
#include <time.h>
#include <stdlib.h>

//
// Private
//

// Fill array with random numbers for an apporcimate average
void fill_random(int *a, int n)
{
    srand(time(NULL));
    for (int i; i < n; i ++)
    {
        int r = rand();
        a[i] = r;
    }
}

// Fill array with sorted values in ascending order
void fill_sorted_asc(int *a, int n)
{
    for (int i; i < n; i++)
    {
        a[i] = i;
    }
}
// Fill array with sorted values in descending order
void fill_sorted_desc(int *a, int n)
{
    for (int i; i < n; i++)
    {
        a[i] = n-i;
    }
}
// Fill array with best case scenario for quicksort
void fill_quicksort_best_case(int *a, int n)
{


}


//
// Public
//
void benchmark(const algorithm_t a, const case_t c, result_t *buf, int n)
{
    int *array = malloc(n*sizeof(int));
    switch (c)
    {
        case best_t:
            switch (a)
            {
                case quick_sort_t:
                    // TODO
                    break;
                
                default:
                    fill_sorted_asc(array, n);
                    break;
            }
            break;

        case worst_t:
            fill_sorted_desc(array, n);

        case average_t:
            fill_random(array, n);
            break;

        default:
            break;
    }
    switch (a)
    {
        case bubble_sort_t:

            break;
        case insertion_sort_t:

            break;
        case quick_sort_t:

            break;
        case linear_search_t:

            break;
        case binary_search_t:

            break;
        default:
            break;
    }
}
