//
// Created by Mali Abramovitch on 16/11/2022.
//

#include "Vector.h"
#include <string>
#include <iostream>


using namespace std;


Vector::Vector(int size, const string& lable) {
    this->size = size;
    this->lable = lable;
    vector = new double[size];
    this->next = nullptr;
}

Vector::~Vector() {
    delete [] vector;
}

string Vector::getLable() {
    string cpyLable = lable;
    return cpyLable;
}

double Vector::getValue(int index) {
    return vector[index];
}

void Vector::setValue(int index, double value) {
    vector[index] = value;
}
Vector* Vector::getNext() {
    return this->next;
}

void Vector::setNext(Vector* nextV) {
    this->next = nextV;
}

bool Vector::hasNext() {
    if (this->next == nullptr)
        return false;
    return true;
}

void Vector::printVector() {
    cout << lable;
    cout << " = [";
    for (int i = 0; i < size; ++i) {
        cout << ' ';
        cout << vector [i];

    }
    cout << "]" << endl;
}

double *Vector::getVector() {
    return this->vector;
}

void Vector::setVector(double *v) {
    this->vector = v;
}





