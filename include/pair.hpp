#pragma once
#include <compare>

template <typename KeyType, typename ValueType>
struct Pair { 
public:
  KeyType first;
  ValueType second;

  Pair() = delete;
  Pair(KeyType x, ValueType y): first(x), second(y) {}

  auto operator<=>(const Pair&) const = default;
};

template <typename KeyType, typename ValueType>
Pair<KeyType, ValueType> MakePair(KeyType first, ValueType second) {
  return Pair<KeyType, ValueType>(first, second);
}