//
// Created by Mali Abramovitch on 16/11/2022.
//

#ifndef INC_01_VECTORLINKEDLIST_H
#define INC_01_VECTORLINKEDLIST_H

#include "Vector.h"
#include <string>

class VectorLinkedList {

public:
    /**
     * C'tor that gets the maximum number of views and the vector dimension.
     * @param maxViews
     * @param vectorDim
     */
    VectorLinkedList(int maxViews, int vectorDim);

    /**
     * C'tor that gets the maximum number of views,the vector dimension and the first vector.
     * @param v
     * @param maxViews
     * @param vectorDim
     */
    VectorLinkedList(Vector *v, int maxViews, int vectorDim);

    /**
     *
     * D'tor.
     */
    ~VectorLinkedList();

    /**
     * Adds observation to the struct.
     * @param obs
     */
    void addObservation(Vector *obs);

    /**
     * Return observation by its label.
     * @param obs
     * @return
     */
    Vector *getObservation(const std::string &obs);

    /**
     * Calculates and prints the expected vector.
     */
    void printExpectedValueVector();

    /**
     * Calculates and prints the cCovariance matrix
     */
    void printCovarianceMatrix();

    /**
     * return the size of the actual struct
     * @return
     */
    int size() const {return lastView + 1;};

    /**
     * Returns the maximum number of views.
     * @return
     */
    int getMaxViews() const {return maxViews;};

private:
    int maxViews;
    int vectorDim;
    int lastView;
    Vector *headVector;
    Vector * calculateMean();
    float ** calculateMeanCovarianceMatrix();
};
#endif //INC_01_VECTORLINKEDLIST_H
