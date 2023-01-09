//
// Created by Mali Abramovitch on 07/01/2023.
//

#ifndef INC_14_QUEUE_H
#define INC_14_QUEUE_H


#include "SortedDoubleLinkedList.h"

template<class T>
class Queue {
private:
    SortedDoubleLinkedList<T> *queue;
public:
    Queue();

    Queue(const Queue<T> &other);

    __attribute__((unused)) Queue(Queue<T> &&other) noexcept;

    ~Queue();

    Queue<T> &operator=(const Queue<T> &other);

    Queue<T> &operator=(Queue<T> &&other) noexcept;

    bool inQueue(T *t) { return queue->add(t); }

    bool inQueueLast(T *t) { return queue->addFirst(t); }

    T *deQueue() { return queue->removeLast()->getData(); }

    T *peek() { return queue->getLastElement()->getData(); }

    __attribute__((unused)) int size() { return queue->getSize(); }

    SortedDoubleLinkedList<T> *getQueue() { return queue; }

    void sort() { queue->sort(); }

    __attribute__((unused)) void clear() {queue->clear();}


};

template<class T>
Queue<T> &Queue<T>::operator=(Queue<T> &&other) noexcept {
    if (this != &other) {
        queue = other.queue;
        other.queue = nullptr;
    }
    return *this;
}

template<class T>
__attribute__((unused)) Queue<T>::Queue(Queue<T> &&other) noexcept {
    this->queue = other.queue;
    other.queue = nullptr;
}

template<class T>
Queue<T>::Queue() {
    queue = new SortedDoubleLinkedList<T>;
}

template<class T>
Queue<T>::Queue(const Queue<T> &other) {
    queue = new SortedDoubleLinkedList<T>(*other.queue);

}

template<class T>
Queue<T>::~Queue() {
    delete queue;
}

template<class T>
Queue<T> &Queue<T>::operator=(const Queue<T> &other) {
    if (*this != other) {
        queue = other.queue;
    }
    return *this;
}

template<class T>
std::ostream &operator<<(std::ostream &os, Queue<T> &s) {
    os << *(s.getQueue());
    return os;
}


#endif //INC_14_QUEUE_H
