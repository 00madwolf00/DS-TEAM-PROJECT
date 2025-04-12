#ifndef GRAPH_H
#define GRAPH_H

#include "AirportNode.h"
#include "Edge.h"
#include <vector>

class Graph {
private:
    struct Node {
        AirportNode airport;
        vector<Edge> edges;
    };

    vector<Node> adjacencyList;

public:
    Graph();

    void addAirport(const AirportNode& ap);
    void addFlight(string origin, const Edge& edge);

    int findAirportIndex(string code) const;
    bool airportExists(string code) const;

    void printGraph() const;
    
};

#endif