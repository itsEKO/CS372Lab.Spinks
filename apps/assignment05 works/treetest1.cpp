#include <queue>
#include "Tree.hpp" 

template<typename T>
void levelOrder(const Tree<T>& tree, std::function<void(T)> visit) {
    if (tree.isEmpty()) {
        return;
    }
    std::queue<std::shared_ptr<const typename Tree<T>::Node>> q;
    q.push(tree._root); // starts with root node

    while (!q.empty()) {
        auto current = q.front();
        q.pop();

        visit(current->_val);

        if (current->_lft) {
            q.push(current->_lft);
        }
        if (current->_rgt) {
            q.push(current->_rgt);
        }
    }
}