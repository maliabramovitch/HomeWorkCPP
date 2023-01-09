//
// Created by Mali Abramovitch on 07/01/2023.
//

#ifndef INC_14_POPULATIONQUEUE_H
#define INC_14_POPULATIONQUEUE_H


#include "Queue.h"
#include "Virus.h"
#include <ostream>

class PopulationQueue {
private:
    Queue<Virus>* queue;
    Virus *target;
    Virus *theBestVirusEver = nullptr;
    Virus *theBestVirusNow = nullptr;
    int virusSize;
    int queueSize;
    bool itsAMatch = false; //true if one of the viruses matching to the target.
    bool allPapi = false; //if all viruses are Papilloma

public:
    PopulationQueue(Virus *target, int virusSize, int populationSize);

    PopulationQueue(const PopulationQueue &pq);

    ~PopulationQueue();

    PopulationQueue &operator=(const PopulationQueue &pq);

    bool addVirusToQueue(Virus *v);

    void operator++();

    bool getItsAMatch() const { return itsAMatch; };

    Virus *getTheBestVirusEver() { return theBestVirusEver; };

    friend std::ostream &operator<<(std::ostream &os, PopulationQueue &p);

    int getQueueSize() const {return queueSize;}

    Virus* deQueueVirus() {return queue->deQueue();}

    void best(Virus *tmp);
};


#endif //INC_14_POPULATIONQUEUE_H
