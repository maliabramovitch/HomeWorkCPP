//
// Created by Mali Abramovitch on 04/01/2023.
//

#ifndef INC_04_SORTEDDOUBLELINKEDLIST_H
#define INC_04_SORTEDDOUBLELINKEDLIST_H

#include "Node.h";

template<class T>
class SortedDoubleLinkedList {
private:
    Node<T> head; // dummy
    Node<T> tail; // dummy
    int size = 0;
public:
    SortedDoubleLinkedList();

    SortedDoubleLinkedList(const SortedDoubleLinkedList<T> &other) noexcept;

    SortedDoubleLinkedList(SortedDoubleLinkedList<T> &&other) noexcept;

    ~SortedDoubleLinkedList();

    SortedDoubleLinkedList &operator=(const SortedDoubleLinkedList<T> &other) noexcept;

    SortedDoubleLinkedList &operator=(SortedDoubleLinkedList<T> &&other) noexcept;

    inline Node<T> *getFirstElement() {
        if (size == 0) return nullptr;
        return head.getNext();
    }

    inline Node<T> *getLastElement() {
        if (size == 0) return nullptr;
        return tail.getPrev();
    }

    inline Node<T> *getHead() { return head; } // head is dummy
    inline Node<T> *getTail() { return tail; } // tail is dummy

    inline int getSize() { return size; }

    Node<T> *getElement(T *t);

    bool addFirst(T *t);

    bool addLast(T *t);

    bool add(T *t);

    void clear();

    bool remove(T *t);

    bool removeFirst();

    bool removeLast();

    bool isEmpty();

    friend std::ostream &operator<<(std::ostream &os, SortedDoubleLinkedList<T>& const sdll);
};

template<class T>
SortedDoubleLinkedList<T>::SortedDoubleLinkedList() {
    head = new Node<T>(nullptr);
    tail = new Node<T>(nullptr);
    head.setNext(tail);
    tail.setPrev(head);
    size = 0;
}

template<class T>
SortedDoubleLinkedList<T>::SortedDoubleLinkedList(const SortedDoubleLinkedList<T> &other) noexcept {
    Node<T> tmpOther = other.head;
    Node<T> tmpThis = head;
    while (tmpOther != other.tail) {
        tmpThis = new Node<T>(nullptr);
        tmpThis.setNext(tmpOther.getNext());
        tmpThis.setPrev(tmpOther.getPrev());
        tmpThis.setData(tmpOther.getData());
        tmpOther = tmpOther.getNext();
        tmpThis = tmpThis.getNext();
    }
    tail = new Node<T>(nullptr, nullptr, nullptr);
    tail.setPrev(other.tail.getPrev());
    size = other.size;
}

template<class T>
SortedDoubleLinkedList<T>::SortedDoubleLinkedList(SortedDoubleLinkedList<T> &&other) noexcept {
    head = other.head;
    tail = other.tail;
    size = other.size;
    other.head = nullptr;
    other.tail = nullptr;
    other.size = 0;
}

template<class T>
SortedDoubleLinkedList<T>::~SortedDoubleLinkedList() {
    clear();
    delete head;
    delete tail;

}

template<class T>
SortedDoubleLinkedList<T> &SortedDoubleLinkedList<T>::operator=(const SortedDoubleLinkedList<T> &other) noexcept {
    if (*this != other) {
        this->head = other.head;
        this->tail = other.tail;
        this->size = other.size;
    }
    return *this;
}

template<class T>
SortedDoubleLinkedList<T> &SortedDoubleLinkedList<T>::operator=(SortedDoubleLinkedList<T> &&other) noexcept {
    if (*this != other) {
        this->head = other.head;
        this->tail = other.tail;
        this->size = other.size;
        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }
    return *this;
}


template<class T>
Node<T> *SortedDoubleLinkedList<T>::getElement(T *t) {
    Node<T> *tmpThis = getFirstElement();
    while (tmpThis != tail) {
        if ((*t) == *(tmpThis->getData())) return tmpThis;
    }
    return nullptr;
}


template<class T>
bool SortedDoubleLinkedList<T>::addFirst(T *t) {
    if (head.getNext()->getData() == t) return false;
    Node<T> *tmp;
    tmp = new Node<T>(t, head.getNext(), head);
    head.getNext()->setPrev(tmp);
    head.setNext(tmp);
    ++size;
    return true;
}

template<class T>
bool SortedDoubleLinkedList<T>::addLast(T *t) {
    if (tail.getPrev()->getData() == t) return false;
    Node<T> *tmp;
    tmp = new Node<T>(t, tail, tail.getPrev());
    tail.getPrev()->setNext(tmp);
    tail.setPrev(tmp);
    ++size;
    return true;
}

template<class T>
bool SortedDoubleLinkedList<T>::add(T *t) {
    Node<T> *tmpNew;
    Node<T> *tmpThis;
    if ((*t) < (*(getFirstElement()->getData()))) {
        addFirst(t);
    } else if ((*t) > (*(getLastElement()->getData()))) {
        addLast(t);
    } else {
        tmpThis = getLastElement();
        while (tmpThis != tail) {
            if ((*t) == *(tmpThis->getData())) return false;
            if ((*t) > *(tmpThis->getData()) && (*t) < *(tmpThis->getNext()->getData())) {
                tmpNew = new Node<T>(t);
                tmpNew->setPrev(tmpThis);
                tmpNew->getNext(tmpThis->getNext());
                tmpThis->getNext()->setPrev(tmpNew);
                tmpThis->setNext(tmpNew);
                ++size;
                break;
            }
            tmpThis = tmpThis->getNext();
        }
    }
    return true;
}

template<class T>
void SortedDoubleLinkedList<T>::clear() {
    Node<T> *tmp1, tmp2 = getFirstElement();
    while (tmp1 != tail) {
        tmp2 = tmp1->getNext();
        delete tmp1;
        tmp1 = tmp2;
    }
    head.setNext(tail);
    tail.setPrev(head);
    ++size;
}

template<class T>
bool SortedDoubleLinkedList<T>::remove(T *t) {
    if (size == 0) return false;
    Node<T>* r = getElement(t);
    if (r == nullptr) return false;
    r->getPrev()->setNext(r->getNext());
    r->getNext()->setPrev(r->getPrev());
    delete r;
    return true;
}

template<class T>
bool SortedDoubleLinkedList<T>::removeFirst() {
    if (size == 0) return false;
    Node<T>* tmp = getFirstElement();
    head.setNext(tmp->getNext());
    tmp->getNext()->setPrev(head);
    delete tmp;
    return true;
}

template<class T>
bool SortedDoubleLinkedList<T>::removeLast() {
    if (size == 0) return false;
    Node<T>* tmp = getLastElement();
    tail.setPrev(tmp->getPrev());
    tmp->getPrev()->setNext(tail);
    delete tmp;
    return true;
}

template<class T>
bool SortedDoubleLinkedList<T>::isEmpty() {
    return size == 0;
}

template<class T>
std::ostream &operator<<(std::ostream &os, SortedDoubleLinkedList<T> const &sdll) {
    if (sdll.size == 0) {
        os << "Empty\n";
        return os;
    }
    Node<T*> tmp = sdll.getLastElement();
    while (tmp != sdll.getTail()) {
        os << *tmp;
        tmp = tmp.getNext();
    }
    return os;
}


#endif //INC_04_SORTEDDOUBLELINKEDLIST_H
