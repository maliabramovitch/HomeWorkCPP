//
// Created by Mali Abramovitch on 20/12/2022.
//

#ifndef INC_03_VIRUS_H
#define INC_03_VIRUS_H


#include <string>
#include <utility>

class Virus {

public:
    Virus(int size, int pm);

    Virus(std::string name, int *per, int size, int pm, int* familySize);

    Virus(Virus &other);

    Virus(Virus &&other) noexcept;

    ~Virus();

    Virus &operator=(Virus const &other);

    Virus &operator=(Virus &&other) noexcept;

    std::string getName() const { return name; };

    __attribute__((unused)) void setName(std::string name1) {this->name = name1;}

    int getSize() const;

    int operator[](int i);

    void operator*(); // updates the Virus
    void operator++();

    friend std::ostream &operator<<(std::ostream &os, Virus &v);

    void calculateErrorIndex(Virus *target);

    double getIndexError() const {return errorIndex;}

    __attribute__((unused)) void setIndexError(double ei) {errorIndex = ei;}

    int getId() const {return id;}

    __attribute__((unused)) void setId(int ID) {id = ID;}

private:
    std::string name;
    int size;
    int *permutation;
    int *familySize;
    int id;
    double errorIndex;
    int pm;

};


#endif //INC_03_VIRUS_H
