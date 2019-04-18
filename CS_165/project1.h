#ifndef PROJECT1_H
#define PROJECT1_H

#include<vector>

void bubble_sort(std::vector<int>& a);
void insertion_sort(std::vector<int>& a);
void spin_the_bottle_sort(std::vector<int>& a);
void shell_sort(std::vector<int>& a, std::vector<int>& gaps);
void annealing_sort(std::vector<int>& a, std::vector<int>& temps, std::vector<int>& reps);

#endif