#pragma once
#include <functional>
#include <stdexcept>
#include <optional>
#include "pair.hpp"
#include "Tree.hpp"
#include "listclass.hpp"

template <typename KeyType, typename ValueType>
class Dictionary {
private:
    using KV = Pair<KeyType, ValueType>;

    Tree<KV> tree_;

    static auto key_less() {
        return [](const KV& a, const KV& b) { return a.first < b.first; };
    }

public:
    Dictionary() = default;

    Dictionary(const Dictionary&) = default;
    Dictionary& operator=(const Dictionary&) = default;

    Dictionary(Dictionary&&) noexcept = default;
    Dictionary& operator=(Dictionary&&) noexcept = default;

    ~Dictionary() = default;

    [[nodiscard]] bool isEmpty() const noexcept { return tree_.isEmpty(); }
    [[nodiscard]] size_t size() const noexcept { return tree_.size(); }

    void insert(const KeyType& k, const ValueType& v) {
        tree_ = tree_.insert(MakePair(k, v), key_less());
    }

    void erase(const KeyType& k) {
        if (tree_.isEmpty()) return;

        Tree<KV> found;
        if (!tree_.find(MakePair(k, ValueType()), found, key_less()))
            return;                     

        Dictionary temp;
        tree_.inorder([&](const KV& p) {
            if (!(p.first == k))               
                temp.insert(p.first, p.second);
        });
        tree_ = std::move(temp.tree_);
    }

    void clear() noexcept { tree_ = Tree<KV>{}; }

    ValueType& at(const KeyType& k) {
        Tree<KV> found;
        if (!tree_.find(MakePair(k, ValueType()), found, key_less()))
            throw std::out_of_range("Dictionary::at: key not found");

        return const_cast<ValueType&>(found.root().second);
    }

    const ValueType& at(const KeyType& k) const {
        Tree<KV> found;
        if (!tree_.find(MakePair(k, ValueType()), found, key_less()))
            throw std::out_of_range("Dictionary::at: key not found");

        return found.root().second;
    }

    ValueType& operator[](const KeyType& k) {
        Tree<KV> found;
        if (tree_.find(MakePair(k, ValueType()), found, key_less())) {
            return const_cast<ValueType&>(found.root().second);
        }
        insert(k, ValueType{});
        return at(k);
    }

    [[nodiscard]] List<KeyType>& keys() const {
        auto* lst = new List<KeyType>;
        tree_.inorder([&](const KV& p) { lst->push_back(p.first); });
        return *lst;                
    }

    [[nodiscard]] List<ValueType>& values() const {
        auto* lst = new List<ValueType>;
        tree_.inorder([&](const KV& p) { lst->push_back(p.second); });
        return *lst;                
    }
};
