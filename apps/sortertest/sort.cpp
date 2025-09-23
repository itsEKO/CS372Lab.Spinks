#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>
#include <functional>
#include "sorter.hpp"

// Fills a vector with random integers
void fillRandom(std::vector<int>& vec, int size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);
    vec.resize(size);
    for (int i = 0; i < size; ++i) {
        vec[i] = dis(gen);
    }
}

int main() {
    Sorter<int> sorter;
    
    // Define the sort functions to be timed
    std::vector<std::pair<std::string, std::function<void(std::vector<int>&)>>> sorts = {
        {"Selection Sort", [&](std::vector<int>& v) { sorter.selectionSort(v); }},
        {"Bubble Sort", [&](std::vector<int>& v) { sorter.bubbleSort(v); }},
        {"Insertion Sort", [&](std::vector<int>& v) { sorter.insertionSort(v); }},
        {"Quicksort", [&](std::vector<int>& v) { sorter.quicksort(v, 0, v.size() - 1); }}
    };

    // Vector sizes to test
    std::vector<int> sizes = {10, 50, 100, 500, 1000, 5000, 10000, 50000, 100000, 250000};

    // Print table header
    std::cout << std::setw(15) << "N" << std::setw(25) << "Selection Sort (ms)"
              << std::setw(25) << "Bubble Sort (ms)" << std::setw(25) << "Insertion Sort (ms)"
              << std::setw(25) << "Quicksort (ms)" << std::endl;
    std::cout << std::string(115, '-') << std::endl;

    for (int n : sizes) {
        std::cout << std::setw(15) << n;
        for (const auto& sort_pair : sorts) {
            std::vector<int> data;
            fillRandom(data, n);
            
            auto start = std::chrono::high_resolution_clock::now();
            sort_pair.second(data); // Call the sort function
            auto end = std::chrono::high_resolution_clock::now();
            
            std::chrono::duration<double, std::milli> duration = end - start;
            std::cout << std::setw(25) << std::fixed << std::setprecision(3) << duration.count();
        }
        std::cout << std::endl;
    }

    return 0;
}