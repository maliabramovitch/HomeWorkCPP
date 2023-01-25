//
// Created by Mali Abramovitch on 07/01/2023.
//

#ifndef INC_14_LENTIVIRUS_H
#define INC_14_LENTIVIRUS_H


#include "Virus.h"

class Lentivirus : public Virus{
public:
    Lentivirus(std::string name, int *per, int size, int* familySize);
};


#endif //INC_14_LENTIVIRUS_H
