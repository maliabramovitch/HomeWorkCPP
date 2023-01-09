//
// Created by Mali Abramovitch on 07/01/2023.
//

#ifndef INC_14_NODE_H
#define INC_14_NODE_H

#include <ostream>

template<class T>
class Node {
private:
    Node<T> *next;
    Node<T> *prev;
    T* data;
public:
    explicit Node(T* data); // default C'tor
    Node(T* data, Node<T>* next, Node<T>* prev); // default C'tor
    Node(const Node<T> &other); // copy C'tor
    Node(Node<T> &&other) noexcept; // copy C'tor
    ~Node(); // D'tor
    Node<T> &operator=(const Node<T> &other) noexcept; // copy assignment =
    Node<T> &operator=(Node<T> &&other) noexcept; // copy assignment =

    Node<T>* getPrev() const;
    void setPrev(Node<T>* prevv);

    Node<T>* getNext() const;
    void setNext(Node<T>* nextt);

    T* getData() const;

    __attribute__((unused)) void setData(T *d);

    bool operator<(const Node<T>& other);
    bool operator>(const Node<T>& other);
    bool operator==(const Node<T>& other);


    //friend std::ostream &operator<<(std::ostream &os, const Node<T> &node);
};

template<class T>
Node<T>* Node<T>::getPrev() const{
    return prev;
}

template<class T>
void Node<T>::setPrev(Node<T> *prevv) {
    prev = prevv;
}

template<class T>
Node<T>* Node<T>::getNext() const{
    return next;
}

template<class T>
void Node<T>::setNext(Node<T> *nextt) {
    next = nextt;
}

template<class T>
T* Node<T>::getData() const {
    return data;
}

template<class T>
__attribute__((unused)) void Node<T>::setData(T *d) {
    data = d;
}

template<class T>
Node<T>::Node(T* d) : next(nullptr), prev(nullptr), data(d){}

template<class T>
Node<T>::Node(T* d, Node<T> *next, Node<T> *prev) : next(next), prev(prev), data(d) {}

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
    delete data;
}

template<class T>
Node<T> &Node<T>::operator=(const Node<T> &other) noexcept {
    if (*this == other) return *this;
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
std::ostream &operator<<(std::ostream &os, Node<T> const &node) {
    os << *(node.getData()) << '\n';
    return os;
}


#endif //INC_14_NODE_H
