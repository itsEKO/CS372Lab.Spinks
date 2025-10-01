#pragma once
#include <iostream>
#include <cstdlib> 

template <typename T>
class Vector {
private:
    class VectorIterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = T*;
        using reference         = T&;

        VectorIterator() : m_ptr(nullptr) {}
        VectorIterator(pointer ptr) : m_ptr(ptr) {}

        reference operator*() const { 
            return *m_ptr; 
        }

        VectorIterator& operator++() { 
            m_ptr++; 
            return *this; 
        }

        VectorIterator operator++(int) { 
            VectorIterator tmp = *this; 
            ++(*this); 
            return tmp; 
        }
        
        bool operator==(const VectorIterator& other) const { 
            return m_ptr == other.m_ptr; 
        }

        bool operator!=(const VectorIterator& other) const { 
            return m_ptr != other.m_ptr; 
        }

        
        VectorIterator operator+(difference_type n) const {
            return VectorIterator(m_ptr + n);
        }

        difference_type operator-(const VectorIterator& other) const {
            return m_ptr - other.m_ptr;
        }

    private:
        pointer m_ptr;
    };
    
public:
    using iterator = VectorIterator;

    Vector() : arr(new T[1]), vCapacity(1), length(0) {}
    
    // Copy Constructor
    Vector(const Vector& obj) : arr(new T[obj.vCapacity]), vCapacity(obj.vCapacity), length(obj.length) {
        for (int i = 0; i < obj.length; i++) {
            this->arr[i] = obj.arr[i];
        }
    }
    
    ~Vector() {
        delete [] arr;
        arr = nullptr;
    }


    iterator begin() {
        return iterator(arr);
    }

    iterator end() {
        return iterator(arr + length);
    }
    

    void put(T data, int index) {
        if (index == vCapacity) {
            push_back(data);
        }
        else {
            arr[index] = data;
        }
    }

    void push_back(T data) {
        // if number of elements is equal to capacity
        // than we need to reallocate and deep copy
        if (length == vCapacity) {
            expand(2 * vCapacity);
        }
        arr[length] = data;
        length++;
    }

    T &at(int index) {
        if (index < 0 || index >= length) { 
            std::cerr << "Vector: index out of bounds on access" << std::endl;
            exit(1);
        }
        else {
            return arr[index];
        }
    }
    
    T at(int index) const {
        if (index < 0 || index >= length) {
            std::cerr << "Vector: index out of bounds on const access" << std::endl;
            exit(1);
        }
        return arr[index];
    }
    
    T get(int index) const {
        return at(index);
    }

    int size() const {
        return length;
    }

    int capacity() const {
        return vCapacity;
    }

    void traverse() {
        for (int i = 0; i < length; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }

	bool operator==(Vector& other) const {
		if (other.size() != length) {
			return false;
		}
		else {
			for (int i = 0; i < length; i++) {
				if (arr[i] != other.get(i)) {
					return false;
				}
			}
		}
		return true;
	};

    T& operator[](int i) {
        if ((i < 0) || (i >= length)) {
            std::cerr << std::endl << "Vector index out of bounds" << std::endl;
        }
        return at(i); 
    }

    Vector& operator=(const Vector& source) {
        if (this == &source) {
            return *this;
        }
        
        Vector temp = source;
        
        std::swap(arr, temp.arr);
        std::swap(vCapacity, temp.vCapacity);
        std::swap(length, temp.length);
        
        return *this;
    }
    
private:
    T *arr;
    int vCapacity;
    int length;

    void expand(int newCapacity) {
        if (newCapacity > vCapacity) {
            T *temp = new T[newCapacity];
            for (int i = 0; i < length; i++) {
                temp[i] = arr[i];
            }
            delete[] arr;
            vCapacity = newCapacity;
            arr = temp;
        }
        else {
            std::cerr << "vector::expand: new capacity is less than equal to current\n";
        }
    }
};


