#pragma once
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>

template <typename T>
class List {
private:
    class Node {
    public:
        T data;
        Node* prev;                    
        std::unique_ptr<Node> next;   
        bool isDeleted;                

        Node(const T& d = T(), Node* p = nullptr)
            : data(d), prev(p), next(nullptr), isDeleted(false) {}
    };

    std::unique_ptr<Node> head;    
    Node* tail;                    
    int activeCount = 0;           
    int deletedCount = 0;          

    void cleanup_deleted_nodes() {
        if (deletedCount == 0) return;

        std::cout << "\n--- CLEANUP TRIGGERED: deleting " << deletedCount << " nodes. ---\n";

        Node* current = head.get();
        while (current) {
            if (current->isDeleted) {
                std::unique_ptr<Node> next_node = std::move(current->next);

                if (current->prev) {
                    current->prev->next = std::move(next_node);
                } else {
                    head = std::move(next_node);
                }

                if (current->next) {
                    current->next->prev = current->prev;
                } else {
                    tail = current->prev;
                }

                current = current->next.get();
            } else {
                current = current->next.get();
            }
        }

        deletedCount = 0;
        std::cout << "--- Cleanup Complete. Active items remaining: " << activeCount << " ---\n";
    }

public:
    List() : head(nullptr), tail(nullptr) {}

    List(const T& newData) {
        push_back(newData);
    }

    List(const List& rhs) {
        Node* current = rhs.head.get();
        while (current) {
            if (!current->isDeleted) {
                push_back(current->data);
            }
            current = current->next.get();
        }
        deletedCount = 0;
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

    ~List() = default;

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
        Node* current = head.get();
        while (current && current->isDeleted) {
            current = current->next.get();
        }
        if (!current) {
            throw std::runtime_error("List is logically empty (no active items)");
        }
        return current->data;
    }

    T back() {
        Node* current = tail;
        while (current && current->isDeleted) {
            current = current->prev;
        }
        if (!current) {
            throw std::runtime_error("List is logically empty (no active items)");
        }
        return current->data;
    }

    void push_front(const T& data) {
        std::unique_ptr<Node> newNode(new Node(data));
        newNode->next = std::move(head);
        if (newNode->next) {
            newNode->next->prev = newNode.get();
        }
        head = std::move(newNode);
        if (!tail) {
            tail = head.get();
        }
        activeCount++;
    }

    void push_back(const T& data) {
        std::unique_ptr<Node> newNode(new Node(data, tail));
        if (tail) {
            tail->next = std::move(newNode);
            tail = tail->next.get();
        } else {
            head = std::move(newNode);
            tail = head.get();
        }
        activeCount++;
    }

    void pop_front() {
        if (empty()) return;

        Node* current = head.get();
        while (current && current->isDeleted) {
            current = current->next.get();
        }
        if (!current) return;

        if (current->prev) {
            current->prev->next = std::move(current->next);
        } else {
            head = std::move(current->next);
        }
        if (current->next) {
            current->next->prev = current->prev;
        } else {
            tail = current->prev;
        }

        activeCount--;
        if (deletedCount == activeCount) {
            cleanup_deleted_nodes();
        }
    }

    void pop_back() {
        if (empty()) return;

        Node* current = tail;
        while (current && current->isDeleted) {
            current = current->prev;
        }
        if (!current) return;

        if (current->prev) {
            current->prev->next = std::move(current->next);
            tail = current->prev;
        } else {
            head = std::move(current->next);
            tail = nullptr;
        }
        if (head) {
            head->prev = nullptr;
        }

        activeCount--;
        if (deletedCount == activeCount) {
            cleanup_deleted_nodes();
        }
    }

    void lazy_remove(const T& data) {
        if (activeCount == 0) return;

        Node* current = head.get();
        while (current) {
            if (!current->isDeleted && current->data == data) {
                current->isDeleted = true;
                deletedCount++;
                activeCount--;
                if (deletedCount == activeCount) {
                    cleanup_deleted_nodes();
                }
                return;
            }
            current = current->next.get();
        }
    }

    void traverse(std::function<void(T&)> doIt) {
        Node* current = head.get();
        while (current) {
            if (!current->isDeleted) {
                doIt(current->data);
            }
            current = current->next.get();
        }
    }
};