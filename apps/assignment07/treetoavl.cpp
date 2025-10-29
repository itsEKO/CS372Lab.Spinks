#include "Tree.hpp"
#include "avltree.hpp"

AVLTree<int>& treeToAVL(const Tree<int>& tree) {
    auto* avl = new AVLTree<int>();  

    tree.inorder([&avl](int value) {
        avl->insert(value);
    });

    return *avl;
}

int main() {
    Tree<int> bst = Tree<int>{}.insert(5).insert(3).insert(7).insert(1).insert(4);
    AVLTree<int>& avl = treeToAVL(bst);
    std::cout << "AVL Tree (in-order): ";
    avl.display(); 
    
    delete &avl; 
    return 0;
}