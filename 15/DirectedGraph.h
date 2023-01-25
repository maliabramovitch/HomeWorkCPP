//
// Created by Mali Abramovitch
// Created by Alon Negrin
//

#ifndef INC_05_DIRECTEDGRAPH_H
#define INC_05_DIRECTEDGRAPH_H


#include <vector>
#include <ostream>
#include <algorithm>
#include <string>

class DirectedGraph {
private:
    std::vector<std::string> elementToIndex;
    std::vector<std::vector<double>> matrix;

public:
    DirectedGraph();

    DirectedGraph(const DirectedGraph &other);

    DirectedGraph &operator=(const DirectedGraph &other);

    ~DirectedGraph();

    void addVertex(std::string v);

    bool removeVertex(std::string v);

    void addEdge(std::string v1, std::string v2, double weight);

    bool removeEdge(std::string v1, std::string v2);

    bool updateWeight(std::string v1, std::string v2, double weight);

    double getWeight(std::string v1, std::string v2);

    std::vector<std::string> getFromVertex(std::string v);

    std::vector<std::string>& getConnectionsFromVertex(std::string v);

    std::vector<std::string> getToVertex(std::string v);

    friend std::ostream &operator<<(std::ostream &os, DirectedGraph &dg);

    bool containsVertex(std::string v);

    int getIndex(std::string v);

    void recursiveHelper(std::string source, std::vector<std::string>& ret);

};

bool DirectedGraph::containsVertex(std::string v) {
    if (std::find(elementToIndex.begin(), elementToIndex.end(), v) == elementToIndex.end())
        return false;
    return true;
}


int DirectedGraph::getIndex(std::string v) {
    if (!containsVertex(v)) return -1;
    return std::find(elementToIndex.begin(), elementToIndex.end(), v) - elementToIndex.begin();
}


DirectedGraph::DirectedGraph() {
    elementToIndex = std::vector<std::string>();
    matrix = std::vector<std::vector<double>>();
}


DirectedGraph::DirectedGraph(const DirectedGraph &other) {
    matrix = std::vector<std::vector<double>>(other.matrix);
    elementToIndex = std::vector<std::string>(other.elementToIndex);
}

template<typename V>
DirectedGraph &DirectedGraph<V>::operator=(const DirectedGraph &other) {
    if (this == &other) {
        return *this;
    }
    matrix = other.matrix;
    elementToIndex = other.elementToIndex;
    return *this;
}


DirectedGraph::~DirectedGraph() {
    for (std::vector<double> vect: matrix) {
        vect.clear();
    }
    matrix.clear();
    elementToIndex.clear();
}

void DirectedGraph::addVertex(V v) {
    if (!containsVertex(v))
        return;
    elementToIndex.push_back(v);
    for (std::vector<double> vect: matrix) {
        vect.push_back(0.0);
    }
    matrix.push_back(std::vector<double>(matrix.size() + 1, 0));
}

bool DirectedGraph<std::string>::removeVertex(std::string v) {
    if (!containsVertex(v))
        return false;
    int index = getIndex(v);
    matrix.erase(matrix.begin() + index);
    for (std::vector<double> vect: matrix) {
        vect.erase(vect.begin() + index);
    }
    elementToIndex.erase(elementToIndex.begin() + index);
    return true;
}


void DirectedGraph::addEdge(V v1, V v2, double weight) {
    addVertex(v1);
    addVertex(v2);
    updateWeight(v1, v2, weight);
}


bool DirectedGraph<std::string>::removeEdge(V v1, V v2) {
    return updateWeight(v1, v2, 0.0);
}


bool DirectedGraph<V>::updateWeight(std::string v1, std::string v2, double weight) {
    if (!containsVertex(v1) || !containsVertex(v2))
        return false;
    if (weight < 0.0) {
        return false;
    }
    int indexV1 = getIndex(v1);
    int indexV2 = getIndex(v2);
    matrix[indexV1][indexV2] = weight;
    return true;
}

double DirectedGraph<V>::getWeight(V v1, V v2) {
    if (!containsVertex(v1) || !containsVertex(v2))
        return false;
    int indexV1 = getIndex(v1);
    int indexV2 = getIndex(v2);
    return matrix[indexV1][indexV2];
}


std::vector<std::string> DirectedGraph::getFromVertex(std::string v) {
    if (!containsVertex(v)) return nullptr;
    std::vector<V> ret = std::vector<V>();
    int indexV = getIndex(v);
    std::vector<double> tmp = matrix[indexV];
    for (int i = 0; i < tmp.size(); ++i) {
        if (tmp[i] > 0.0) {
            ret.push_back(elementToIndex[i]);
        }
    }
    return ret;
}

std::vector<V>& DirectedGraph::getConnectionsFromVertex(std::string v) {
    std::vector<V> connections = std::vector<V>();
    recursiveHelper(v, connections);
    return connections;
}

void  DirectedGraph<V>::recursiveHelper(std::string source, std::vector<std::string>& ret) {
    if (std::find(ret.begin(), ret.end(), source) != ret.end())
        return;
    ret.push_back(source);
    std::vector<std::string> destination = getFromVertex(source);
    if (destination.empty()) {
        return;
    }
    for (int i = 0; i < destination.size(); ++i) {
            recursiveHelper(destination[i], ret);
    }
    return;
}

std::vector<std::string> DirectedGraph::getToVertex(std::string v) {
    if (!containsVertex(v)) return nullptr;
    std::vector<std::string> ret = std::vector<std::string>();
    int indexV = getIndex(v);
    for (int i = 0; i < matrix.size(); ++i) {
        if (matrix[i][indexV] > 0.0) {
            ret.push_back(elementToIndex[i]);
        }
    }
    return ret;
}

std::ostream &operator<<(std::ostream &os, DirectedGraph &dg) {
    for (int i =0; i < dg.elementToIndex.size(); ++i){
        std::string element = dg.elementToIndex[i];
        os << element << ":\t";
        std::vector<std::string> out = dg.getFromVertex(element);
        if (out != nullptr) {
            for (int j = 0; j < out.size(); ++j) {
                os << out[j] << " " ;
            }
        }
         os << "\n";
    }
    return os;
}


#endif //INC_05_DIRECTEDGRAPH_H


