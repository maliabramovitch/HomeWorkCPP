//
// Created by Mali Abramovitch on 20/12/2022.
//

#include <iostream>
#include "Population.h"

Population::Population(int populationSize, Virus &target, int virusSize, int pm) {
    this->target = new Virus(target);
    this->populationSize = populationSize;
    population = new Virus *[populationSize];
    this->virusSize = virusSize;
    this->pm = pm;
    this->theBestVirusEver = new Virus(virusSize, pm);
}


Population::Population(Population &other) {
    this->target = new Virus(*other.target);
    this->population = new Virus *[other.populationSize];
    this->populationSize = other.populationSize;
    this->virusSize = other.virusSize;
    this->pm = other.pm;
    for (int i = 0; i < other.populationSize; ++i) {
        this->population[i] = &other[i];
    }
    this->theBestVirusEver = other.theBestVirusEver;
    this->itsAMatch = other.itsAMatch;
}

Population::~Population() {
    if (!target) delete target;
    for (int i = 0; i < populationSize; ++i) {
        if (!population[i]) delete population[i];
    }
    if (!population) delete[] population;
    if (!theBestVirusEver) delete theBestVirusEver;
}

Population &Population::operator=(Population const &other) {
    if (this == &other) {
        return *this;
    }
    if (this->populationSize != other.populationSize) {
        this->populationSize = other.populationSize;
        this->population = new Virus *[populationSize];
    }
    for (int i = 0; i < populationSize; ++i) {
        this->population[i] = other.population[i];
    }

    this->virusSize = other.virusSize;
    this->pm = other.pm;
    this->target = other.target;

    return *this;
}

Virus &Population::operator[](int i) {
    return (*population)[i];
}

void Population::operator++( ) {
    *(population[populationSize - 1]) = *(population[0]);
    for (int i = 0; i < populationSize; ++i) {
        *(*population[i]);
        population[i]->calculateErrorIndex(target);
        if ((population[i]->getIndexError()) == 0) {
            itsAMatch = true;
        }
    }
    insertionSort();
    if (population[0]->getIndexError() < theBestVirusEver->getIndexError()) {
        delete theBestVirusEver;
        theBestVirusEver = new Virus(*population[0]);
    }
}

std::ostream &operator<<(std::ostream &os, Population &p) {
    for (int i = 0; i < p.populationSize; ++i) {
        Virus v = *(p.population[i]);
        os << v << '\n';
    }
    return os;
}

void Population::insertionSort() {
    int i, j;
    Virus *v;
    for (i = 1; i < populationSize; i++) {
        j = i - 1;

        while (j >= 0 && population[j + 1]->getIndexError() < population[j]->getIndexError()) {
            v = population[j + 1];
            population[j + 1] = population[j];
            population[j] = v;
            --j;
        }

    }

}


void Population::setVirus(int i, Virus &v) {
    population[i] = &v;
}
