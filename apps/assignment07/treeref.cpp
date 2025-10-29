#include <random>
#include <ctime>
#include <Tree.hpp>

Tree<int> randomTree(size_t count) {
    static std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
<<<<<<< HEAD
    std::uniform_int_distribution<int> dist(0, 1000); 
=======
    std::uniform_int_distribution<int> dist(0, 1000);
>>>>>>> origin/main

    Tree<int> tree;
    for (size_t i = 0; i < count; ++i) {
        int value = dist(rng);
<<<<<<< HEAD
        tree = tree.insert(value); 
=======
        tree = tree.insert(value);
>>>>>>> origin/main
    }
    return tree;
}

int main() {
    Tree<int> t = randomTree(10);
    std::cout << "Random BST with 10 nodes: " << t << std::endl;

    return 0;
}