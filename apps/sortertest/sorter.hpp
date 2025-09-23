#include <vector>
#include <algorithm>
#include <random>

template <typename T>
class Sorter {
public:
    void selectionSort(std::vector<T>& arr);
    void bubbleSort(std::vector<T>& arr);
    void insertionSort(std::vector<T>& arr);
    void quicksort(std::vector<T>& arr, int low, int high); 
private:
    int partition(std::vector<T>& arr, int low, int high);
};

template <typename T>
void Sorter<T>::selectionSort(std::vector<T>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        std::swap(arr[min_idx], arr[i]);
    }
}

// bubbleSort
template <typename T>
void Sorter<T>::bubbleSort(std::vector<T>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// insertionSort
template <typename T>
void Sorter<T>::insertionSort(std::vector<T>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// quicksort
template <typename T>
void Sorter<T>::quicksort(std::vector<T>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

// partition
template <typename T>
int Sorter<T>::partition(std::vector<T>& arr, int low, int high) {
    T pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}