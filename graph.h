//
// Created by kote on 27.09.15.
//

#ifndef YACOURSE_GRAPH_H
#define YACOURSE_GRAPH_H

#endif //YACOURSE_GRAPH_H

#include <vector>
#include <unordered_map>

using namespace std;

typedef tuple<int, int> tuple_key_t;

struct key_hash : public unary_function<tuple_key_t, size_t> {
    size_t operator()(const tuple_key_t &k) const;
};

typedef unordered_map<tuple<int, int>, int, key_hash> arc_map;

template<typename TWeight>
class IGraph {
public:
    virtual vector<int> *getAdjacencyList(int vertexNumber) = 0;

    virtual TWeight getArcWeight(int sourceVertex, int destVertex) = 0;
};

class SimpleGraph : public IGraph<int> {
    vector<vector<int> *> *_adjacencyList;
    arc_map *_arcWeights;
public:
    vector<int> *getAdjacencyList(int vertexNumber);

    int getArcWeight(int sourceVertex, int destVertex);

    int size();

    SimpleGraph(vector<vector<int> *> *adjacencyList, arc_map *arcWeights);

    ~SimpleGraph();
};

SimpleGraph read_graph_from_file(string fileName);