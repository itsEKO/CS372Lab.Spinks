#include <iostream>
#include <chrono>
#include <memory>
#include <algorithm>
#include <cmath>
#include <string>

template<typename T>
class VectorBase {
public:
    virtual ~VectorBase() {}
    virtual void push_back(const T& value) = 0;
    virtual int size() const = 0;
};

template <typename T>
class Vector : public VectorBase<T> {
protected:
    T* arr;
    int length;
    int vCapacity;

    virtual void expand() {
        int newCapacity = (vCapacity == 0) ? 1 : vCapacity * 2;
        T* temp = new T[newCapacity];
        
        for (int i = 0; i < length; ++i) {
            temp[i] = arr[i];
        }

        delete[] arr;
        vCapacity = newCapacity;
        arr = temp;
    }

public:
    Vector() : arr(new T[1]), length(0), vCapacity(1) {}

    ~Vector() {
        delete[] arr;
    }

    void push_back(const T& data) override {
        if (length == vCapacity) {
            expand();
        }
        arr[length] = data;
        length++;
    }

    int size() const override {
        return length;
    }
};

template <typename T>
class VectorSTL : public Vector<T> {
protected:
    void expand() override {
        int newCapacity = (this->vCapacity == 0) ? 1 : this->vCapacity * 2;
        T* temp = new T[newCapacity];

        std::copy(this->arr, this->arr + this->length, temp);

        delete[] this->arr;
        this->vCapacity = newCapacity;
        this->arr = temp;
    }

public:
    VectorSTL() : Vector<T>() {}
};

template <typename T>
class VectorOptimized : public Vector<T> {
protected:
    void expand() override {
        int newCapacity;
        if (this->vCapacity == 0) {
            newCapacity = 128;
        } else {
            newCapacity = this->vCapacity * 4;
        }
        
        T* temp = new T[newCapacity];
        std::copy(this->arr, this->arr + this->length, temp);

        delete[] this->arr;
        this->vCapacity = newCapacity;
        this->arr = temp;
    }

public:
    VectorOptimized() : Vector<T>() {}
};


template <typename T>
void timeVectorGrowth(VectorBase<T>& vec, const std::string& name) {
    std::cout << "--- " << name << " Timings ---" << std::endl;
    int numElementsToAdd = 2;

    for (int i = 0; i < 22; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        
        for (int j = 0; j < numElementsToAdd; ++j) {
            vec.push_back(j);
        }

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        
        std::cout << "Added " << numElementsToAdd << " elements. Total elements: " 
                  << vec.size() << ". Time taken: " << duration.count() 
                  << " ms." << std::endl;
        
        numElementsToAdd *= 2;
    }
    std::cout << std::endl;
}

int main() {
    Vector<int> vecForLoop;
    timeVectorGrowth(vecForLoop, "Vector with For-Loop Copy");

    VectorSTL<int> vecSTL;
    timeVectorGrowth(vecSTL, "Vector with std::copy");

    VectorOptimized<int> vecOptimized;
    timeVectorGrowth(vecOptimized, "Vector with Larger Initial Capacity and Quadrupling");

    return 0;
}
