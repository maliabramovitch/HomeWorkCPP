//
// Created by Mali Abramovitch on 08/01/2023.
//

#ifndef INC_14_WORLD_H
#define INC_14_WORLD_H


#include "PopulationQueue.h"

class World {
private:
    int *familyIndexes;
    PopulationQueue *population;
    int generation;
    Virus *target;

    static void invalidInput();

public:
    World(char *config, char *first_generation, int gen);

    __attribute__((unused)) __attribute__((unused)) World(World &other);

    ~World();

    World &operator=(World const &other);

    void RunTheWorld();

    void printpop();
};


#endif //INC_14_WORLD_H
