#include <cstddef>
#include <stdexcept>
#include <initializer_list>
#include <utility>

template <typename T, size_t N>
class Array {
public:
    using value_type = T;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using iterator = T*;
    using const_iterator = const T*;

    Array() = default;

    Array(std::initializer_list<T> init) {
        if (init.size() > N) {
            throw std::out_of_range("Initializer list size exceeds array capacity.");
        }
        size_t i = 0;
        for (const auto& item : init) {
            data_[i++] = item;
        }
    }

    reference at(size_type pos) {
        if (pos >= N) {
            throw std::out_of_range("Array index out of bounds.");
        }
        return data_[pos];
    }
    const_reference at(size_type pos) const {
        if (pos >= N) {
            throw std::out_of_range("Array index out of bounds.");
        }
        return data_[pos];
    }

    reference operator[](size_type pos) {
        return data_[pos];
    }
    const_reference operator[](size_type pos) const {
        return data_[pos];
    }

    reference front() {
        return data_[0];
    }
    const_reference front() const {
        return data_[0];
    }

    reference back() {
        return data_[N - 1];
    }
    const_reference back() const {
        return data_[N - 1];
    }

    pointer data() noexcept {
        return data_;
    }
    const_pointer data() const noexcept {
        return data_;
    }

    iterator begin() noexcept {
        return data_;
    }
    const_iterator begin() const noexcept {
        return data_;
    }

    iterator end() noexcept {
        return data_ + N;
    }
    const_iterator end() const noexcept {
        return data_ + N;
    }

    constexpr size_type size() const noexcept {
        return N;
    }
    
    constexpr size_type max_size() const noexcept {
        return N;
    }

    constexpr bool empty() const noexcept {
        return N == 0;
    }

    void fill(const T& value) {
        for (size_type i = 0; i < N; ++i) {
            data_[i] = value;
        }
    }

    void swap(Array& other) noexcept {
        for (size_type i = 0; i < N; ++i) {
            std::swap(data_[i], other.data_[i]);
        }
    }

private:
    T data_[N];
};