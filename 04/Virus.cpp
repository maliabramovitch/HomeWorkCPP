//
// Created by Mali Abramovitch on 07/01/2023.
//

#include <iostream>
#include "Virus.h"


Virus::Virus(std::string name, int *per, int size, int pmm, int *familySize, char family) {
    this->name = std::move(name);
    this->permutation = new int[size];
    this->permutation = per;
    this->id = 0;
    this->familySize = familySize;
    this->errorIndex = 0;
    this->pm = pmm;
    this->size = size;
    this->family = family;
}

Virus::Virus(const Virus &other) {
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
    this->family = other.family;
}

Virus::Virus(Virus &&other) noexcept {
    this->name = other.name;
    this->size = other.size;
    this->permutation = other.permutation;
    this->errorIndex = other.errorIndex;
    pm = other.pm;
    this->familySize = other.familySize;
    this->family = other.family;
    other.permutation = nullptr;
    other.name = "";
    other.errorIndex = 0;
    this->id = other.id;
    other.family = 0;
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
    this->family = other.family;

    return *this;
}

Virus &Virus::operator=(Virus &&other) noexcept {
    if (*this == other) return *this;
    this->name = other.name;
    this->size = other.size;
    this->permutation = other.permutation;
    this->errorIndex = other.errorIndex;
    pm = other.pm;
    this->familySize = other.familySize;
    this->id = other.id;
    this->family = other.family;
    other.permutation = nullptr;
    other.name = "";
    other.errorIndex = 1;
    other.familySize = nullptr;
    other.id = 0;
    other.family = 0;
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
        //std::cout<< n << " 1. " << *this << '\t' << i << '\t' << j << std::endl;
        tmp = this->permutation[i];
        this->permutation[i] = this->permutation[j];
        this->permutation[j] = tmp;
        //std::cout << n<< " 2. "<< *this << '\t' << i << '\t' << j << std::endl;
    }
}

void Virus::operator++() {
    ++(*familySize);
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


bool Virus::operator<(Virus &other) {
    if (this->getIndexError() > other.getIndexError())
        return false;
    else if (getIndexError() < other.getIndexError()) {
        return true;
    } else {
        if (this->name == other.name) {
            if (this->id < other.id) return true;
            else return false;
        } else return true;
    }
}

bool Virus::operator>(Virus &other) {
    return !(*this < other) && !(*this == other);
}

bool Virus::operator==(Virus &other) {
    if (family != other.family) return false;
    if (name != other.name) return false;
    if (id != other.id) return false;
    for (int i = 0; i < size; ++i) {
        if (permutation[i] != other.permutation[i]) return false;
    }
    return true;
}

bool Virus::operator!=(Virus &other) {
    return !operator==(other);
}

std::ostream &operator<<(std::ostream &os, Virus &v) {
    os << v.getFamily() << ' ' << v.getName();
    if (v.getId() != 0) {
        os << '_';
        os << v.getId();
    }
    os << ' ';
    for (int i = 0; i < v.getSize(); ++i) {
        os << v[i] << ' ';
    }
    return os;
}
