#include "project1.h"

#include <iostream>
#include <random>

void swap(int& a, int& b);
void test_set(int test_size);
void shell_sequence(std::vector<int>& a, int size);
std::ostream& operator<<(std::ostream& out, const std::vector<int>& a);

const int SMALL_SET = 100;
const int MEDIUM_SET = 1000;
const int LARGE_SET = 10000;
const int EVEN_LARGER_SET = 100000;
const int PHAT_ASS_SET = 1000000;

int main()
{
	test_set(SMALL_SET);
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

void test_set(int set_size)
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
	for (int i = 0; i < set_size; ++i)
	{
		swap(a[i], a[distr(eng)]);
	}

	b = a;

	std::cout << "-------------------- BUBBLE SORT --------------------\n\n";
	std::cout << "BEFORE:\n";
	std::cout << b;
	bubble_sort(b);

	std::cout << "AFTER:\n";
	std::cout << b;

	b = a;
	std::cout << "-------------------- INSERTION SORT --------------------\n\n";
	std::cout << "BEFORE:\n";
	std::cout << b;
	insertion_sort(b);

	std::cout << "AFTER:\n";
	std::cout << b;

	b = a;
	std::cout << "------------------- SPIN THE BOTTLE -------------------\n\n";
	std::cout << "BEFORE:\n";
	std::cout << b;

	spin_the_bottle_sort(b);

	std::cout << "AFTER:\n";
	std::cout << b;

	b = a;
	std::cout << "------------------- SHELL SORT -------------------\n\n";
	std::cout << "BEFORE:\n";
	std::cout << b;
	
	std::vector<int> gaps;
	shell_sequence(gaps, set_size);
	std::cout << gaps;
	shell_sort(b, gaps);
	
	std::cout << "AFTER:\n";
	std::cout << b;

	
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
