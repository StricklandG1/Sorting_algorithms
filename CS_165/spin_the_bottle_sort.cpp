#include "project1.h"
#include <random>
#include <iostream>

bool sorted(const std::vector<int>& nums)
{
	size_t len = nums.size();
	bool sorted = true;
	int i = 0;
	while (sorted && i < len - 1)
	{
		sorted = nums[i] < nums[i + 1];
		++i;
	}
	return sorted;
}

void spin_the_bottle_sort(std::vector<int>& nums)
{
	size_t len = nums.size();
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(0, len - 1);
	while (!sorted(nums))
	{
		for (int i = 0; i < len; ++i)
		{
			int j = distr(eng);
			if (i < j)
			{
				if (nums[i] > nums[j])
				{
					int temp = nums[i];
					nums[i] = nums[j];
					nums[j] = temp;
				}
			}
			else if (j < i)
			{
				if (nums[j] > nums[i])
				{
					int temp = nums[j];
					nums[j] = nums[i];
					nums[i] = temp;
				}
			}
		}
	}
}
