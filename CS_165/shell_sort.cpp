#include "project1.h"

void shell_sort(std::vector<int>& a, std::vector<int>& gaps)
{
	size_t len_a = a.size();
	size_t len_gap = gaps.size();

	for (size_t gap = 0; gap < len_gap; ++gap)
	{
		for (int i = gaps[gap]; i < len_a; ++i)
		{
			int temp = a[i];
			int j = i;
			while (j >= gaps[gap] && temp < a[j - gaps[gap]])
			{
				a[j] = a[j - gaps[gap]];
				j -= gaps[gap];
			}
			a[j] = temp;
		}
	}
}
