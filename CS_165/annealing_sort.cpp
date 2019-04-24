#include "project1.h"
#include <random>

void annealing_sort(std::vector<int>& a, std::vector<int>& temps, std::vector<int>& reps)
{
	int len = a.size();
	int  temps_len = temps.size();
	int  reps_len = reps.size();
	std::random_device rd;
	std::mt19937 eng(rd());
	for (int i = 0; i < temps_len; ++i)
	{
		for (int j = 0; j < len - 1; ++j)
		{
			std::uniform_int_distribution<> distr(j + 1, ((len > (j + temps[i])) ? (j + temps[i]) : len));

			for (int k = 0; k < reps[i]; ++k)
			{
				int s = distr(eng);
				if (a[j] > a[s])
				{
					int temp = a[i];
					a[j] = a[s];
					a[s] = temp;
				}
			}
		}
		for (int j = len - 1; j > 0; --j)
		{
			std::uniform_int_distribution<> distr(((1 > j - temps[i]) ? 1 : j - temps[i]), j - 1);
			for (int k = 0; k < reps[i]; ++k)
			{
				int s = distr(eng);
				if (a[s] > a[j])
				{
					int temp = a[s];
					a[s] = a[j];
					a[j] = temp;
				}
			}
		}
	}
}