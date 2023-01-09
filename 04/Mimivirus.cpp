//
// Created by Mali Abramovitch on 07/01/2023.
//

#include "Mimivirus.h"

#include <utility>

Mimivirus::Mimivirus(std::string name1, int *per1, int size1, int *familySize1) : Virus(std::move(name1), per1, size1, 4, familySize1, 'M') {

}
