#include "project1.h"
#include"inversions.h"

#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <string>

void swap(int& a, int& b);
void test_set(int test_size, bool almost_sorted);
void shell_sequence_1(std::vector<int>& a, int size);
void shell_sequence_2(std::vector<int>& a, int size);
std::ostream& operator<<(std::ostream& out, const std::vector<int>& a);
void write_to_file(std::string fName, int n, double t);
void annealing_reps(std::vector<int>& a, int size, int reps);
void annealing_sequence_1(std::vector<int>& b, int size);
void annealing_sequence_2(std::vector<int>& b, int size);

const int SMALL_SET = 100;
const int MEDIUM_SET = 1000;
const int LARGE_SET = 10000;
const int EVEN_LARGER_SET = 100000;
const int LARGEST_SET = 1000000;

int main()
{
	test_set(SMALL_SET, false);
	test_set(SMALL_SET, false);
	test_set(SMALL_SET, false);
	test_set(SMALL_SET, true);
	test_set(SMALL_SET, true);
	test_set(SMALL_SET, true);
	test_set(MEDIUM_SET, false);
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
	/*
	test_set(PHAT_ASS_SET, false);
	test_set(PHAT_ASS_SET, false);
	test_set(PHAT_ASS_SET, false);
	test_set(PHAT_ASS_SET, true);
	test_set(PHAT_ASS_SET, true);
	test_set(PHAT_ASS_SET, true);
	test_set(PHAT_ASS_SET, true); 
	*/
	system("pause");
	return 0;
}

