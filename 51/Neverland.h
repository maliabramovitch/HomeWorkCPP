//
// Created by Mali Abramovitch on 25/01/2023.
//

#ifndef INC_51_NEVERLAND_H
#define INC_51_NEVERLAND_H

#include "DirectedGraph.h"
class Neverland {
private:
    DirectedGraph* dg;
    void writeToFile(std::string outFile);
public:
    Neverland();
    Neverland(const Neverland& other);
    Neverland& operator=(const Neverland& other);
    ~Neverland();

    void initTransportLine(std::string fileName); // reads the file and initialize the transport lines
    void getLinesInfo(std::string outFile); // get the source and returns the required information



};


#endif //INC_51_NEVERLAND_H
