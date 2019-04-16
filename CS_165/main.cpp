#include "project1.h"

#include <iostream>
#include <ctime>
#include <random>

void swap(int& a, int& b);
void print(int* a, int size);

int main()
{
	int size = 10;
	int* a = new int[size];
	for (int i = 0; i < size; ++i)
	{
		a[i] = i + 1;
	}

	print(a, size);

	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(0, size - 1);
	for (int i = 0; i < size; ++i)
	{
		swap(a[i], a[distr(eng)]);
	}

	print(a, size);

	delete[] a;

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
	std::cout << std::endl;
}