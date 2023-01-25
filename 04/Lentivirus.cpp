//
// Created by Mali Abramovitch on 07/01/2023.
//

#include "Lentivirus.h"

#include <utility>

Lentivirus::Lentivirus(std::string name, int *per, int sizee, int* familySize) : Virus(std::move(name), per, sizee, 2, familySize, 'L'){}