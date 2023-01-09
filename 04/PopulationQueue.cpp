//
// Created by Mali Abramovitch on 07/01/2023.
//

#include "PopulationQueue.h"
#include <iostream>

PopulationQueue::PopulationQueue(Virus *target, int virusSize, int populationSize) {
    this->target = target;
    this->virusSize = virusSize;
    this->queueSize = populationSize;
    this->queue = new Queue<Virus>;
    theBestVirusEver = nullptr;
}

PopulationQueue::PopulationQueue(const PopulationQueue &pq) {
    this->target = pq.target;
    this->queue = new Queue<Virus>(*(pq.queue));
    this->virusSize = pq.virusSize;
    this->queueSize = pq.queueSize;
    this->theBestVirusEver = new Virus(*pq.theBestVirusEver);
    this->itsAMatch = pq.itsAMatch;
}

PopulationQueue::~PopulationQueue() {
    delete queue;
    delete theBestVirusEver;
}

PopulationQueue &PopulationQueue::operator=(const PopulationQueue &pq) {
    if (this != &pq) {
        if (this == &pq) return *this;
        this->target = pq.target;
        this->queue = pq.queue;
        this->virusSize = pq.virusSize;
        this->queueSize = pq.queueSize;
        delete theBestVirusEver;
        this->theBestVirusEver = new Virus(*pq.theBestVirusEver);
        this->itsAMatch = pq.itsAMatch;
    }
    return *this;
}

/*void PopulationQueue::operator++() {
    Virus *tmp;
    Queue<Virus> *tmpQueue;
    tmpQueue = new Queue<Virus>(*this->queue);
    if (queue->peek()->getFamily() != 'P') {
        tmp = queue->deQueue();
        for (int i = 0; i < queueSize - 1; ++i) {
            Virus *tmpD = queue->deQueue();
            tmpQueue->inQueueLast(tmpD);
        }
        *tmp = *(tmpQueue->peek());
        tmpQueue->inQueueLast(tmp);
    } else {
        for (int i = 0; i < queueSize; ++i) {
            Virus *tmpD = queue->deQueue();
            tmpQueue->inQueueLast(tmpD);
        }
    }
    for (int i = 0; i < queueSize; ++i) {
        tmp = tmpQueue->deQueue();
        *(*tmp);
        tmp->calculateErrorIndex(target);
        if (theBestVirusEver == nullptr || tmp->getIndexError() < theBestVirusEver->getIndexError()) {
            delete theBestVirusEver;
            theBestVirusEver = new Virus(*tmp);
        }
        if (tmp->getIndexError() == 0) itsAMatch = true;
        queue->inQueue(tmp);
    }
    delete tmpQueue;
}*/

void PopulationQueue::best(Virus* tmp) {
    if (theBestVirusNow == nullptr || tmp->getIndexError() < theBestVirusNow->getIndexError()) {
        theBestVirusNow = tmp;
    }
}

void PopulationQueue::operator++() {
    Virus *tmp;
    Virus* bad;
    Queue<Virus> *tmpQueue;
    tmpQueue = new Queue<Virus>();
    if (!allPapi) {
        int count = 0;
        while (!allPapi && queue->peek()->getFamily() == 'P') {
            tmp = deQueueVirus();
            queue->inQueueLast(tmp);
            ++count;
            if (count == queueSize) allPapi = true;

        }
        bad = deQueueVirus();
        queue->sort();
        for (int i = 0; i < queueSize - 1; ++i) {
            Virus *tmpD = queue->deQueue();
            best(tmpD);
            tmpQueue->inQueueLast(tmpD);
        }
        *bad = *theBestVirusNow;
        tmpQueue->inQueueLast(bad);
    } else {
        for (int i = 0; i < queueSize; ++i) {
            Virus *tmpD = queue->deQueue();
            best(tmpD);
            tmpQueue->inQueueLast(tmpD);
        }
    }
    for (int i = 0; i < queueSize; ++i) {
        tmp = tmpQueue->deQueue();
        *(*tmp);
        tmp->calculateErrorIndex(target);
        if (theBestVirusEver == nullptr || tmp->getIndexError() < theBestVirusEver->getIndexError()) {
            delete theBestVirusEver;
            theBestVirusEver = new Virus(*tmp);
        }
        if (tmp->getIndexError() == 0) itsAMatch = true;
        queue->inQueue(tmp);
    }
    delete tmpQueue;
}

std::ostream &operator<<(std::ostream &os, PopulationQueue &p) {
    os << *(p.queue);
    return os;
}

bool PopulationQueue::addVirusToQueue(Virus *v) {
    v->calculateErrorIndex(target);
    return queue->inQueue(v);
}
