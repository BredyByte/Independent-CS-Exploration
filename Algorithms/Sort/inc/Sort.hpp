#ifndef SORT_HPP
#define SORT_HPP

#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

class Sort {
	public:
		static void printArr(const vector<int>&);
		static void bubbleSort(vector<int>&);
		static void selectionSort(vector<int>&);
		static void insertionSort(vector<int>&);
		static void hoareSort(vector<int>&);
};

#endif
