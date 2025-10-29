#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include "Tree.hpp"
#include "avltree.hpp"

using namespace std::chrono;

std::pair<double,double>& measureSearchTimes(
        const Tree<int>&    bst,
        const AVLTree<int>& avl)
{
    std::vector<int> values;
    values.reserve(bst.size());
    bst.inorder([&values](int v){ values.push_back(v); });

    if (values.empty()) {
        static std::pair<double,double> zero{0.0,0.0};
        return zero;
    }

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<std::size_t> dist(0, values.size() - 1);

    constexpr int TRIALS = 100;
    std::vector<int> queries(TRIALS);
    for (int i = 0; i < TRIALS; ++i)
        queries[i] = values[dist(rng)];

    double bstTotal = 0.0, avlTotal = 0.0;
    for (int key : queries) {
        auto t0 = steady_clock::now();
        [[maybe_unused]] bool f1 = bst.member(key);
        auto t1 = steady_clock::now();
        bstTotal += duration_cast<nanoseconds>(t1-t0).count();

        auto t2 = steady_clock::now();
        [[maybe_unused]] bool f2 = avl.contains(key);
        auto t3 = steady_clock::now();
        avlTotal += duration_cast<nanoseconds>(t3-t2).count();
    }

    static std::pair<double,double> result;
    result.first  = bstTotal / TRIALS;
    result.second = avlTotal / TRIALS;
    return result;
}

int main()
{
    std::vector<size_t> sizes = {100, 500, 1000, 2500, 5000, 10000};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 1000000);

    std::cout << "Elements | BST Avg (ns) | AVL Avg (ns)\n";
    std::cout << "---------|--------------|-------------\n";

    for (size_t n : sizes) {
        std::vector<int> values(n);
        for (size_t i = 0; i < n; ++i)
            values[i] = dist(gen);

        Tree<int> bst;
        AVLTree<int> avl;

        for (int v : values) {
            bst = bst.insert(v);
            avl.insert(v);
        }

        auto& avg = measureSearchTimes(bst, avl);
        std::cout << n << " | " << avg.first << " | " << avg.second << "\n";
    }

    return 0;
}