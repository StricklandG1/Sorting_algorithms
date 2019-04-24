#include "project1.h"

void insertion_sort(std::vector<int>& nums)
{
	size_t len = nums.size();
	for (size_t i = 1; i < len; ++i)
	{
		int temp = nums[i];
		size_t j = i;
		while (j > 0 && nums[j - 1] > temp)
		{
			nums[j] = nums[j - 1];
			--j;
		}
		nums[j] = temp;
	}
}
