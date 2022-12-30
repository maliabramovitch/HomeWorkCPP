//
// Created by Mali Abramovitch on 16/11/2022.
//

#include "VectorLinkedList.h"
#include "Vector.h"
#include <iostream>
#include <string>

using namespace std;

VectorLinkedList::VectorLinkedList(int maxViews, int vectorDim) {
    this->headVector = nullptr;
    this->maxViews = maxViews;
    this->vectorDim = vectorDim;
    this->lastView = -1;
}

VectorLinkedList::VectorLinkedList(Vector *v, int maxViews, int vectorDim) {
    this->headVector = v;
    this->maxViews = maxViews;
    this->vectorDim = vectorDim;
    this->lastView = -1;
}

VectorLinkedList::~VectorLinkedList() {
    if (lastView == -1) {
        return;
    }
    if (lastView == 0) {
        delete this->headVector;
        return;
    }
    Vector *tmp = this->headVector;
    Vector *tmp2 = tmp->getNext();
    while (tmp->hasNext()) {
        delete tmp;
        tmp = tmp2;
        tmp2 = tmp->getNext();
    }
    delete this;
}

void VectorLinkedList::addObservation(Vector *obs) {
    if (lastView == maxViews - 1) {
        cerr << "You have reached to the maximum size of Observations";
        return;
    }
    if (lastView == -1) {
        this->headVector = obs;
        this->lastView++;
        return;
    }
    Vector *tmp = this->headVector;
    while (tmp->hasNext()) {
        if (tmp->getLable() == obs->getLable()) {
            break;
        }
        tmp = tmp->getNext();
    }
    if (tmp->getLable() == obs->getLable()) {
        tmp->setVector(obs->getVector());
        return;
    }
    tmp->setNext(obs);
    lastView++;
}

Vector *VectorLinkedList::getObservation(const std::string &obs) {
    Vector *tmp = this->headVector;
    if (tmp == nullptr) {
        return nullptr;
    }
    while (tmp->getLable() != obs) {
        if (tmp->getNext() == nullptr) {
            cerr << "Invalid or nonexistent observation.\n";
            return nullptr;
        }
        tmp = tmp->getNext();
    }
    return tmp;
}

/**
 * private function to calculate mean- Expected value vector
 */
Vector *VectorLinkedList::calculateMean() {
    auto *mean = new Vector(vectorDim, "mean");
    Vector *tmp = this->headVector;
    for (int i = 0; i < (lastView + 1); ++i) {
        mean->setValue(i, 0);
    }
    for (int i = 0; i < (lastView + 1); i++) {
        for (int j = 0; j < vectorDim; j++) {
            float val = (float) mean->getValue(j) + tmp->getValue(j) * ((1.0 / (lastView + 1)));
            mean->setValue(j, val);
        }
        tmp = tmp->getNext();
    }
    return mean;
}

void VectorLinkedList::printExpectedValueVector() {
    if (lastView == -1) {
        cerr << "Empty calculator." << endl;
        return;
    }
    Vector *mean = calculateMean();
    mean->printVector();
    delete mean;
}

/**
 * priv.e function to calculate cov- Covariance matrix
 */
float **VectorLinkedList::calculateMeanCovarianceMatrix() {
    Vector *mean = calculateMean();
    float val;
    auto *mat = new float *[vectorDim];
    Vector *tmp = this->headVector;
    Vector *tmp2 = this->headVector;
    for (int i = 0; i < vectorDim; ++i) {
        mat[i] = new float [vectorDim];
    }
    for (int i = 0; i < lastView + 1; ++i) {
        for (int j = i; j < vectorDim; ++j) {
            for (int m = 0; m < (lastView + 1); ++m) {
                val= (float) ((tmp->getValue(i) - (mean->getValue(i))) * (tmp2->getValue(j)- (mean->getValue(j))));
                mat [i][j] += val;
                tmp = tmp->getNext();
                tmp2 = tmp2->getNext();
            }
            if (lastView > 0) {
                mat[i][j] *= (float) (1.0/lastView);
                mat[j][i] = mat[i][j];
            }

            tmp2 = this->headVector;
            tmp = this->headVector;
        }

    }
    delete mean;
    return mat;
}

void VectorLinkedList::printCovarianceMatrix() {
    if (lastView == -1) {
        cerr << "Empty calculator." << endl;
        return;
    }
    float **cov = calculateMeanCovarianceMatrix();
    cout << "cov = [" << endl;
    for (int i = 0; i < vectorDim; ++i) {
        for (int j = 0; j < vectorDim; ++j) {
            cout << ' ';
            cout << cov[i][j];

        }
        cout << endl;
        delete[] cov[i];
    }
    cout << ']';
    delete[] cov;
}


