//
// Created by Mali Abramovitch on 20/12/2022.
//

#ifndef INC_03_POPULATION_H
#define INC_03_POPULATION_H


#include "Virus.h"

class Population {
public:
    Population(int populationSize, Virus &target, int virusSize, int pm);

    Population(Population &other);

    ~Population();

    Population &operator=(Population const &other);

    /*
     * no need for the big 5 because there is only one population while the program is running
     */
    void setVirus(int i, Virus &v);

    Virus &operator[](int i);

    void operator++();

    bool getItsAMatch() const {return itsAMatch;};

    Virus *getTheBestVirusEver() {return theBestVirusEver;};

    friend std::ostream &operator<<(std::ostream &os, Population &p);

    int getPm() const {return pm;};

    void insertionSort();

private:
    Virus *target;
    Virus **population;
    int populationSize;
    Virus *theBestVirusEver = nullptr;
    int virusSize;
    bool itsAMatch = false; //true if one of the viruses matching to the target.
    int pm;
};


#endif //INC_03_POPULATION_H
