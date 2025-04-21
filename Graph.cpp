#include "Graph.h"
#include <iostream>
#include <limits>
#include <stack>
#include <queue>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <unordered_set>


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
void Graph::dijkstraToState(const string& originCode, const string& stateCode, bool useCost) {
    AirportNode* origin = getAirport(originCode);
    if (!origin) {
        cout << "Origin airport not found.\n";
        return;
    }

    unordered_map<AirportNode*, double> dist;
    unordered_map<AirportNode*, AirportNode*> prev;
    unordered_map<AirportNode*, bool> visited;

    for (auto* airport : adjacencyList) {
        dist[airport] = numeric_limits<double>::infinity();
        prev[airport] = nullptr;
        visited[airport] = false;
    }

    dist[origin] = 0;

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

    // Output paths to airports in matching state
    bool found = false;
    for (auto* airport : adjacencyList) {
        if (airport == origin) continue;
        if (airport->getState() == stateCode && dist[airport] < numeric_limits<double>::infinity()) {
            found = true;
            stack<AirportNode*> path;
            for (AirportNode* at = airport; at != nullptr; at = prev[at])
                path.push(at);

            cout << "\nPath to " << airport->getCode() << " (" << airport->getCity() << ", " << airport->getState() << "): ";
            while (!path.empty()) {
                cout << path.top()->getCode();
                path.pop();
                if (!path.empty()) cout << " -> ";
            }

            cout << "\nTotal " << (useCost ? "cost" : "distance") << ": " << dist[airport] << "\n";
        }
    }

    if (!found) {
        cout << "No reachable airports found in state " << stateCode << ".\n";
    }
}
void Graph::shortestPathWithStops(string originCode, string destCode, int stops, bool useCost) {
    AirportNode* origin = getAirport(originCode);
    AirportNode* destination = getAirport(destCode);

    if (!origin || !destination) {
        cout << "Origin or destination not found.\n";
        return;
    }

    double bestValue = numeric_limits<double>::infinity();
    vector<AirportNode*> bestPath;

    function<void(AirportNode*, int, double, vector<AirportNode*>&)> dfs;
    dfs = [&](AirportNode* current, int remainingStops, double currentValue, vector<AirportNode*>& path) {
        path.push_back(current);

        if (remainingStops == 0) {
            if (current == destination && currentValue < bestValue) {
                bestValue = currentValue;
                bestPath = path;
            }
            path.pop_back();
            return;
        }

        for (Edge* edge : current->getEdges()) {
            double nextValue = currentValue + (useCost ? edge->cost : edge->distance);
            dfs(edge->to, remainingStops - 1, nextValue, path);
        }

        path.pop_back();
    };

    vector<AirportNode*> path;
    dfs(origin, stops, 0, path);

    if (bestPath.empty()) {
        cout << "No path from " << originCode << " to " << destCode << " with exactly " << stops << " stops.\n";
        return;
    }

    cout << "Best path from " << originCode << " to " << destCode
         << " with exactly " << stops << " stops:\n";

    for (size_t i = 0; i < bestPath.size(); ++i) {
        cout << bestPath[i]->getCode();
        if (i + 1 < bestPath.size()) cout << " -> ";
    }

    cout << "\nTotal " << (useCost ? "cost" : "distance") << ": " << bestValue << "\n";
}
void Graph::displayConnectionStats() const {
    struct Stat {
        string code;
        int inbound = 0;
        int outbound = 0;

        int total() const { return inbound + outbound; }
    };

    unordered_map<string, Stat> stats;

    // First pass: initialize stats
    for (const auto* airport : adjacencyList) {
        string code = airport->getCode();
        stats[code] = { code, 0, static_cast<int>(airport->getEdges().size()) };
    }

    // Second pass: count inbound connections
    for (const auto* airport : adjacencyList) {
        for (Edge* edge : airport->getEdges()) {
            string destCode = edge->to->getCode();
            stats[destCode].inbound++;
        }
    }

    // Move to vector and sort
    vector<Stat> result;
    for (const auto& pair : stats) {
        result.push_back(pair.second);
    }

    sort(result.begin(), result.end(), [](const Stat& a, const Stat& b) {
        return a.total() > b.total();  // sort by total connections descending
    });

    // Print
    cout << "\n=== Airport Connection Stats ===\n";
    cout << "Code\tInbound\tOutbound\tTotal\n";
    for (const Stat& s : result) {
        cout << s.code << "\t" << s.inbound << "\t" << s.outbound << "\t\t" << s.total() << "\n";
    }
}

void Graph::primMST() const {
    if (adjacencyList.empty()) {
        cout << "Graph is empty.\n";
        return;
    }

    struct Entry {
        AirportNode* from;
        AirportNode* to;
        double cost;

        bool operator>(const Entry& other) const {
            return cost > other.cost;
        }
    };

    unordered_set<AirportNode*> visited;
    priority_queue<Entry, vector<Entry>, greater<Entry>> pq;

    AirportNode* start = adjacencyList.front();  // start anywhere
    visited.insert(start);

    // Push all outgoing edges from start
    for (Edge* edge : start->getEdges()) {
        pq.push({ start, edge->to, edge->cost });
    }

    double totalCost = 0;
    vector<Entry> mstEdges;

    while (!pq.empty()) {
        Entry current = pq.top();
        pq.pop();

        if (visited.count(current.to)) continue;

        visited.insert(current.to);
        totalCost += current.cost;
        mstEdges.push_back(current);

        for (Edge* edge : current.to->getEdges()) {
            if (!visited.count(edge->to)) {
                pq.push({ current.to, edge->to, edge->cost });
            }
        }
    }

    if (mstEdges.size() != adjacencyList.size() - 1) {
        cout << "Graph is not fully connected. MST is a spanning forest.\n";
    }

    cout << "\n=== Prim's MST ===\n";
    for (const Entry& edge : mstEdges) {
        cout << edge.from->getCode() << " -> " << edge.to->getCode()
             << " ($" << edge.cost << ")\n";
    }

    cout << "Total MST cost: $" << totalCost << "\n";
}



Graph* Graph::createUndirectedGraph() const {
    Graph* undirected = new Graph();

    // Step 1: Add all airports
    for (AirportNode* airport : adjacencyList) {
        undirected->addAirport(airport->getCode());
        AirportNode* copy = undirected->getAirport(airport->getCode());
        copy->setCity(airport->getCity());
        copy->setState(airport->getState());
    }

    // Step 2: Add bidirectional edges
    unordered_set<string> added; // to avoid double adding

    for (AirportNode* airport : adjacencyList) {
        string origin = airport->getCode();

        for (Edge* edge : airport->getEdges()) {
            string dest = edge->to->getCode();
            string pairKey = origin < dest ? origin + "-" + dest : dest + "-" + origin;

            if (added.count(pairKey)) continue;

            // Check if reverse edge exists
            bool reverseFound = false;
            for (Edge* revEdge : edge->to->getEdges()) {
                if (revEdge->to == airport) {
                    reverseFound = true;

                    double lowerCost = min(edge->cost, revEdge->cost);
                    double avgDistance = (edge->distance + revEdge->distance) / 2.0;

                    undirected->addFlight(origin, dest, avgDistance, lowerCost);
                    undirected->addFlight(dest, origin, avgDistance, lowerCost); // symmetric

                    added.insert(pairKey);
                    break;
                }
            }
        }
    }

    return undirected;
}
