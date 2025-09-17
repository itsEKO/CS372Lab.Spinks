#pragma once

template <typename T>
class CircularList{
private:
    class Node {
    public:
        T  data;
        Node* prev;
        Node* next;
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
            temp = current.next;
            delete current;
            current = temp;
        }
    }

    public:
    CircularList() : head(nullptr), tail(nullptr)  {}

    CircularList(T newData) {
        setupList();
        head->data = newData;
    }

    CircularList(CircularList& rhs) { // copy constructor
        deleteListContents();
        head = rhs.head;
        tail = rhs.tail;
    }

    ~CircularList() {// And a destructor
        deleteListContents();
    }

    bool  empty(){
        return head == tail;
    }

    void push_front(T data) {
        Node* newNode = new Node();
        newNode->data = data;
        newNode->next = head;
        newNode->prev = nullptr;
        head = newNode;
    }

    void push_back(T data) {
        Node* newNode = new Node();
        newNode->data = data;
        newNode->next = nullptr;
        newNode->prev = tail;
        tail = newNode;
    }
    T front() {
    return (head->data);
    }
    T back() {
    return (tail->data);
    }
    void pop_back() {
        Node *lastNode = tail;
        tail = tail.prev;
        tail.next = nullptr;
        delete lastNode;
    }

    void pop_front() {
        Node *firstNode = head;
        head = head.next;
        head.prev = nullptr;
        delete firstNode;
    }

    void traverse(std::function<void(T &)> doIt) {
    Node* current = head;
    if (head == tail){
        doIt(head->data);
    }
    while(current != head){
        doIt(current->data);
        current = current->next;
    }
    doIt(tail->data);
};

