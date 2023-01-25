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

template<typename V=std::string>
class DirectedGraph {
private:
    std::vector<V> elementToIndex;
    std::vector<std::vector<double>> matrix;

public:
    DirectedGraph();

    DirectedGraph(const DirectedGraph<V> &other);

    DirectedGraph<V> &operator=(const DirectedGraph<V> &other);

    ~DirectedGraph();

    void addVertex(V v);

    bool removeVertex(V v);

    void addEdge(V v1, V v2, double weight);

    bool removeEdge(V v1, V v2);

    bool updateWeight(V v1, V v2, double weight);

    double getWeight(V v1, V v2);

    std::vector<V> getFromVertex(V v);

    std::vector<V>& getConnectionsFromVertex(V v);

    std::vector<V> getToVertex(V v);

    template<typename E>
    friend std::ostream &operator<<(std::ostream &os, DirectedGraph<E> &dg);

    bool containsVertex(V v);

    int getIndex(V v);

    void recursiveHelper(V source, std::vector<V>& ret);

};

template<typename V>
bool DirectedGraph<V>::containsVertex(V v) {
    if (std::find(elementToIndex.begin(), elementToIndex.end(), v) == elementToIndex.end())
        return false;
    return true;
}

template<typename V>
int DirectedGraph<V>::getIndex(V v) {
    if (!containsVertex(v)) return -1;
    return std::find(elementToIndex.begin(), elementToIndex.end(), v) - elementToIndex.begin();
}

template<typename V>
DirectedGraph<V>::DirectedGraph() {
    elementToIndex = std::vector<V>();
    matrix = std::vector<std::vector<double>>();
}

template<typename V>
DirectedGraph<V>::DirectedGraph(const DirectedGraph<V> &other) {
    matrix = std::vector<std::vector<double>>(other.matrix);
    elementToIndex = std::vector<V>(other.elementToIndex);
}

template<typename V>
DirectedGraph<V> &DirectedGraph<V>::operator=(const DirectedGraph<V> &other) {
    if (this == &other) {
        return *this;
    }
    matrix = other.matrix;
    elementToIndex = other.elementToIndex;
    return *this;
}

template<typename V>
DirectedGraph<V>::~DirectedGraph() {
    for (std::vector<double> vect: matrix) {
        vect.clear();
    }
    matrix.clear();
    elementToIndex.clear();
}

template<typename V>
void DirectedGraph<V>::addVertex(V v) {
    if (!containsVertex(v))
        return;
    elementToIndex.push_back(v);
    for (std::vector<double> vect: matrix) {
        vect.push_back(0.0);
    }
    matrix.push_back(std::vector<double>(matrix.size() + 1, 0));
}

template<typename V>
bool DirectedGraph<V>::removeVertex(V v) {
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

template<typename V>
void DirectedGraph<V>::addEdge(V v1, V v2, double weight) {
    addVertex(v1);
    addVertex(v2);
    updateWeight(v1, v2, weight);
}

template<typename V>
bool DirectedGraph<V>::removeEdge(V v1, V v2) {
    return updateWeight(v1, v2, 0.0);
}

template<typename V>
bool DirectedGraph<V>::updateWeight(V v1, V v2, double weight) {
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

template<typename V>
double DirectedGraph<V>::getWeight(V v1, V v2) {
    if (!containsVertex(v1) || !containsVertex(v2))
        return false;
    int indexV1 = getIndex(v1);
    int indexV2 = getIndex(v2);
    return matrix[indexV1][indexV2];
}

template<typename V>
std::vector<V> DirectedGraph<V>::getFromVertex(V v) {
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

template<typename V>
std::vector<V>& DirectedGraph<V>::getConnectionsFromVertex(V v) {
    std::vector<V> connections = std::vector<V>();
    recursiveHelper(v, connections);
    return connections;
}

template<typename V>
void  DirectedGraph<V>::recursiveHelper(V source, std::vector<V>& ret) {
    if (std::find(ret.begin(), ret.end(), source) != ret.end())
        return;
    ret.push_back(source);
    std::vector<V> destination = getFromVertex(source);
    if (destination.empty()) {
        return;
    }
    for (int i = 0; i < destination.size(); ++i) {
            recursiveHelper(destination[i], ret);
    }
    return;
}

template<typename V>
std::vector<V> DirectedGraph<V>::getToVertex(V v) {
    if (!containsVertex(v)) return nullptr;
    std::vector<V> ret = std::vector<V>();
    int indexV = getIndex(v);
    for (int i = 0; i < matrix.size(); ++i) {
        if (matrix[i][indexV] > 0.0) {
            ret.push_back(elementToIndex[i]);
        }
    }
    return ret;
}

template<typename V>
std::ostream &operator<<(std::ostream &os, DirectedGraph<V> &dg) {
    for (int i =0; i < dg.elementToIndex.size(); ++i){
        V element = dg.elementToIndex[i];
        os << element << ":\t";
        std::vector<V> out = dg.getFromVertex(element);
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


