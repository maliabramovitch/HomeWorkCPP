//
// Created by Mali Abramovitch on 16/11/2022.
//

#ifndef INC_01_VECTOR_H
#define INC_01_VECTOR_H

#include <string>

class Vector {

public:
    /**
     * C'tor
     * @param size
     * @param lable
     */
    Vector(int size, const std::string& lable);

    /**
     * D'tor
     */
    ~Vector();

    /**
     * return the lable of the vector
     * @return
     */
    std::string getLable();

    /**
     * return the value in index i
     * @param index
     * @return
     */
    double getValue(int index);

    /**
     * set the value in index i
     * @param index
     * @param value
     */
    void setValue(int index, double value);

    /**
     * return pointer for the next vector
     * @return
     */
    Vector* getNext();

    /**
     * set the pointer to the next vector
     * @param nextV
     */
    void setNext(Vector* nextV);

    /**
     * return true if the is next vector, else false.
     * @return
     */
    bool hasNext();

    /**
     * print the vector by Guy's format
     */
    void printVector();

    /**
     * return this->vector
     * @return
     */
    double* getVector();

    /**
     * set this->vector
     * @param vector
     */
    void setVector(double* vector );

    /**
     * Return the dimension of the vector.
     * @return
     */
    int getDim() const {return this->size;};

private:
    double* vector;
    std::string lable;
    int size;
    Vector* next = nullptr;
};


#endif //INC_01_VECTOR_H
