//
// Created by Mali Abramovitch on 20/12/2022.
//

#include "Virus.h"
#include <iostream>

using namespace std;


Virus::Virus(int size, int pmm) : size(size), pm(pmm) {
    this->name = "";
    this->permutation = new int[size];
    familySize = nullptr;
    this->id = 0;
    errorIndex = 1;
    familySize = nullptr;
}


Virus::Virus(std::string name, int *per, int size, int pmm, int* familySize) : size(size) {
    this->name = std::move(name);
    this->permutation = new int[size];
    this->permutation = per;
    this->id = 0;
    this->familySize = familySize;
    this->errorIndex = 0;
    this->pm = pmm;
}

Virus::Virus(Virus &other) {
    this->name = other.name;
    this->size = other.size;
    this->permutation = new int[other.size];
    for (int i = 0; i < size; ++i) {
        this->permutation[i] = other.permutation[i];
    }
    this->errorIndex = other.errorIndex;
    this->familySize = other.familySize;
    pm = other.pm;
    this->id = other.id;
}

Virus::Virus(Virus &&other) noexcept {
    this->name = other.name;
    this->size = other.size;
    this->permutation = other.permutation;
    this->errorIndex = other.errorIndex;
    pm = other.pm;
    this->familySize = other.familySize;
    other.permutation = nullptr;
    other.name = "";
    other.errorIndex = 0;
    this->id = other.id;
}

Virus::~Virus() {
    delete[] this->permutation;
}

Virus &Virus::operator=(Virus const &other) {
    if (this == &other) {
        return *this;
    }
    for (int i = 0; i < size; ++i) {
        permutation[i] = other.permutation[i];
    }
    this->familySize = other.familySize;
    this->id = (*other.familySize) + 1; // if the copy= has been called, another member has added to the family
    ++(*familySize);
    this->name = other.name;
    this->errorIndex = other.errorIndex;
    return *this;
}

Virus &Virus::operator=(Virus &&other) noexcept {
    this->name = other.name;
    this->size = other.size;
    this->permutation = other.permutation;
    this->errorIndex = other.errorIndex;
    pm = other.pm;
    this->familySize = other.familySize;
    this->id = other.id;
    other.permutation = nullptr;
    other.name = "";
    other.errorIndex = 1;
    other.familySize = nullptr;
    other.id = 0;
    return *this;
}

int Virus::getSize() const {
    return size;
}

int Virus::operator[](int i) {
    return permutation[i];
}

void Virus::operator*() {
    for (int n = 0; n < pm; ++n) {
        int i, j, tmp;
        i = rand() % size;
        j = rand() % size;
        tmp = this->permutation[i];
        this->permutation[i] = this->permutation[j];
        this->permutation[j] = tmp;
    }
}

void Virus::operator++() {
    ++(*familySize);
}

std::ostream &operator<<(std::ostream &os, Virus &v) {
    os << v.getName();
    if (v.id != 0) {
        os << '_';
        os << v.getId();
    }
    os << '\t';
    for (int i = 0; i < v.size; ++i) {
        os << v[i] << ' ';
    }
    return os;
}

void Virus::calculateErrorIndex(Virus *target) {
    double similar = 0;
    for (int i = 0; i < size; ++i) {
        if ((*target)[i] == permutation[i]) {
            ++similar;
        }
    }
    errorIndex = double(1 - (double) (similar / size));
}
