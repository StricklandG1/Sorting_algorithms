#include "project1.h"

void bubble_sort(std::vector<int>& a)
{
	size_t len = a.size();
	for (size_t i = 0; i < len; ++i)
	{
		for (size_t j = 1; j < len - i; ++j)
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