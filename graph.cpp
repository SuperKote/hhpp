#include "graph.h"
#include <iostream>
#include <fstream>
#include "boost/algorithm/string/split.hpp"
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <string>
#include <assert.h>
using namespace boost;

vector<vector<int>*>* createAdjacencyList(int nodeCount);

tuple<int, int, int> parseArc(string basic_string);

tuple<int, int> parseHeader(ifstream &inputStream);

tuple<vector<vector<int>*>*, arc_map*> parseBody(ifstream &inputStream, int nodeCount, int arcCount);

tuple<int, int> parseProblemLine(string line);



size_t key_hash::operator()(const tuple_key_t &k) const {
    return get<0>(k) ^ 367 + get<1>(k) ^ 367;
}

vector<int>* SimpleGraph::getAdjacencyList(int vertexNumber) { return _adjacencyList->at(vertexNumber); }

int SimpleGraph::getArcWeight(int sourceVertex, int destVertex) {
    tuple<int, int> key(sourceVertex, destVertex);
    arc_map::const_iterator searchResult = _arcWeights->find(key);
    return searchResult != _arcWeights->end() ? searchResult->second : INT16_MAX;
}

SimpleGraph::SimpleGraph(vector<vector<int>*> *adjacencyList, arc_map *arcWeights) {
    _adjacencyList = adjacencyList;
    _arcWeights = arcWeights;
}

SimpleGraph readGraphFromFile(string fileName) {
    ifstream sourceFile;
    sourceFile.open(fileName);
	auto header = parseHeader(sourceFile);
	auto body = parseBody(sourceFile, get<0>(header), get<1>(header));
    return SimpleGraph(get<0>(body), get<1>(body));
}

tuple<int, int> parseHeader(ifstream &inputStream) {
    string line;
    while (getline(inputStream, line)) {
        switch (line.at(0)) {
            case 'c':
                break;
            case 'p':
                return parseProblemLine(line);
            default:
                throw logic_error("Expected problem line as first non comment line.");
        }
    }
    throw logic_error("File is empty.");
};

tuple<int, int> parseProblemLine(string line) {
    vector<string> parts;
    split(parts, line, ' ');
    assert(parts.size() == 4);
    assert(parts.at(1) == "sp");
    return make_tuple(lexical_cast<int>(parts.at(2)), lexical_cast<int>(parts.at(3)));
};

tuple<vector<vector<int>*>*, arc_map*> parseBody(ifstream &inputStream, int nodeCount, int arcCount) {
	auto adjacencyList = createAdjacencyList(nodeCount);
	auto arcWeights = new arc_map(arcCount);
    string line;
    tuple<int, int, int> arc;
    vector<int>* listForNode;
    while (getline(inputStream, line)) {
        switch (line.at(0)) {
            case 'c':
                break;
            case 'a':
                arc = parseArc(line);
                listForNode = (*adjacencyList).at(get<0>(arc));
                listForNode->push_back(get<1>(arc));
                (*arcWeights)[make_tuple(get<0>(arc), get<1>(arc))] = get<2>(arc);
                break;
            default:
                throw logic_error("Dat file ez broken =\\");
        }        
    };
	return make_tuple(adjacencyList, arcWeights);
}


tuple<int, int, int> parseArc(string arc_string) {
    vector<string> parts;
    boost::split(parts, arc_string, is_any_of(" "));
    assert(parts.size() == 4);
    return make_tuple(lexical_cast<int>(parts.at(1)), lexical_cast<int>(parts.at(2)), lexical_cast<int>(parts.at(3)));		
}

vector<vector<int>*>* createAdjacencyList(int nodeCount) {
	auto adjacencyList = new vector<vector<int>*>(nodeCount);
    for (auto it = (*adjacencyList).begin(); it != (*adjacencyList).end(); ++it) {
        adjacencyList->push_back(new vector<int>());
    }
    return adjacencyList;
};