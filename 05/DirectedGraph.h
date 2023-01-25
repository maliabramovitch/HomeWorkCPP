//
// Created by Mali Abramovitch
// Created by Alon Negrin
//

#ifndef INC_51_DIRECTEDGRAPH_H
#define INC_51_DIRECTEDGRAPH_H

#include <vector>
#include <ostream>
#include <algorithm>
#include <string>

class DirectedGraph {
private:
    std::vector<std::string> elementToIndex;
    std::vector<std::vector<int>> matrix;

public:
    DirectedGraph();

    DirectedGraph(const DirectedGraph &other);

    DirectedGraph &operator=(const DirectedGraph &other);

    ~DirectedGraph();

    void addVertex(std::string v);

    bool removeVertex(std::string v);

    void addEdge(std::string v1, std::string v2, int weight);

    bool removeEdge(std::string v1, std::string v2);

    bool updateWeight(std::string v1, std::string v2, int weight);

    int getWeight(std::string v1, std::string v2);

    std::vector<std::string> getFromVertex(std::string v);

    std::vector<std::string> getConnectionsFromVertex(std::string v);

    std::vector<std::string> getToVertex(std::string v);

    friend std::ostream &operator<<(std::ostream &os, DirectedGraph &dg);

    bool containsVertex(std::string v);

    int getIndex(std::string v);

    void recursiveHelper(std::string source, std::vector<std::string>& ret);

};

#endif //INC_51_DIRECTEDGRAPH_H
