#include "algorithm.h"

//
// Private
//


//
// Public
//

// Swaps two pointers
void swap(int *p1, int *p2)
{
	int t;
	t = *p1;
	*p1 = *p2;
	*p2 = t;
}

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
	if (n <= 1)
	{
		return;
	}

	int pivot = a[n-1];
	int pivot_offset = 0;

	for (int i = 0; i < n -1; i++)
	{
		if (a[i] < pivot)
		{
			swap(&a[pivot_offset], &a[i]);
			pivot_offset++;
		}
	}

	swap(&a[pivot_offset], &a[n-1]);

	quick_sort(a, pivot_offset);
	quick_sort(a + pivot_offset + 1, n - pivot_offset - 1);
}

bool linear_search(const int *a, int n, int v)
{
	for (int i = 0; i < n; i++)
	{
		if (a[i] == v)
		{
			return true;
		}
	}
	return false;
}

bool binary_search(const int *a, int n, int v)
{
	return false; // TODO: binary search
}
