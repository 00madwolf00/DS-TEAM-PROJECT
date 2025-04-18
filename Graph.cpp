#include "Graph.h"
#include <iostream>

Graph::Graph() {}

void Graph::addAirport(const string& code) {
    if (!airportExists(code)) {
        AirportNode newAirport(code);
        Node node = { newAirport, {} };
        adjacencyList.push_back(node);
    }
}

bool Graph::airportExists(string code) const {
    for (const auto& node : adjacencyList) {
        if (node.airport.name == code) return true;
    }
    return false;
}

int Graph::getAirportIndex(string code) const {
    for (int i = 0; i < adjacencyList.size(); ++i) {
        if (adjacencyList[i].airport.name == code)
            return i;
    }
    return -1;
}

void Graph::addFlight(string origin, string destination, double distance, double cost) {
    int originIndex = getAirportIndex(origin);
    int destIndex = getAirportIndex(destination);

    if (originIndex != -1 && destIndex != -1) {
        Edge edge(destIndex, distance, cost);
        adjacencyList[originIndex].edges.push_back(edge);
    } else {
        cout << "Flight not added: " << origin << " or " << destination << " not found." << endl;
    }
}

void Graph::displayGraph() const {
    for (int i = 0; i < adjacencyList.size(); ++i) {
        cout << adjacencyList[i].airport.name << " -> ";
        for (auto& edge : adjacencyList[i].edges) {
            cout << "(" << adjacencyList[edge.to].airport.name
                 << ", " << edge.distance << " mi, $" << edge.cost << ") ";
        }
        cout << endl;
    }
}
