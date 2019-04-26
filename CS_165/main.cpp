#include "project1.h"

#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <string>

void swap(int& a, int& b);
void test_set(int test_size, bool almost_sorted);
void shell_sequence(std::vector<int>& a, int size);
std::ostream& operator<<(std::ostream& out, const std::vector<int>& a);
void write_to_file(std::string fName, int n, double t);
void annealing_reps(std::vector<int>& a, int size, int reps);
void annealing_sequence_1(std::vector<int>& a, std::vector<int>& b, int size);
void annealing_sequence_2(std::vector<int>& a, std::vector<int>& b, int size);



const int SMALL_SET = 100;
const int MEDIUM_SET = 1000;
const int LARGE_SET = 10000;
const int EVEN_LARGER_SET = 100000;
const int PHAT_ASS_SET = 1000000;

int main()
{
	test_set(SMALL_SET, false);
	test_set(SMALL_SET, false);
	test_set(SMALL_SET, false);
	test_set(SMALL_SET, true);
	test_set(SMALL_SET, true);
	test_set(SMALL_SET, true);
	/*test_set(MEDIUM_SET, false);
	test_set(MEDIUM_SET, false);
	test_set(MEDIUM_SET, false);
	test_set(MEDIUM_SET, true);
	test_set(MEDIUM_SET, true);
	test_set(MEDIUM_SET, true);
	test_set(LARGE_SET, false);
	test_set(LARGE_SET, false);
	test_set(LARGE_SET, false);
	test_set(LARGE_SET, true);
	test_set(LARGE_SET, true);
	test_set(LARGE_SET, true);
	test_set(EVEN_LARGER_SET, false);
	test_set(EVEN_LARGER_SET, false);
	test_set(EVEN_LARGER_SET, false);
	test_set(EVEN_LARGER_SET, true);
	test_set(EVEN_LARGER_SET, true);
	test_set(EVEN_LARGER_SET, true);
	test_set(PHAT_ASS_SET, false);
	test_set(PHAT_ASS_SET, false);
	test_set(PHAT_ASS_SET, false);
	test_set(PHAT_ASS_SET, true);
	test_set(PHAT_ASS_SET, true);
	test_set(PHAT_ASS_SET, true);
	test_set(PHAT_ASS_SET, true);*/

	system("pause");
	return 0;
}

void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

void test_set(int set_size, bool almost_sorted)
{
	std::vector<int> a = std::vector<int>(set_size);
	std::vector<int> b = std::vector<int>(set_size);
	for (int i = 0; i < set_size; ++i)
	{
		a[i] = i + 1;
	}


	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(0, set_size - 1);
	if (!almost_sorted)
	{
		for (int i = 0; i < set_size; ++i)
		{
			swap(a[i], a[distr(eng)]);
		}
	}
	else
	{
		int x = 0;
		for (int i = set_size; i != 0; i /= 2)
		{
			++x;
		}
		x *= 2;

		for (int i = 0; i < x; ++i)
		{
			swap(a[distr(eng)], a[distr(eng)]);
		}
	}
	clock_t start;
	clock_t end;
	double t = 0.0;
	double min = INT_MAX;

	for (int i = 0; i < 3; ++i)
	{
		b = a;

		std::cout << "-------------------- BUBBLE SORT --------------------\n\n";
		double t = 0.0;
		start = clock();
		bubble_sort(b);
		end = clock();
		t = static_cast<float>(end - start) / CLOCKS_PER_SEC;
		min = (t < min) ? t : min;
	}
	std::string fName = (almost_sorted) ? "bubble_almost" : "bubble_random";
	write_to_file(fName, set_size, min);
	t = 0.0;
	min = INT_MAX;
	for (int i = 0; i < 3; ++i)
	{
		b = a;
		std::cout << "-------------------- INSERTION SORT --------------------\n\n";
		start = clock();
		insertion_sort(b);
		end = clock();
		t = static_cast<float>(end - start) / CLOCKS_PER_SEC;
		min = (t < min) ? t : min;
	}
	fName = (almost_sorted) ? "insertion_almost" : "insertion_random";
	write_to_file(fName, set_size, min);

	t = 0.0;
	double total = 0.0;
	for (int i = 0; i < 3; ++i)
	{
		b = a;
		std::cout << "------------------- SPIN THE BOTTLE -------------------\n\n";
		start = clock();
		spin_the_bottle_sort(b);
		end = clock();
		t = static_cast<float>(end - start) / CLOCKS_PER_SEC;
		total += t;
	}
	t = total / 3;
	fName = (almost_sorted) ? "spin_almost" : "spin_random";
	write_to_file(fName, set_size, t);

	t = 0.0;
	min = INT_MAX;
	std::vector<int> gaps;
	shell_sequence(gaps, set_size);
	for (int i = 0; i < 3; ++i)
	{
		b = a;
		std::cout << "------------------- SHELL SORT -------------------\n\n";
		start = clock();
		shell_sort(b, gaps);
		end = clock();
		t = static_cast<float>(end - start) / CLOCKS_PER_SEC;
		min = (t < min) ? t : min;
	}
	fName = (almost_sorted) ? "shell_almost" : "shell_random";
	write_to_file(fName, set_size, min);

	b = a;
	std::cout << "------------------- ANNEALING SORT -------------------\n\n";
	std::cout << "BEFORE:\n";
	std::cout << b;
	gaps.clear();
	annealing_sequence_1(b, gaps, set_size);
	std::cout << "gaps:\n";
	gaps.push_back(0);
	std::cout << gaps;

	std::vector<int> reps;
	annealing_reps(reps, gaps.size(), 3);
	std::cout << "reps\n";
	std::cout << reps;
	start = clock();
	annealing_sort(b, gaps, reps);
	end = clock();
	t = static_cast<float>(end - start);
	std::cout << "AFTER\n";
	std::cout << b;
	fName = (almost_sorted) ? "annealing_almost" : "annealing_random";
	write_to_file(fName, set_size, t);

}

void annealing_sequence_1(std::vector<int>& a, std::vector<int>& b, int size)
{
	int len = a.size() / 2;
	
	for(int i = 1; i < len ; i*=2)
	{
		b.push_back(len - i);
	}
}

void annealing_sequence_2(std::vector<int>& a, std::vector<int>& b, int size)
{

}

void shell_sequence(std::vector<int>& a, int size)
{
	for (size_t i = size / 2; i != 0; i /= 2)
	{
		a.push_back(i);
	}
}

void shell_sequence_2(std::vector<int>& a, int size)
{

}

std::ostream& operator<<(std::ostream& out, const std::vector<int>& a)
{
	size_t len = a.size();
	for (size_t i = 0; i < len; ++i)
	{
		out << a[i] << " ";
	}
	out << "\n\n";
	return out;
}

void write_to_file(std::string fName, int n, double t)
{
	std::ofstream outFile;
	outFile.open(fName + ".txt", std::ofstream::app);
	outFile << fName << "," << n << "," << t << "\n";
}

void annealing_reps(std::vector<int>& a, int size, int reps)
{
	for (int i = 0; i < size - 1; ++i)
	{
		a.push_back(reps);
	}
	a.push_back(0);
}