#include "project1.h"

void insertion_sort(int* a, int size)
{
	for (int i = 1; i < size; ++i)
	{
		int temp = a[i];
		int j = i;
		while (j > 0 && a[j - 1] > temp)
		{
			a[j] = a[j - 1];
			--j;
		}
		a[j] = temp;
	}
}
