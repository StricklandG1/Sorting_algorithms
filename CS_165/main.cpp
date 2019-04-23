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

const int SMALL_SET = 100;
const int MEDIUM_SET = 1000;
const int LARGE_SET = 10000;
const int EVEN_LARGER_SET = 100000;
const int PHAT_ASS_SET = 1000000;

int main()
{
	/*test_set(SMALL_SET, false);
	test_set(SMALL_SET, false);
	test_set(SMALL_SET, false);
	test_set(SMALL_SET, true);
	test_set(SMALL_SET, true);
	test_set(SMALL_SET, true);*/
	test_set(MEDIUM_SET, false);
	test_set(MEDIUM_SET, false);
	test_set(MEDIUM_SET, false);
	test_set(MEDIUM_SET, true);
	test_set(MEDIUM_SET, true);
	test_set(MEDIUM_SET, true);
	//test_set(MEDIUM_SET);
	//test_set(LARGE_SET);
	//test_set(EVEN_LARGER_SET);
	//test_set(PHAT_ASS_SET);

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

	b = a;

	std::cout << "-------------------- BUBBLE SORT --------------------\n\n";
	double t = 0.0;
	clock_t start = clock();
	bubble_sort(b);
	clock_t end = clock();
	t = static_cast<float>(end - start) / CLOCKS_PER_SEC;
	std::string fName = (almost_sorted) ? "bubble_almost" : "bubble_random";
	write_to_file(fName, set_size, t);

	b = a;
	std::cout << "-------------------- INSERTION SORT --------------------\n\n";
	start = clock();
	insertion_sort(b);
	end = clock();
	t = static_cast<float>(end - start) / CLOCKS_PER_SEC;
	fName = (almost_sorted) ? "insertion_almost" : "insertion_random";
	write_to_file(fName, set_size, t);

	b = a;
	std::cout << "------------------- SPIN THE BOTTLE -------------------\n\n";
	start = clock();
	spin_the_bottle_sort(b);
	end = clock();
	t = static_cast<float>(end - start) / CLOCKS_PER_SEC;
	fName = (almost_sorted) ? "spin_almost" : "spin_random";
	write_to_file(fName, set_size, t);

	b = a;
	std::cout << "------------------- SHELL SORT -------------------\n\n";
	
	std::vector<int> gaps;
	shell_sequence(gaps, set_size);
	start = clock();
	shell_sort(b, gaps);
	end = clock();
	t = static_cast<float>(end - start) / CLOCKS_PER_SEC;
	fName = (almost_sorted) ? "shell_almost" : "shell_random";
	write_to_file(fName, set_size, t);
}

void shell_sequence(std::vector<int>& a, int size)
{
	for (size_t i = size / 2; i != 0; i /= 2)
	{
		a.push_back(i);
	}
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
