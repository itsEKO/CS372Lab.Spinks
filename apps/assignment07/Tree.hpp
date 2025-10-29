#pragma once
#include <memory>
#include <functional>
#include <cassert>
#include <initializer_list>
#include <vector>
#include <iostream>

template<typename T>
class Tree
{
    struct Node
    {
        Node(std::shared_ptr<const Node> lft, T val, std::shared_ptr<const Node> rgt, std::shared_ptr<const Node> parent)
            : _lft(lft), _val(val), _rgt(rgt), _parent(parent)
        {}

        std::shared_ptr<const Node> _lft;
        T _val;
        std::shared_ptr<const Node> _rgt;
        std::weak_ptr<const Node> _parent; 
    };

    explicit Tree(std::shared_ptr<const Node> node) : _root(node) {}

public:
    Tree() : _root(nullptr) {}
    Tree(const Tree& other) = default;
    Tree& operator=(const Tree& other) = default;
    ~Tree() = default;
    Tree(Tree&& other) = default;
    Tree& operator=(Tree&& other) = default;

    Tree(Tree lft, T val, Tree rgt)
    {
        std::shared_ptr<const Node> newLeft = lft._root
            ? std::make_shared<Node>(lft._root->_lft, lft._root->_val, lft._root->_rgt, nullptr)
            : nullptr;
        std::shared_ptr<const Node> newRight = rgt._root
            ? std::make_shared<Node>(rgt._root->_lft, rgt._root->_val, rgt._root->_rgt, nullptr)
            : nullptr;
        _root = std::make_shared<Node>(newLeft, val, newRight, nullptr);
        if (newLeft) {
            newLeft = std::make_shared<Node>(newLeft->_lft, newLeft->_val, newLeft->_rgt, _root);
        }
        if (newRight) {
            newRight = std::make_shared<Node>(newRight->_lft, newRight->_val, newRight->_rgt, _root);
        }
        if (newLeft || newRight) {
            _root = std::make_shared<Node>(newLeft, val, newRight, nullptr);
        }
    }

    Tree(std::initializer_list<T> init) {
        Tree t;
        for (T v : init) {
            t = t.insert(v);
        }
        _root = t._root;
    }

    bool isEmpty() const { return !_root; }

    size_t size() const {
        if (isEmpty()) return 0;
        return 1 + left().size() + right().size();
    }

    T root() const {
        assert(!isEmpty());
        return _root->_val;
    }

    Tree left() const {
        assert(!isEmpty());
        return Tree(_root->_lft);
    }

    Tree right() const {
        assert(!isEmpty());
        return Tree(_root->_rgt);
    }

    template <typename Compare = std::less<T>>
    Tree insert(T x, Compare comp = std::less<T>()) const {
        if (isEmpty()) {
            return Tree(std::make_shared<Node>(nullptr, x, nullptr, nullptr)); 
        }
        T y = root();
        if (comp(x, y)) {
            Tree newLeft = left().insert(x, comp);
            std::shared_ptr<const Node> newLeftNode = newLeft._root
                ? std::make_shared<Node>(newLeft._root->_lft, newLeft._root->_val, newLeft._root->_rgt, nullptr)
                : nullptr;
            std::shared_ptr<const Node> newRightNode = _root->_rgt
                ? std::make_shared<Node>(_root->_rgt->_lft, _root->_rgt->_val, _root->_rgt->_rgt, nullptr)
                : nullptr;
            auto newNode = std::make_shared<Node>(newLeftNode, y, newRightNode, nullptr);
            if (newLeftNode) {
                newLeftNode = std::make_shared<Node>(newLeftNode->_lft, newLeftNode->_val, newLeftNode->_rgt, newNode);
            }
            if (newRightNode) {
                newRightNode = std::make_shared<Node>(newRightNode->_lft, newRightNode->_val, newRightNode->_rgt, newNode);
            }
            return Tree(std::make_shared<Node>(newLeftNode, y, newRightNode, nullptr));
        }
        else if (comp(y, x)) {
            Tree newRight = right().insert(x, comp);
            std::shared_ptr<const Node> newLeftNode = _root->_lft
                ? std::make_shared<Node>(_root->_lft->_lft, _root->_lft->_val, _root->_lft->_rgt, nullptr)
                : nullptr;
            std::shared_ptr<const Node> newRightNode = newRight._root
                ? std::make_shared<Node>(newRight._root->_lft, newRight._root->_val, newRight._root->_rgt, nullptr)
                : nullptr;
            auto newNode = std::make_shared<Node>(newLeftNode, y, newRightNode, nullptr);
            if (newLeftNode) {
                newLeftNode = std::make_shared<Node>(newLeftNode->_lft, newLeftNode->_val, newLeftNode->_rgt, newNode);
            }
            if (newRightNode) {
                newRightNode = std::make_shared<Node>(newRightNode->_lft, newRightNode->_val, newRightNode->_rgt, newNode);
            }
            return Tree(std::make_shared<Node>(newLeftNode, y, newRightNode, nullptr));
        }
        else {
            return *this; 
        }
    }

    template <typename Compare = std::less<T>>
    bool member(T x, Compare comp = std::less<T>()) const {
        if (isEmpty()) {
            return false;
        }
        T y = root();
        if (comp(x, y)) {
            return left().member(x, comp);
        }
        else if (comp(y, x)) {
            return right().member(x, comp);
        }
        else {
            return true;
        }
    }

    template<typename Compare = std::less<T>>
    bool find(T x, Tree& subtreeWhereFound, Compare comp = std::less<T>()) const {
        if (isEmpty()) {
            subtreeWhereFound = Tree();
            return false;
        }
        T y = root();
        if (comp(x, y)) {
            return left().find(x, subtreeWhereFound, comp);
        }
        else if (comp(y, x)) {
            return right().find(x, subtreeWhereFound, comp);
        }
        else {
            subtreeWhereFound = *this;
            return true;
        }
    }

    std::vector<T> pathToRoot(T x) const {
        std::vector<T> path;
        if (isEmpty()) return path;

        Tree subtree;
        if (find(x, subtree)) {
            std::shared_ptr<const Node> current = subtree._root;
            while (current) {
                path.push_back(current->_val);
                current = current->_parent.lock();
            }
        }
        return path;
    }

    void preorder(std::function<void(T)> visit) const {
        if (isEmpty())
            return;
        T contents = root();
        visit(contents);
        left().preorder(visit);
        right().preorder(visit);
    }

    void inorder(std::function<void(T)> visit) const {
        if (isEmpty()) return;
        left().inorder(visit);
        T contents = root();
        visit(contents);
        right().inorder(visit);
    }

    void postorder(std::function<void(T)> visit) const {
        if (isEmpty()) return;
        left().postorder(visit);
        right().postorder(visit);
        T contents = root();
        visit(contents);
    }

private:
    std::shared_ptr<const Node> _root;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Tree<T>& tree) {
    if (tree.isEmpty()) {
        os << "[]";
        return os;
    }
    os << "[";
    tree.inorder([&os](T val) { os << val << " "; });
    os << "]";
    return os;
}

