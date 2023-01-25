//
// Created by Mali Abramovitch
// Created by Alon Negrin
//

#include "Neverland.h"
#include <sstream>
#include <fstream>
#include "MyException.h"
#include <iostream>

using namespace std;

Neverland::Neverland() {
    dg = new DirectedGraph();
}

Neverland::Neverland(const Neverland &other) {
    dg = new DirectedGraph(*other.dg);
}

Neverland &Neverland::operator=(const Neverland &other) {
    if (this == &other) {
        return *this;
    }
    *dg = *other.dg;
    return *this;
}

Neverland::~Neverland() {
    delete dg;
}

void Neverland::initTransportLine(std::string fileName) {
    ifstream readFile(fileName);
    if (!readFile) {
        throw MyException("ERROR: " + fileName + " does not exist or cannot be opened\n");
    }
    string text;
    getline(readFile, text);
    stringstream s(text);
    string v1, v2, weight;
    s >> v1;
    s >> v2;
    s >> weight;
    int w = stoi(weight);
    if (w < 0 || !s || v1 == "exit" || v2 == "exit")
        throw MyException("ERROR: node definition in " + fileName + " is invalid\n");
    int getWeight = dg->getWeight(v1, v2);
    if (getWeight != -1 && getWeight < w) {
        dg->updateWeight(v1, v2, w);
    } else if (getWeight == -1) {
        dg->addEdge(v1, v2, w);
    }
}


void Neverland::getLinesInfo(string outFile="output.dat") {
    writeToFile(outFile);
    string userInput;
    while (true) {
        cin >> userInput;
        if (userInput == "exit") {
            return;
        }
        if (!dg->containsVertex(userInput)) {
            cout << userInput << " does not exist in the current network\n"
                 << "USAGE: <node> or ‘exit’ to terminate\n";
            continue;
        }
        vector<string> stations = dg->getFromVertex(userInput);
        if (stations.empty()) {
            cout << userInput << " : no outbound travel\n";
            continue;
        } else {
            cout << userInput;
            for (const string & station : stations) {
                cout << '\t';
                cout << station;
            }
            cout << '\n';
        }
    }
}


void Neverland::writeToFile(std::string outFile) {
    ofstream out(outFile);
    if (!out) {
        throw MyException("ERROR: " + outFile + " does not exist or cannot be opened\n");
    }
    out << *dg;
}
