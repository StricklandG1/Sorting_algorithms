#include "project1.h"
#include <random>

void annealing_sort(std::vector<int>& nums, const std::vector<int>& temps, const std::vector<int>& reps)
{
	int a_len = nums.size();
	int temps_len = temps.size();
	int reps_len = reps.size();
	std::random_device rd;
	std::mt19937 eng(rd());
	for (int j = 0; j < temps_len; ++j)
	{
		for (int i = 0; i < a_len - 1; ++i)
		{
			int min = ((a_len > (i + temps[j])) ? (i + temps[j]) : a_len - 1);
			for (int k = 0; k < reps[j]; k++)
			{
				std::uniform_int_distribution<> distr(i + 1, min);

				int s = distr(eng);
				if (nums[i] > nums[s])
				{
					int temp = nums[i];
					nums[i] = nums[s];
					nums[s] = temp;
				}
			}
		}
		for (int i = a_len - 1; i > 1; --i)
		{
			int max = ((1 > (i - temps[j])) ? 1 : (i - temps[j]));
			for (int k = 0; k < reps[j]; ++k)
			{
				std::uniform_int_distribution<> distr(max, i - 1);

				int s = distr(eng);
				if (nums[s] > nums[i])
				{
					int temp = nums[s];
					nums[s] = nums[i];
					nums[i] = temp;
				}
			}
		}
	}
}