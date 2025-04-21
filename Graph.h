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

    struct UndirectedEdge{
        AirportNode* from;
        AirportNode* to;

        double cost;

        UndirectedEdge(AirportNode* f, AirportNode* t, double c) : from(f), to(t), cost(c) {}

        bool operator<(const UndirectedEdge& other){
            return cost < other.cost;
        }
    };

    vector<AirportNode*> adjacencyList;

public:
    Graph();
    ~Graph();
    void shortestPathWithStops(string originCode, string destCode, int stops, bool useCost);
    void displayConnectionStats() const;

    void addAirport(const string& code) ;
    void addFlight(string origin, string destination, double distance, double cost);

    AirportNode* getAirport(string code) const;
    bool airportExists(string code) const;

    void displayGraph() const;
    void dijkstra(string start, string end, bool useCost);
    void dijkstraToState(const string& originCode, const string& stateCode, bool useCost);

    void loadFromCSV(const string& filename);

    void makeUndirectedGraph();
    void primMST();
    void kruskalMST();
};

#endif
