//
// Created by Mali Abramovitch on 07/01/2023.
//

#include "Papillomavirus.h"

#include <utility>

Papillomavirus::Papillomavirus(std::string name, int *per, int size, int* familySize) : Virus(std::move(name), per, size,1,  familySize, 'P') {}
