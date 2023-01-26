//
// Created by Mali Abramovitch
// Created by Alon Negrin
//

#ifndef INC_51_NEVERLAND_H
#define INC_51_NEVERLAND_H

#include "DirectedGraph.h"
class Neverland {
private:
    DirectedGraph* dg;
    void writeToFile(std::string outFile); // penning a file and write the graph to the file.
public:
    Neverland(); // default C'tor
    Neverland(const Neverland& other); // copy C'tor
    Neverland& operator=(const Neverland& other); // copy assignment
    ~Neverland(); // D'tor

    void initTransportLine(std::string fileName); // reads the file and initialize the transport lines
    void getLinesInfo(std::string outFile); // get the source and returns the required information



};


#endif //INC_51_NEVERLAND_H
