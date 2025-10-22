#include "Tree.hpp"

template<typename T>
Tree<T> prune(const Tree<T>& tree) {
    if (tree.isEmpty()) {
        return Tree<T>();
    }
    struct PruneHelper {
        static std::shared_ptr<const typename Tree<T>::Node> pruneNode(
            std::shared_ptr<const typename Tree<T>::Node> node) {
            if (!node) {
                return nullptr;
            }
            if (!node->_lft && !node->_rgt) {
                return nullptr;
            }
            auto newLeft = pruneNode(node->_lft);
            auto newRight = pruneNode(node->_rgt);

            if (!newLeft && !newRight) {
                return nullptr;
            }
            return std::make_shared<const typename Tree<T>::Node>(newLeft, node->_val, newRight, nullptr);
        }
    };
    return Tree<T>(PruneHelper::pruneNode(tree._root));
}