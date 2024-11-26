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
	bool swaps;
	for (int i = 0; i < n-1; i++)
	{
		for (int j = 0; j< n-i-1; j++)
		{
			if ( a[j] > a[j+1]) {
				swap(&a[j], &a[j+1]);
				swaps = true;
			}
		}
		
	}
	
}

void insertion_sort(int *a, int n)
{
	for(int i = 1;i<n;i++) 
    {
        int key = a[i];
        int j = i-1;

        while(j>=0 && key < a[j])
        {
           a[j+1] = a[j]; 
           j-=1;
        }
        a[j+1] = key;
    }
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
	if (n <= 0)
	return false; // TODO: binary search

	int middle = n/2;
	int number = a[middle];

	if (number == v)
	return true;

	else if (number > v)
	return binary_search (a, middle, v);

	else

	return binary_search (a + middle + 1, n-middle-1, v);

}
