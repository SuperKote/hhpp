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
    vector<int> getAdjacencyList(int vertexNumber);

    TWeight getArcWeight(int sourceVertex, int destVertex);
};

class SimpleGraph : public IGraph<int> {
    vector<vector<int>*>* _adjacencyList;
    arc_map* _arcWeights;
public:
    vector<int>* getAdjacencyList(int vertexNumber);

    int getArcWeight(int sourceVertex, int destVertex);
	SimpleGraph(vector<vector<int>*>* adjacencyList, arc_map* arcWeights);
	~SimpleGraph();
    /* Smth like this?
     * {
        _arcWeights.clear();
        for(vector<vector<int>>::iterator it = _adjacencyList.begin(); it != _adjacencyList.end(); ++it) {
            (*it).clear();
        }
        _adjacencyList.clear();
    }*/ ;

};

SimpleGraph readGraphFromFile(string fileName);