//
// Created by Mali Abramovitch on 07/01/2023.
//

#ifndef INC_14_SORTEDDOUBLELINKEDLIST_H
#define INC_14_SORTEDDOUBLELINKEDLIST_H

#include "Node.h"
#include <ostream>

template<class T>
class SortedDoubleLinkedList {
private:
    Node<T> *head; // dummy
    Node<T> *tail; // dummy
    int size = 0;
public:
    SortedDoubleLinkedList();

    SortedDoubleLinkedList(const SortedDoubleLinkedList<T> &other) noexcept;

    __attribute__((unused)) SortedDoubleLinkedList(SortedDoubleLinkedList<T> &&other) noexcept;

    ~SortedDoubleLinkedList();

    SortedDoubleLinkedList &operator=(const SortedDoubleLinkedList<T> &other) noexcept;

    SortedDoubleLinkedList &operator=(SortedDoubleLinkedList<T> &&other) noexcept;

    inline Node<T> *getFirstElement() const{
        if (size == 0) return nullptr;
        return head->getNext();
    }

    inline Node<T> *getLastElement() const{
        if (size == 0) return nullptr;
        return tail->getPrev();
    }

    __attribute__((unused)) inline Node<T> *getHead() const{ return head; } // head is dummy
    inline Node<T> *getTail() const{ return tail; } // tail is dummy

    inline int getSize() const{ return size; }

    bool contains(T *t) const;

    Node<T> *getElement(T *t) const;

    bool addFirst(T *t);

    bool addLast(T *t);

    bool add(T *t);

    void clear();

    Node<T> *remove(T *t);

    __attribute__((unused)) Node<T> *removeFirst();

    Node<T> *removeLast();

    __attribute__((unused)) bool isEmpty();

    void sort();
};

template<class T>
SortedDoubleLinkedList<T>::SortedDoubleLinkedList() {
    head = new Node<T>(nullptr);
    tail = new Node<T>(nullptr);
    head->setNext((tail));
    tail->setPrev((head));
    size = 0;
}

template<class T>
SortedDoubleLinkedList<T>::SortedDoubleLinkedList(const SortedDoubleLinkedList<T> &other) noexcept {
    Node<T>* tmpOther = other.getFirstElement();
    head = new Node<T>(nullptr);
    tail = new Node<T>(nullptr);
    head->setNext(tail);
    tail->setPrev(head);
    while (tmpOther != other.getTail()) {
        T* t =new T(*tmpOther->getData());
        addLast(t);
        tmpOther =tmpOther->getNext();
    }
}

