#include "project1.h"

void bubble_sort(int* a, int size)
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 1; j < size - i; ++j)
		{
			if (a[j - 1] > a[j])
			{
				int temp = a[j - 1];
				a[j - 1] = a[j];
				a[j] = temp;
			}
		}
	}
}