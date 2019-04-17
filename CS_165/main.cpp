#include "project1.h"

#include <iostream>
#include <ctime>
#include <random>

void swap(int& a, int& b);
void print(int* a, int size);
int* copy(int* a, int* b, int size); // copy a INTO b
void test_set(int* a, int* b, int test_size);
void test_bubble(int* a, int size);

const int SMALL_SET = 100;
const int MEDIUM_SET = 1000;
const int LARGE_SET = 10000;
const int EVEN_LARGER_SET = 100000;
const int PHAT_ASS_SET = 1000000;

int main()
{
	int* a = new int[PHAT_ASS_SET];
	int* b = new int[PHAT_ASS_SET];
	test_set(a, b, SMALL_SET);
	test_set(a, b, MEDIUM_SET);
	test_set(a, b, LARGE_SET);
	test_set(a, b, EVEN_LARGER_SET);
	test_set(a, b, PHAT_ASS_SET);

	system("pause");
	return 0;
}

void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

void print(int* a, int size)
{
	for (int i = 0; i < size; ++i)
	{
		std::cout << a[i] << " ";
	}
	std::cout << "\n\n\n";
}

// copy a INTO b
int* copy(int* a, int* b, int size)
{
	for (int i = 0; i < size; ++i)
	{
		b[i] = a[i];
	}
	return b;
}

void test_set(int* a, int* b, int set_size)
{
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

	b = copy(a, b, set_size);
	copy(a, b, set_size);

	std::cout << "-------------------- BUBBLE SORT --------------------\n\n";
	std::cout << "BEFORE:\n";
	print(b, set_size);

	test_bubble(b, set_size);

	std::cout << "AFTER:\n";
	print(b, set_size);

	copy(a, b, set_size);
	std::cout << "-------------------- INSERTION SORT --------------------\n\n";
	std::cout << "BEFORE:\n";
	print(b, set_size);

	insertion_sort(b, set_size);

	std::cout << "AFTER:\n";
	print(b, set_size);
}

void test_bubble(int* a, int size)
{
	bubble_sort(a, size);
}