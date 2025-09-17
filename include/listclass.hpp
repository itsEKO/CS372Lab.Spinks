#pragma once
#include <functional>
#include <iostream>

template <typename T>
class List {
private:
    class Node {
    public:
        T data;
        Node* prev;
        Node* next;
        Node(const T& d = T(), Node* p = nullptr, Node* n = nullptr) : data(d), prev(p), next(n) {}
    };
    Node* head = nullptr;
    Node* tail = nullptr;

    void setupList() {
        Node* newNode = new Node();
        newNode->next = nullptr;
        newNode->prev = nullptr;
        head = newNode;
        tail = newNode;
    }

    void deleteListContents() {
        Node* current = head;
        Node* temp = nullptr;
        while (current != nullptr) {
            temp = current->next; 
            delete current;
            current = temp;
        }
        head = tail = nullptr;
    }

public:
    List() {
        head = nullptr;
        tail = nullptr; 
    }

    List(T newData) {
        head = nullptr;
        tail = nullptr;
        push_back(newData); 
    }

    List(List& rhs) { 
        head = nullptr;
        tail = nullptr;
        Node* current = rhs.head;
        while (current != nullptr && current != rhs.tail) {
            push_back(current->data);
            current = current->next;
        }
    }

    ~List() {
        deleteListContents();
    }

    bool empty() {
        return head == nullptr; 
    }

    void push_front(T data) {
        Node* newNode = new Node(data);
        newNode->next = head;
        newNode->prev = nullptr;
        if (head) head->prev = newNode;
        head = newNode;
        if (!tail) tail = newNode;
    }

    void push_back(T data) { 
        Node* newNode = new Node(data);
        newNode->next = nullptr;
        newNode->prev = tail;
        if (tail) tail->next = newNode;
        tail = newNode;
        if (!head) head = newNode;
    }

    T front() {
        if (empty()) throw std::runtime_error("List is empty");
        return head->data;
    }

    T back() {
        if (empty()) throw std::runtime_error("List is empty");
        return tail->data;
    }

    void pop_back() {
        if (empty()) return; 
        Node* lastNode = tail;
        tail = tail->prev; 
        if (tail) tail->next = nullptr; 
        else head = nullptr;
        delete lastNode;
    }

    void pop_front() {
        if (empty()) return; 
        Node* firstNode = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete firstNode;
    }

    void traverse(std::function<void(T&)> doIt) {
        Node* current = head;
        while (current != nullptr) {
            doIt(current->data);
            current = current->next;
        }
    }
};