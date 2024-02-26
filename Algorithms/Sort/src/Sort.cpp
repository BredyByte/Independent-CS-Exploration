#include "Sort.hpp"

void Sort::bubbleSort(vector<int>& arr) {
    int length = arr.size();
    while (length != 0) {
        int max_index = 0;
        for(int i = 1; i < length; i++){
            if (arr[i - 1] > arr[i]) {
                swap(arr[i - 1], arr[i]);
                max_index = i;
            }
        }
        length = max_index;
    }

}

void Sort::selectionSort(vector<int>& arr) {
    int length = arr.size();
    for (int i = 0; i < length - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < length; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            swap(arr[i], arr[min_index]);
        }
    }
}

void Sort::insertionSort(vector<int>& arr) {
    int length = arr.size();
    for (int i = 1; i < length; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }

}

int hoarePartition(vector<int>& arr, int low, int high) {
    int pivot = arr[(low + high) / 2];
    int i = low - 1;
    int j = high + 1;
    while (true) {
        do {
            i++;
        } while (arr[i] < pivot);

        do {
            j--;
        } while (arr[j] > pivot);

        if (i >= j)
            return j;

        swap(arr[i], arr[j]);
    }
}

void hoareSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = hoarePartition(arr, low, high);
        ::hoareSort(arr, low, pi);
        ::hoareSort(arr, pi + 1, high);
    }
}

void Sort::hoareSort(vector<int>& arr) {
    ::hoareSort(arr, 0, arr.size() - 1);
}

void Sort::printArr(const vector<int>& arr) {
    for (size_t i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
