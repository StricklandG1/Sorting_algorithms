#include "project1.h"

void bubble_sort(std::vector<int>& nums)
{
	size_t len = nums.size();
	for (size_t i = 0; i < len; ++i)
	{
		for (size_t j = 1; j < len - i; ++j)
		{
			if (nums[j - 1] > nums[j])
			{
				int temp = nums[j - 1];
				nums[j - 1] = nums[j];
				nums[j] = temp;
			}
		}
	}
}