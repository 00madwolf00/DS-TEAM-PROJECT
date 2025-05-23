/*
* Graph.h
* Names: Allicyan Chin, Jaheem Clayton, Jasmine Heymann
* Course: COP-3415
* Last Modified: 04/20/2025
*/

#ifndef GRAPH_H
#define GRAPH_H
using namespace std;

#include "AirportNode.h"
#include "Edge.h"
#include <vector>
#include <unordered_set>

class Graph {
private:
    struct Node {
        AirportNode airport;
        vector<Edge> edges;
    };

    struct UndirectedEdge{
        AirportNode* from;
        AirportNode* to;
        double cost;

        UndirectedEdge(AirportNode* f, AirportNode* t, double c) : from(f), to(t), cost(c) {}

        bool operator<(const UndirectedEdge& other) const {
            return cost < other.cost;
        }
    };

    vector<AirportNode*> adjacencyList;
    vector<UndirectedEdge> undirectedEdges;

public:
    Graph();
    ~Graph();
    void shortestPathWithStops(string originCode, string destCode, int stops, bool useCost);
    void displayConnectionStats() const;

    void addAirport(const string& code);
    void addFlight(string origin, string destination, double distance, double cost);

    AirportNode* getAirport(string code) const;
    bool airportExists(string code) const;

    void displayGraph() const;
    void dijkstra(string start, string end, bool useCost);
    void dijkstraToState(const string& originCode, const string& stateCode, bool useCost);
    
    void loadFromCSV(const string& filename);

    void createUndirectedGraph();
    void primMST();
    void kruskalMST();
};

#endif
