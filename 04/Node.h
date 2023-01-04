//
// Created by Mali Abramovitch on 04/01/2023.
//

#ifndef INC_04_NODE_H
#define INC_04_NODE_H

#include <ostream>

template<class T>
class Node {
private:
    Node<T> *next, prev;
    T *data;
public:
    explicit Node(T *data); // default C'tor
    explicit Node(T *data, Node<T>* next, Node<T>* prev); // default C'tor
    Node(const Node<T> &other); // copy C'tor
    Node(Node<T> &&other) noexcept; // copy C'tor
    ~Node(); // D'tor
    Node<T> &operator=(const Node<T> &other) noexcept; // copy assignment =
    Node<T> &operator=(Node<T> &&other) noexcept; // copy assignment =

    inline Node *getPrev() { return prev; }

    inline void setPrev() { this->prev = prev; }

    inline Node *getNext() { return next; };

    inline void setNext() { this->next = next; };

    inline T *getData() { return data; }

    inline void setData() { this->data = data; }

    bool operator<(const Node<T>& other);
    bool operator>(const Node<T>& other);
    bool operator==(const Node<T>& other);


    friend std::ostream &operator<<(std::ostream &os, Node<T> &node);
};

template<class T>
Node<T>::Node(T *data) : next(nullptr), prev(nullptr), data(new T(data)) {}


template<class T>
Node<T>::Node(T *data, Node<T> *next, Node<T> *prev) : next(next), prev(prev), data(new T(data)) {}

template<class T>
Node<T>::Node(const Node<T> &other) {
    prev = new Node<T>();
    prev = other.prev;
    next = new Node<T>();
    next = other.next;
    data = new T();
    data = other.data;
}

template<class T>
Node<T>::Node(Node<T> &&other) noexcept {
    this->next = other.next;
    this->prev = other.prev;
    this->data = other.data;
    other.next = nullptr;
    other.prev = nullptr;
    other.data = nullptr;
}

template<class T>
Node<T>::~Node() {
    delete next;
    delete prev;
    delete data;
}

template<class T>
Node<T> &Node<T>::operator=(const Node<T> &other) noexcept {
    if (this == other) return *this;
    next = other.next;
    next = other.prev;
    next = other.data;
    return *this;
}

template<class T>
Node<T> &Node<T>::operator=(Node<T> &&other) noexcept {
    if (this == other) return *this;
    next = other.next;
    next = other.prev;
    next = other.data;
    other.next = nullptr;
    other.prev = nullptr;
    other.data = nullptr;
    return *this;
}

template<class T>
bool Node<T>::operator==(const Node<T> &other) {
    return (*data == *other.data);
}

template<class T>
bool Node<T>::operator>(const Node<T> &other) {
    return (*data > *other.data);
}

template<class T>
bool Node<T>::operator<(const Node<T> &other) {
    return (*data > *other.data);
}

template<class T>
std::ostream &operator<<(std::ostream &os, Node<T> &node) {
    os << *(node.data) << '\n';
    return os;
}

#endif //INC_04_NODE_H
