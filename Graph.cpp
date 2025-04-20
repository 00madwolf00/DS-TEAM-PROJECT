#include "Graph.h"
#include <iostream>
#include <limits>
#include <stack>
#include <fstream>
#include <sstream>
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
        if (node.airport.getCode() == code) return true;
    }
    return false;
}

int Graph::getAirportIndex(string code) const {
    for (int i = 0; i < adjacencyList.size(); ++i) {
        if (adjacencyList[i].airport.getCode() == code)
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
        cout << adjacencyList[i].airport.getCode() << " -> ";
        for (auto& edge : adjacencyList[i].edges) {
            cout << "(" << adjacencyList[edge.to].airport.getCode()
                 << ", " << edge.distance << " mi, $" << edge.cost << ") ";
        }
        cout << endl;
    }
}

void Graph::dijkstra(string start, string end, bool useCost) {
    int n = adjacencyList.size();
    int startIndex = getAirportIndex(start);
    int endIndex = getAirportIndex(end);

    if (startIndex == -1 || endIndex == -1) {
        cout << "Start or end airport does not exist.\n";
        return;
    }

    vector<double> dist(n, numeric_limits<double>::infinity());
    vector<int> prev(n, -1);
    vector<bool> visited(n, false);

    dist[startIndex] = 0;

    for (int i = 0; i < n; ++i) {
        // Find unvisited node with smallest dist
        int u = -1;
        double minDist = numeric_limits<double>::infinity();
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }

        if (u == -1) break; // all reachable nodes visited
        visited[u] = true;

        // Relax neighbors
        for (const Edge& edge : adjacencyList[u].edges) {
            int v = edge.to;
            double weight = useCost ? edge.cost : edge.distance;
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
            }
        }
    }

    if (dist[endIndex] == numeric_limits<double>::infinity()) {
        cout << "No path from " << start << " to " << end << ".\n";
        return;
    }

    // Reconstruct path
    stack<int> path;
    for (int at = endIndex; at != -1; at = prev[at])
        path.push(at);

    cout << "Shortest path from " << start << " to " << end << ":\n";
    while (!path.empty()) {
        cout << adjacencyList[path.top()].airport.getCode();
        path.pop();
        if (!path.empty()) cout << " -> ";
    }

    cout << "\nTotal " << (useCost ? "cost" : "distance") << ": " << dist[endIndex] << "\n";
}