void test_set(int set_size, bool almost_sorted)
{
	std::vector<int> a(set_size);
	std::vector<int> b(set_size);
	for (int i = 0; i < set_size; ++i)
	{
		a[i] = i + 1;
	}


	std::random_device rd;
	std::mt19937 eng(rd());

	if (!almost_sorted)
	{
		for (int i = 0; i < set_size - 1; ++i)
		{
			std::uniform_int_distribution<> distr(i, set_size - 1);
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
		std::uniform_int_distribution<> distr(0, set_size - 1);
		for (int i = 0; i < x; ++i)
		{
			swap(a[distr(eng)], a[distr(eng)]);
		}
	}

	clock_t start;
	clock_t end;
	double t = 0.0;
	double min = INT_MAX;
	std::string fName;
	std::vector<int> gaps;
	double total = 0.0;
	
	for (int i = 0; i < 3; ++i)
	{
		b = a;

		std::cout << "-------------------- BUBBLE SORT --------------------\n\n";
		double t = 0.0;
		start = clock();
		bubble_sort(b);
		end = clock();
		t = static_cast<double>(end - start) / CLOCKS_PER_SEC;
		min = (t < min) ? t : min;
	}
	fName = (almost_sorted) ? "bubble_almost" : "bubble_random";
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
		t = static_cast<double>(end - start) / CLOCKS_PER_SEC;
		min = (t < min) ? t : min;
	}
	fName = (almost_sorted) ? "insertion_almost" : "insertion_random";
	write_to_file(fName, set_size, min);
	std::cout << "insertion alone(" << set_size << "): " << t << "\n\n";

	t = 0.0;
	for (int i = 0; i < 3; ++i)
	{
		b = a;
		std::cout << "------------------- SPIN THE BOTTLE -------------------\n\n";
		start = clock();
		spin_the_bottle_sort(b);
		end = clock();
		t = static_cast<double>(end - start) / CLOCKS_PER_SEC;
		total += t;
	}
	t = total / 3;
	fName = (almost_sorted) ? "spin_almost" : "spin_random";
	write_to_file(fName, set_size, t);
	
	t = 0.0;
	min = INT_MAX;
	shell_sequence_1(gaps, set_size);
	std::cout << gaps;
	for (int i = 0; i < 1; ++i)
	{
		b = a;
		std::cout << "------------------- SHELL SORT (sequence 1) -------------------\n\n";
		start = clock();
		shell_sort(b, gaps);
		end = clock();
		t = static_cast<double>(end - start) / CLOCKS_PER_SEC;
		min = (t < min) ? t : min;
	}
	fName = (almost_sorted) ? "shell_almost_seq1" : "shell_random_seq1";
	write_to_file(fName, set_size, min);
	std::cout << "time(" << set_size << "): " << min << "\n\n";
	std::cout << "inversions(" << set_size << "): " << mergeSort(b) << "\n\n";
	
	t = 0.0;
	min = INT_MAX;
	shell_sequence_2(gaps, set_size);
	std::cout << gaps;
	for (int i = 0; i < 3; ++i)
	{
		b = a;
		std::cout << "------------------- SHELL SORT (sequence 2) -------------------\n\n";
		start = clock();
		shell_sort(b, gaps);
		end = clock();
		t = static_cast<double>(end - start) / CLOCKS_PER_SEC;
		min = (t < min) ? t : min;
	}
	fName = (almost_sorted) ? "shell_almost_seq2" : "shell_random_seq2";
	write_to_file(fName, set_size, min);
	std::cout << "time(" << set_size << "): " << min << "\n\n";
	std::cout << "inversions(" << set_size << "): " << mergeSort(b) << "\n\n";
	
	gaps.clear();
	annealing_sequence_1(gaps, set_size);
	std::cout << "gaps:\n";
	gaps.push_back(0);
	std::cout << gaps;

	std::vector<int> reps;
	annealing_reps(reps, gaps.size(), 2);
	std::cout << "reps\n";
	std::cout << reps;
	total = 0.0;
	for (int i = 0; i < 3; ++i)
	{
		std::cout << "------------------- ANNEALING SORT (SEQUENCE 1) -------------------\n\n";
		b = a;
		start = clock();
		annealing_sort(b, gaps, reps);
		end = clock();
		t = static_cast<double>(end - start) / CLOCKS_PER_SEC;
		total += t;
	}
	//t = total / 3;
	fName = (almost_sorted) ? "annealing_almost_seq1" : "annealing_random_seq1";
	write_to_file(fName, set_size, t);
	std::cout << "inversions(" << set_size << "): " << mergeSort(b) << "\n\n";
	std::cout << "time: " << t << "\n\n";
	
	gaps.clear();
	annealing_sequence_2(gaps, set_size);
	std::cout << "gaps:\n";
	gaps.push_back(0);
	std::cout << gaps;
	std::vector<int> reps;
	reps.clear();
	annealing_reps(reps, gaps.size(), 3);
	std::cout << "reps\n";
	std::cout << reps;
	total = 0.0;
	for (int i = 0; i < 3; ++i)
	{
		b = a;
		std::cout << "------------------- ANNEALING SORT (SEQUENCE 2) -------------------\n\n";
		start = clock();
		annealing_sort(b, gaps, reps);
		end = clock();
		t = static_cast<double>(end - start) / CLOCKS_PER_SEC;
		total += t;
	}
	t = total / 3;
	fName = (almost_sorted) ? "annealing_almost_seq2" : "annealing_random_seq2";
	write_to_file(fName, set_size, t);
	std::cout << "inversions(" << set_size << "): " << mergeSort(b) << "\n\n";
	std::cout << "time: " << t << "\n\n";
	
}

void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

// perfect squares
void annealing_sequence_1(std::vector<int>& b, int size)
{
	int i = 1;
	while ((i * i) < size / 10)
	{
		b.push_back(i * i);
		++i;
	}
	i = 0;
	int j = b.size() - 1;
	while (i < j)
	{
		swap(b[i], b[j]);
		++i;
		--j;
	}
}

// Decreasing powers of 2
void annealing_sequence_2(std::vector<int>& b, int size)
{
	int len = size;
	for (int i = 1; i < len; i*=2)
	{
		b.push_back(i);
	}
	//reverse
	int i = 0;
	int j = b.size() - 1;
	while (i < j)
	{
		swap(b[i], b[j]);
		++i;
		--j;
	}
}

// increasing powers of 2
void shell_sequence_1(std::vector<int>& a, int size)
{
	int len = size;
	for (int i = 1; i < len; i *= 2)
	{
		a.push_back(i);
	}
}

// fibonacci #'s
void shell_sequence_2(std::vector<int>& a, int size)
{
	a.push_back(0);
	a.push_back(1);
	a.push_back(1);
	int lim = size / 10;
	for (int i = 2; a[i] < lim; ++i)
	{
		a.push_back(a[i - 1] + a[i]);
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

void annealing_reps(std::vector<int>& a, int size, int reps)
{
	for (int i = 0; i < size - 1; ++i)
	{
		a.push_back(reps);
	}
	a.push_back(0);
}