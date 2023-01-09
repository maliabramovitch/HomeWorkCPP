//
// Created by Mali Abramovitch on 07/01/2023.
//

#ifndef INC_14_PAPILLOMAVIRUS_H
#define INC_14_PAPILLOMAVIRUS_H


#include "Virus.h"

class Papillomavirus : public Virus{
public:
    Papillomavirus(std::string name, int *per, int size, int* familySize);

};


#endif //INC_14_PAPILLOMAVIRUS_H
