#pragma once
#include <iostream>
#include <functional>
#include "listclass.h" // my list class

template <typename T>
class Bag {
private:
    List<T> list; 
    int length; 

public:
    Bag() : length(0) {
        // List constructor initializes an empty list
    }

    Bag(T newData) : length(1) {
        list = List<T>(newData); 
    }

    // Copy constructor
    Bag(const Bag& rhs) : list(rhs.list), length(rhs.length) {
    }

    Bag& operator=(const Bag& rhs) {
        if (this != &rhs) {
            list = rhs.list; 
            length = rhs.length;
        }
        return *this;
    }

    // Destructor
    ~Bag() {}

    void put(T data, int pos) {
        if (pos < 0 || pos > length) {
            std::cerr << "Bag: index out of bounds in put" << std::endl;
            exit(1);
        }
        if (pos == length) {
            push_back(data);
        } else {
            typename List<T>::Node* current = list.head;
            for (int i = 0; i < pos; ++i) {
                current = current->next;
            }
            typename List<T>::Node* newNode = new typename List<T>::Node();
            newNode->data = data;
            newNode->next = current;
            newNode->prev = current->prev;
            if (current->prev) {
                current->prev->next = newNode;
            } else {
                list.head = newNode;
            }
            current->prev = newNode;
            length++;
        }
    }

    void push_back(T data) {
        list.push_back(data);
        length++;
    }

    T& at(int index) {
        if (index < 0 || index >= length) {
            std::cerr << "Bag: index out of bounds on access" << std::endl;
            exit(1);
        }
        typename List<T>::Node* current = list.head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    int size() {
        return length;
    }

    void traverse() {
        list.traverse([](T& data) {
            std::cout << data << std::endl;
        });
        std::cout << std::endl;
    }
};
```