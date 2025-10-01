#pragma once
#include <functional>
#include <iostream>
#include <stdexcept>
#include <utility> 

template <typename T>
class List {
private:
    class Node {
    public:
        T data;
        Node* prev;
        Node* next;
        bool isDeleted; // Flag to  know if deleted

        Node(const T& d = T(), Node* p = nullptr, Node* n = nullptr)
            : data(d), prev(p), next(n), isDeleted(false) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    int activeCount = 0;   
    int deletedCount = 0;  // # of deleted items

    void deleteListContents() {
        Node* current = head;
        Node* temp = nullptr;
        while (current != nullptr) {
            temp = current->next; 
            delete current;
            current = temp;
        }
        head = tail = nullptr;
        activeCount = 0;
        deletedCount = 0;
    }

    void cleanup_deleted_nodes() {
        if (deletedCount == 0) return;

        std::cout << "\n--- CLEANUP TRIGGERED: Physically deleting " << deletedCount << " ghost nodes. ---\n";
        
        Node* current = head;
        Node* next_node = nullptr;

        while (current != nullptr) {
            next_node = current->next; 

            if (current->isDeleted) {
                if (current->prev) {
                    current->prev->next = current->next;
                } else {
                    head = current->next;
                }

                if (current->next) {
                    current->next->prev = current->prev;
                } else {
                    tail = current->prev;
                }

                delete current;
            }
            current = next_node; 
        }

        deletedCount = 0; 
        std::cout << "--- Cleanup Complete. Active items remaining: " << activeCount << " ---\n";
    }

public:
    List() = default;

    List(T newData) {
        push_back(newData); 
    }

    List(const List& rhs) { 
        Node* current = rhs.head;
        while (current != nullptr) {
            if (!current->isDeleted) {
                push_back(current->data);
            }
            current = current->next;
        }
    }

    List& operator=(const List& rhs) {
        if (this != &rhs) {
            List temp(rhs);
            std::swap(head, temp.head);
            std::swap(tail, temp.tail);
            std::swap(activeCount, temp.activeCount);
            std::swap(deletedCount, temp.deletedCount);
        }
        return *this;
    }

    ~List() {
        deleteListContents();
    }
    bool empty() const {
        return activeCount == 0; 
    }
        int size() const {
        return activeCount + deletedCount;
    }
        int active_size() const {
        return activeCount;
    }
        int ghost_size() const {
        return deletedCount;
    }

    T front() {
        Node* current = head;
        while (current != nullptr && current->isDeleted) {
            current = current->next;
        }
        if (current == nullptr) {
            throw std::runtime_error("List is logically empty (no active items)");
        }
        return current->data;
    }

    T back() {
        Node* current = tail; 
        while (current != nullptr && current->isDeleted) {
            current = current->prev;
        }
        if (current == nullptr) {
            throw std::runtime_error("List is logically empty (no active items)");
        }
        return current->data;
    }

    void push_front(T data) {
        Node* newNode = new Node(data);
        newNode->next = head;
        newNode->prev = nullptr;
        if (head) head->prev = newNode;
        head = newNode;
        if (!tail) tail = newNode;
        
        activeCount++; 
    }

    void push_back(T data) { 
        Node* newNode = new Node(data);
        newNode->next = nullptr;
        newNode->prev = tail;
        if (tail) tail->next = newNode;
        tail = newNode;
        if (!head) head = newNode;
        
        activeCount++; 
    }

    void pop_front() {
        if (empty()) return;

        Node* nodeToRemove = head;
        while (nodeToRemove != nullptr && nodeToRemove->isDeleted) {
            nodeToRemove = nodeToRemove->next;
        }

        if (nodeToRemove == nullptr) return; 

        if (nodeToRemove->prev) nodeToRemove->prev->next = nodeToRemove->next;
        else head = nodeToRemove->next; 

        if (nodeToRemove->next) nodeToRemove->next->prev = nodeToRemove->prev;
        else tail = nodeToRemove->prev; 

        delete nodeToRemove;
        activeCount--;
        
        if (deletedCount == activeCount) {
             cleanup_deleted_nodes();
        }
    }

    void pop_back() {
        if (empty()) return; 

        Node* nodeToRemove = tail;
        while (nodeToRemove != nullptr && nodeToRemove->isDeleted) {
            nodeToRemove = nodeToRemove->prev;
        }
        
        if (nodeToRemove == nullptr) return; 

        if (nodeToRemove->prev) nodeToRemove->prev->next = nodeToRemove->next;
        else head = nodeToRemove->next; 

        if (nodeToRemove->next) nodeToRemove->next->prev = nodeToRemove->prev;
        else tail = nodeToRemove->prev; 

        delete nodeToRemove;
        activeCount--;
        
        if (deletedCount == activeCount) {
             cleanup_deleted_nodes();
        }
    }

    void lazy_remove(const T& data) {
        if (activeCount == 0) return;

        Node* current = head;
        while (current != nullptr) {
            if (!current->isDeleted && current->data == data) {
                current->isDeleted = true;
                deletedCount++;
                activeCount--; 

                if (deletedCount == activeCount) {
                    cleanup_deleted_nodes();
                }
                return; 
            }
            current = current->next;
        }
    }

    void traverse(std::function<void(T&)> doIt) {
        Node* current = head;
        while (current != nullptr) {
            if (!current->isDeleted) {
                doIt(current->data);
            }
            current = current->next;
        }
    }
};


