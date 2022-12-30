#include <iostream>
#include <string>
#include "Vector.h"
#include "VectorLinkedList.h"
#include <sstream>

using namespace std;

/*
 * Everything below these are functions to manage the switch cases
 */

/**
 * add observation to the struct
 * @param mama
 * @param vectorDim
 */
void addObs(VectorLinkedList *mama, int vectorDim);

/**
 * asks for a label and prints the given view, if the label does no exist it prints warning
 * @param mama
 */
void printObs(VectorLinkedList *mama);

/**
 * prints the expected vector
 * @param mama
 */
void printExpected(VectorLinkedList *mama);


/**
 * prints the covariance matrix
 * @param mama
 */
void printCovariance(VectorLinkedList *mama);


/**
 * Checks that the initial conditions are fulfilled
 * @param argc
 * @param argv
 */
void ChecksLegality(int argc, char **argv);

int main(int argc, char *argv[]) {
    ChecksLegality(argc, argv);
    string userStr;
    int choise = 0;
    int vectorDim = stoi(argv[1]);
    int maxView = stoi(argv[2]);
    auto *mama = new VectorLinkedList(maxView, vectorDim); //MAMA FOR MATRIX
    cout
            << "[1] New observation\n[2] Print observation\n[3] Expected value vector\n[4] Covariance matrix\n[5] Exit"
            << endl;
    cin >> choise;
    while (true) {
        switch (choise) {
            case 1:
                addObs(mama, vectorDim);
                break;
            case 2:
                printObs(mama);
                break;
            case 3:
                printExpected(mama);
                break;
            case 4:
                printCovariance(mama);
                break;
            case 5:
                delete mama;
                return 0;
            default:
                cerr << "Invalid option" << endl;
                break;
        }
        cin >> choise;
    }
}


void addObs(VectorLinkedList *mama, int vectorDim) {
    string userStr, vector, name;
    int count = 0;
    cout << "Enter observation name:" << endl;
    cin.ignore();
    getline(cin, name);
    auto *v = new Vector(vectorDim, name);
    cout << "Enter observation values:" << endl;
    getline(cin, vector);
    for (long unsigned int i = 0; i < (vector.size() + 1); ++i) { //checks if the input is in the right size
        if (vector[i] == ' ' || vector[i] == '\0' || vector[i] == '\n') {
            count++;
        }
    }
    if (count != vectorDim) {
        cerr << "Invalid observation." << endl;
        return;
    }
    stringstream buff(vector);
    for (int i = 0; i < vectorDim; ++i) {
        buff >> vector;
        v->setValue(i, stod(vector));
    }
    mama->addObservation(v);
}

void printObs(VectorLinkedList *mama) {
    string userStr;
    cout << "Enter observation name:" << endl;
    cin >> userStr;
    Vector *v = mama->getObservation(userStr);
    if (v == nullptr) {
        cerr << "Invalid or nonexistent observation." << endl;
        return;
    }
    v->printVector();
}

void printExpected(VectorLinkedList *mama) {
    mama->printExpectedValueVector();
}

void printCovariance(VectorLinkedList *mama) {
    mama->printCovarianceMatrix();
}

void ChecksLegality(int argc, char **argv) {
    if (argc < 3) {
        cerr << "Invalid arguments <" << '-' << '>' << " <" << '-' << ">" << endl;
    }
    if (stoi(argv[1]) > 10 || stoi(argv[1]) < 1 || stoi(argv[2]) > 3000 || stoi(argv[2]) < 1) {
        cerr << "Invalid arguments <" << argv[1] << '>' << " <" << argv[2] << ">" << endl;
    }
}
