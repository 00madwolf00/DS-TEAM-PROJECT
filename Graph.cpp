#include "Graph.h"
#include <iostream>
#include <limits>
#include <stack>
#include <queue>
#include <unordered_map>

Graph::Graph() {}

Graph::~Graph() {
    for (auto* airport : adjacencyList) {
        delete airport;
    }
    adjacencyList.clear();
}

void Graph::addAirport(const string& code) {
    if (!airportExists(code)) {
        AirportNode* newAirport = new AirportNode(code);
        adjacencyList.push_back(newAirport);
    }
}

bool Graph::airportExists(string code) const {
    for (const auto& airport : adjacencyList) {
        if (airport->getCode() == code)
            return true;
    }
    return false;
}

AirportNode* Graph::getAirport(string code) const {
    for (const auto& airport : adjacencyList) {
        if (airport->getCode() == code)
            return airport;
    }
    return nullptr;
}

void Graph::addFlight(string origin, string destination, double distance, double cost) {
    AirportNode* originNode = getAirport(origin);
    AirportNode* destNode = getAirport(destination);

    if (originNode && destNode) {
        Edge* edge = new Edge(destNode, distance, cost);
        originNode->addEdge(edge);
    } else {
        cout << "Flight not added: " << origin << " or " << destination << " not found.\n";
    }
}

void Graph::displayGraph() const {
    for (const auto& airport : adjacencyList) {
        cout << airport->getCode() << " -> ";
        for (Edge* edge : airport->getEdges()) {
            cout << "(" << edge->to->getCode()
                 << ", " << edge->distance << " mi, $" << edge->cost << ") ";
        }
        cout << endl;
    }
}

void Graph::dijkstra(string start, string end, bool useCost) {
    AirportNode* startNode = getAirport(start);
    AirportNode* endNode = getAirport(end);

    if (!startNode || !endNode) {
        cout << "Start or end airport does not exist.\n";
        return;
    }

    // Reset visited and costs
    unordered_map<AirportNode*, double> dist;
    unordered_map<AirportNode*, AirportNode*> prev;
    unordered_map<AirportNode*, bool> visited;

    for (auto* airport : adjacencyList) {
        dist[airport] = numeric_limits<double>::infinity();
        prev[airport] = nullptr;
        visited[airport] = false;
    }

    dist[startNode] = 0;

    while (true) {
        AirportNode* current = nullptr;
        double minDist = numeric_limits<double>::infinity();

        for (auto* airport : adjacencyList) {
            if (!visited[airport] && dist[airport] < minDist) {
                minDist = dist[airport];
                current = airport;
            }
        }

        if (!current) break;
        visited[current] = true;

        for (Edge* edge : current->getEdges()) {
            AirportNode* neighbor = edge->to;
            double weight = useCost ? edge->cost : edge->distance;
            if (dist[current] + weight < dist[neighbor]) {
                dist[neighbor] = dist[current] + weight;
                prev[neighbor] = current;
            }
        }
    }

    if (dist[endNode] == numeric_limits<double>::infinity()) {
        cout << "No path from " << start << " to " << end << ".\n";
        return;
    }

    stack<AirportNode*> path;
    for (AirportNode* at = endNode; at != nullptr; at = prev[at]) {
        path.push(at);
    }

    cout << "Shortest path from " << start << " to " << end << ":\n";
    while (!path.empty()) {
        cout << path.top()->getCode();
        path.pop();
        if (!path.empty()) cout << " -> ";
    }

    cout << "\nTotal " << (useCost ? "cost" : "distance") << ": " << dist[endNode] << "\n";
}
