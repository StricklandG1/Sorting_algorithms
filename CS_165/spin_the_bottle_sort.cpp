#include "project1.h"
#include <random>
#include <iostream>

bool sorted(int* a, int size)
{
	bool sorted = true;
	int i = 0;
	while (sorted && i < size - 1)
	{
		sorted = a[i] < a[i + 1];
		++i;
	}
	return sorted;
}

void spin_the_bottle_sort(int* a, int size)
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(0, size - 1);
	while (!sorted(a, size))
	{
		for (int i = 0; i < size; ++i)
		{
			int j = distr(eng);
			//std::cout << rand_i << "        " << rand_j;
			if (i < j)
			{
				if (a[i] > a[j])
				{
					int temp = a[i];
					a[i] = a[j];
					a[j] = temp;
				}
			}
			else if (j < i)
			{
				if (a[j] > a[i])
				{
					int temp = a[j];
					a[j] = a[i];
					a[i] = temp;
				}
			}
		}
	}
}
