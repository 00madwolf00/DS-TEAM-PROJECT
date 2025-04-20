#ifndef GRAPH_H
#define GRAPH_H
using namespace std;

#include "AirportNode.h"
#include "Edge.h"
#include <vector>

class Graph {
private:
    struct Node {
        AirportNode airport;
        vector<Edge> edges;
    };

    vector<AirportNode*> adjacencyList;

public:
    Graph();
    ~Graph();

    void addAirport(const string& code) ;
    void addFlight(string origin, string destination, double distance, double cost);

    AirportNode* getAirport(string code) const;
    bool airportExists(string code) const;

    void displayGraph() const;
    void dijkstra(string start, string end, bool useCost);

    void loadFromCSV(const string& filename);

    
};

#endif