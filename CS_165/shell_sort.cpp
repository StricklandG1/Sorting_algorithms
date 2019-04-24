#include "project1.h"

void shell_sort(std::vector<int>& nums, std::vector<int>& gaps)
{
	size_t len_a = nums.size();
	size_t len_gap = gaps.size();

	for (size_t gap = 0; gap < len_gap; ++gap)
	{
		for (int i = gaps[gap]; i < len_a; ++i)
		{
			int temp = nums[i];
			int j = i;
			while (j >= gaps[gap] && temp < nums[j - gaps[gap]])
			{
				nums[j] = nums[j - gaps[gap]];
				j -= gaps[gap];
			}
			nums[j] = temp;
		}
	}
}
