#include <random>
#include <ctime>
#include <Tree.hpp>

// Function to generate a Tree with 'count' random integers
Tree<int> randomTree(size_t count) {
    // Use current time as seed for randomness
    static std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<int> dist(0, 1000); // Random ints in range [0, 1000]

    Tree<int> tree;
    for (size_t i = 0; i < count; ++i) {
        int value = dist(rng);
        tree = tree.insert(value); // Insert using default std::less<int> (BST order)
    }
    return tree;
}

int main() {
    Tree<int> t = randomTree(10);
    std::cout << "Random BST with 10 nodes: " << t << std::endl;

    return 0;
}