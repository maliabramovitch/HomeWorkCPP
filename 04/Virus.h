//
// Created by Mali Abramovitch on 07/01/2023.
//

#ifndef INC_14_VIRUS_H
#define INC_14_VIRUS_H

#include <string>
#include <utility>
#include <ostream>

class Virus {
protected:
    std::string name;
    char family;
    int size;
    int *permutation;
    int *familySize;
    int id;
    double errorIndex;
    int pm;

public:

    Virus(std::string name, int *per, int size, int pm, int* familySize, char family) ;

    Virus(const Virus &other);

    Virus(Virus &&other) noexcept;

    ~Virus();

    Virus &operator=(Virus const &other);

    Virus &operator=(Virus &&other) noexcept;

    std::string getName() const { return name; };

    __attribute__((unused)) void setName(std::string name1) {this->name = std::move(name1);}

    char getFamily() const {return family;}

    __attribute__((unused)) void setFamily(char f) {family = f;}

    int getSize() const;

    int operator[](int i);

    void operator*(); // updates the Virus
    void operator++();

    friend std::ostream& operator<<(std::ostream& os, Virus& v);

    void calculateErrorIndex(Virus *target);

    double getIndexError() const {return errorIndex;}

    __attribute__((unused)) void setIndexError(double ei) {errorIndex = ei;}

    int getId() const {return id;}

    __attribute__((unused)) void setId(int ID) {id = ID;}

    bool operator<(Virus &other);
    bool operator>(Virus &other);
    bool operator==(Virus &other);
    bool operator!=(Virus &other);

};

#endif //INC_14_VIRUS_H
