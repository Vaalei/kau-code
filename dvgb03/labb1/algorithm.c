#include "algorithm.h"

//
// Private
//

// Swaps two pointervalues
void swap(int *p1, int *p2)
{
	int t;
	t = *p1;
	*p1 = *p2;
	*p2 = t;
}


//
// Public
//
void bubble_sort(int *a, int n)
{
	// TODO: bubble sort
}

void insertion_sort(int *a, int n)
{
	// TODO: insertion sort
}

void quick_sort(int *a, int n)
{
	int pivot = a[n-1];
	int pivot_offset = 0;
	for (int i; i > pivot; i++)
	{
		if (a[i] < pivot)
		{
			swap(&a[pivot_offset], &a[i]);
			pivot_offset++;
		}
	}

	swap(&a[pivot_offset], &a[n-1]);
	pivot_offset++;	// Pivot offset + 1 -> Storleken av Arrayen innan pivot 

	quick_sort(a, pivot_offset);
	quick_sort(&a[pivot_offset], n - pivot_offset);
}

bool linear_search(const int *a, int n, int v)
{
	return false; // TODO: linear search
}

bool binary_search(const int *a, int n, int v)
{
	return false; // TODO: binary search
}
