#include "project1.h"

void insertion_sort(std::vector<int>& a)
{
	size_t len = a.size();
	for (size_t i = 1; i < len; ++i)
	{
		int temp = a[i];
		size_t j = i;
		while (j > 0 && a[j - 1] > temp)
		{
			a[j] = a[j - 1];
			--j;
		}
		a[j] = temp;
	}
}