template<class T>
__attribute__((unused)) SortedDoubleLinkedList<T>::SortedDoubleLinkedList(SortedDoubleLinkedList<T> &&other) noexcept {
    head = new Node<T>;
    tail = new Node<T>;
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
        clear();
        Node<T>* tmpOther = other.getFirstElement();
        while (tmpOther != other.getTail()) {
            T* t =new T(*tmpOther->getData());
            addLast(t);
            tmpOther =tmpOther->getNext();
        }
        return *this;
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
Node<T> *SortedDoubleLinkedList<T>::getElement(T *t) const {
    if (size == 0) return nullptr;
    Node<T> *tmpThis = getFirstElement();
    while (tmpThis != tail) {
        if ((*t) == (*tmpThis->getData())) {
            return tmpThis;
        }
        tmpThis = tmpThis->getNext();
    }
    return nullptr;
}

template<class T>
bool SortedDoubleLinkedList<T>::contains(T *t) const {
    if (getElement(t) == nullptr) return false;
    return true;
}


template<class T>
bool SortedDoubleLinkedList<T>::addFirst(T *t) {
    if (size > 0 && head->getNext()->getData() == t) return false;
    Node<T> *tmp;
    tmp = new Node<T>(t, head->getNext(), head);
    head->getNext()->setPrev(tmp);
    head->setNext(tmp);
    ++size;
    return true;
}

template<class T>
bool SortedDoubleLinkedList<T>::addLast(T *t) {
    if (size > 0 && tail->getPrev()->getData() == t) return false;
    Node<T> *tmp;
    tmp = new Node<T>(t, tail, tail->getPrev());
    tail->getPrev()->setNext(tmp);
    tail->setPrev(tmp);
    ++size;
    return true;
}

template<class T>
bool SortedDoubleLinkedList<T>::add(T *t) {
    if (contains(t)) return false;
    Node<T> *tmpNew;
    Node<T> *tmpThis;
    if (size == 0 || (*t) < (*(getFirstElement()->getData()))) {
        addFirst(t);
    } else if ((*t) > (*(getLastElement()->getData()))) {
        addLast(t);
    } else {
        tmpThis = getFirstElement();
        while (tmpThis != tail) {
            if ((*t) > *(tmpThis->getData())) {
                if (tmpThis->getNext() == nullptr) {
                    addLast(t);
                }
                else if (*t < *(tmpThis->getNext()->getData()) && *t != *(tmpThis->getNext()->getData())) {
                    tmpNew = new Node<T>(t);
                    tmpNew->setPrev(tmpThis);
                    tmpNew->setNext(tmpThis->getNext());
                    (tmpThis->getNext())->setPrev(tmpNew);
                    tmpThis->setNext(tmpNew);
                    ++size;
                    break;
                }
            }
            tmpThis = tmpThis->getNext();
        }
    }

    return true;
}

template<class T>
void SortedDoubleLinkedList<T>::clear() {
    if (size == 0) return;
    Node<T> *tmp1 = getFirstElement(), *tmp2;
    while (tmp1 != tail) {
        tmp2 = tmp1->getNext();
        delete tmp1;
        tmp1 = tmp2;
    }
    head->setNext(tail);
    tail->setPrev(head);
    size = 0;
}

template<class T>
Node<T> *SortedDoubleLinkedList<T>::remove(T *t) {
    if (size == 0) return nullptr;
    Node<T>* r = getElement(t);
    if (r == nullptr) return nullptr;
    r->getPrev()->setNext(r->getNext());
    r->getNext()->setPrev(r->getPrev());
    --size;
    return r;
}

template<class T>
__attribute__((unused)) Node<T> *SortedDoubleLinkedList<T>::removeFirst() {
    if (size == 0) return nullptr;
    Node<T>* tmp = getFirstElement();
    head->setNext(tmp->getNext());
    tmp->getNext()->setPrev(head);
    --size;
    return tmp;
}

template<class T>
Node<T> *SortedDoubleLinkedList<T>::removeLast() {
    if (size == 0) return nullptr;
    Node<T>* tmp = getLastElement();
    tail->setPrev(tmp->getPrev());
    tmp->getPrev()->setNext(tail);
    --size;
    return tmp;
}

template<class T>
__attribute__((unused)) bool SortedDoubleLinkedList<T>::isEmpty() {
    return size == 0;
}


template<class T>
void SortedDoubleLinkedList<T>::sort() {
    Node<T> *tmp1 = getFirstElement(), *tmp2;
    while (tmp1->getNext() != tail) {
        if (*(tmp1->getData()) > *(tmp1->getNext()->getData())) {
            tmp2 = remove((tmp1->getNext()->getData()));
            add(tmp2->getData());
        }
        else {
            tmp1 = tmp1->getNext();
        }

    }
}


template<class T>
std::ostream& operator<<(std::ostream& os, SortedDoubleLinkedList<T> sdll){
    if (sdll.getSize() == 0) {
        os << "Empty\n";
        return os;
    }
    Node<T> *tmp = sdll.getFirstElement();
    while (tmp != sdll.getTail()) {
        os << *tmp;
        tmp = tmp->getNext();
    }
    return os;
}


#endif //INC_14_SORTEDDOUBLELINKEDLIST_H
