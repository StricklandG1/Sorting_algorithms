#ifndef INVERSIONS_H
#define INVERSIONS_H
#include <vector>

int _mergeSort(std::vector<int>& arr, std::vector<int>& temp, int left, int right);
int merge(std::vector<int>& arr, std::vector<int>& temp, int left, int mid, int right);

int mergeSort(std::vector<int>& arr);


#endif