#include "Sort.hpp"

int main() {
    vector<int> arr = {9, 2, 1, 10, 7, 4};
    Sort::printArr(arr);
	Sort::hoareSort(arr);
    Sort::printArr(arr);
    return 0;
}
