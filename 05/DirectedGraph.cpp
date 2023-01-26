//
// Created by Mali Abramovitch
// Created by Alon Negrin
//

#include "DirectedGraph.h"

//default C'tor
DirectedGraph::DirectedGraph() {
    elementToIndex = std::vector<std::string>();
    matrix = std::vector<std::vector<int>>();
}

//copy C'tor
DirectedGraph::DirectedGraph(const DirectedGraph &other) {
    matrix = std::vector<std::vector<int>>(other.matrix);
    elementToIndex = std::vector<std::string>(other.elementToIndex);
}

// copy assignment
DirectedGraph &DirectedGraph::operator=(const DirectedGraph &other) {
    if (this == &other) {
        return *this;
    }
    matrix = other.matrix;
    elementToIndex = other.elementToIndex;
    return *this;
}

// D'tor
DirectedGraph::~DirectedGraph() {
    for (std::vector<int> vect: matrix) {
        vect.clear();
    }
    matrix.clear();
    elementToIndex.clear();
}
// end of The Rule Of Three

/**
 * add vertex to the graph
 * @param v
 */
void DirectedGraph::addVertex(std::string v) {
    if (containsVertex(v))
        return;
    elementToIndex.push_back(v);
    for (std::vector<int>& vect: matrix) {
        vect.push_back(0);
    }
    matrix.push_back(std::vector<int>(matrix.size() + 1, 0));
}

/**
 * remove vertex from the graph
 * @param v
 * @return true if succeeded, false otherwise.
 */
bool DirectedGraph::removeVertex(std::string v) {
    if (!containsVertex(v))
        return false;
    int index = getIndex(v);
    matrix.erase(matrix.begin() + index);
    for (std::vector<int>& vect: matrix) {
        vect.erase(vect.begin() + index);
    }
    elementToIndex.erase(elementToIndex.begin() + index);
    return true;
}

/**
 * add egde to the graph
 * @param v1
 * @param v2
 * @param weight
 */
void DirectedGraph::addEdge(std::string v1, std::string v2, int weight) {
    addVertex(v1);
    addVertex(v2);
    updateWeight(v1, v2, weight);
}

/**
 * remove egde from the graph
 * @param v1
 * @param v2
 * @return true if succeeded, false otherwise.
 */
bool DirectedGraph::removeEdge(std::string v1, std::string v2) {
    return updateWeight(v1, v2, 0);
}

/**
 * updetes the weight of the edge from v1 to v2.
 * @param v1
 * @param v2
 * @param weight
 * @return true if succeeded, false otherwise.
 */
bool DirectedGraph::updateWeight(std::string v1, std::string v2, int weight) {
    if (!containsVertex(v1) || !containsVertex(v2))
        return false;
    if (weight < 0) {
        return false;
    }
    int indexV1 = getIndex(v1);
    int indexV2 = getIndex(v2);
    matrix[indexV1][indexV2] = weight;
    return true;
}

int DirectedGraph::getWeight(std::string v1, std::string v2) {
    if (!containsVertex(v1) || !containsVertex(v2))
        return -1;
    int indexV1 = getIndex(v1);
    int indexV2 = getIndex(v2);
    return matrix[indexV1][indexV2];
}

/**
 *
 * @param v
 * @return vector that contains all neighboring vertices
 */
std::vector<std::string> DirectedGraph::getFromVertex(std::string v) {
    std::vector<std::string> ret = std::vector<std::string>();
    if (!containsVertex(v)) return ret;
    int indexV = getIndex(v);
    std::vector<int> tmp = matrix[indexV];
    for (unsigned int i = 0; i < tmp.size(); ++i) {
        if (tmp[i] > 0) {
            ret.push_back(elementToIndex[i]);
        }
    }
    return ret;
}

/**
 *
 * @param v
 * @return a vector which contains all vertices that connected to v.
 */
std::vector<std::string> DirectedGraph::getConnectionsFromVertex(std::string v) {
    std::vector<std::string> connections = std::vector<std::string>();
    recursiveHelper(v, connections);
    connections.erase(connections.begin());
    return connections;
}

void  DirectedGraph::recursiveHelper(std::string source, std::vector<std::string>& ret) {
    if (std::find(ret.begin(), ret.end(), source) != ret.end())
        return;
    ret.push_back(source);
    std::vector<std::string> destination = getFromVertex(source);
    if (destination.empty()) {
        return;
    }
    for (unsigned int i = 0; i < destination.size(); ++i) {
        recursiveHelper(destination.at(i), ret);
    }
    return;
}

/**
 *
 * @param v
 * @return a vector that continues all vertices that connected to v.
 */
std::vector<std::string> DirectedGraph::getToVertex(std::string v) {
    std::vector<std::string> ret = std::vector<std::string>();
    if (!containsVertex(v)) return ret;
    int indexV = getIndex(v);
    for (unsigned int i = 0; i < matrix.size(); ++i) {
        if (matrix[i][indexV] > 0) {
            ret.push_back(elementToIndex[i]);
        }
    }
    return ret;
}

std::ostream &operator<<(std::ostream &os, DirectedGraph &dg) {
    for (unsigned int i =0; i < dg.elementToIndex.size(); ++i){
        std::string element = dg.elementToIndex[i];
        os << element << ":\t";
        std::vector<std::string> out = dg.getFromVertex(element);
        if (!out.empty()) {
            for (unsigned int j = 0; j < out.size(); ++j) {
                os << out[j] << " " ;
            }
        }
        os << "\n";
    }
    return os;
}

/**
 *
 * @param v
 * @return return true if v is in graph, false otherwise.
 */
bool DirectedGraph::containsVertex(std::string v) {
    if (std::find(elementToIndex.begin(), elementToIndex.end(), v) == elementToIndex.end())
        return false;
    return true;
}

/**
 *
 * @param v
 * @return the corresponding index of v in the vector indexToElement that representing map.
 */
int DirectedGraph::getIndex(std::string v) {
    if (!containsVertex(v)) return -1;
    return std::find(elementToIndex.begin(), elementToIndex.end(), v) - elementToIndex.begin();
}


