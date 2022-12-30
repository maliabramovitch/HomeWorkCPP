//
// Created by Mali Abramovitch on 20/12/2022.
//

#ifndef INC_03_WORLD_H
#define INC_03_WORLD_H


#include "Population.h"

class World {
private:
    int* familyIndexes;
    Population *population;
    int generation;
    Virus *target;
public:
    World(char *config, char *first_generation, int gen);

    __attribute__((unused)) World(World &other);

    ~World();

    World &operator=(World const &other);

    /*
     * no need for the big 5 because there is only one world while the program is running
     */
    void RunTheWorld();
};


#endif //INC_03_WORLD_H
