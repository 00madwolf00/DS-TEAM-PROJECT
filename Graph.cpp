/*
* Graph.cpp
* Names: Allicyan Chin, Jaheem Clayton, Jasmine Heymann
* Course: COP-3415
* Last Modified: 04/20/2025
*/

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
    for(auto* airport : adjacencyList) {
        delete airport;
    }
    adjacencyList.clear();
}

void Graph::addAirport(const string& code) {
    if(!airportExists(code)) {
        AirportNode* newAirport = new AirportNode(code);
        adjacencyList.push_back(newAirport);
    }
}

bool Graph::airportExists(string code) const {
    for(const auto& airport : adjacencyList) {
        if(airport->getCode() == code)
            return true;
    }
    return false;
}

AirportNode* Graph::getAirport(string code) const {
    for(const auto& airport : adjacencyList) {
        if(airport->getCode() == code)
            return airport;
    }
    return nullptr;
}

void Graph::addFlight(string origin, string destination, double distance, double cost) {
    AirportNode* originNode = getAirport(origin);
    AirportNode* destNode = getAirport(destination);

    if(originNode && destNode) {
        Edge* edge = new Edge(destNode, distance, cost);
        originNode->addEdge(edge);
    } else {
        cout << "Flight not added: " << origin << " or " << destination << " not found.\n";
    }
}

void Graph::displayGraph() const {
    for(const auto& airport : adjacencyList) {
        cout << airport->getCode() << " -> ";
        for(Edge* edge : airport->getEdges()) {
            cout << "(" << edge->to->getCode()
                 << ", " << edge->distance << " mi, $" << edge->cost << ") ";
        }
        cout << endl;
    }
}

void Graph::dijkstra(string start, string end, bool useCost) {
    AirportNode* startNode = getAirport(start);
    AirportNode* endNode = getAirport(end);

    if(!startNode || !endNode) {
        cout << "Start or end airport does not exist.\n";
        return;
    }

    // Reset visited and costs
    unordered_map<AirportNode*, double> dist;
    unordered_map<AirportNode*, AirportNode*> prev;
    unordered_map<AirportNode*, bool> visited;

    for(auto* airport : adjacencyList) {
        dist[airport] = numeric_limits<double>::infinity();
        prev[airport] = nullptr;
        visited[airport] = false;
    }

    dist[startNode] = 0;

    while(true) {
        AirportNode* current = nullptr;
        double minDist = numeric_limits<double>::infinity();

        for(auto* airport : adjacencyList) {
            if(!visited[airport] && dist[airport] < minDist) {
                minDist = dist[airport];
                current = airport;
            }
        }

        if(!current) break;
        visited[current] = true;

        for(Edge* edge : current->getEdges()) {
            AirportNode* neighbor = edge->to;
            double weight = useCost ? edge->cost : edge->distance;
            if(dist[current] + weight < dist[neighbor]) {
                dist[neighbor] = dist[current] + weight;
                prev[neighbor] = current;
            }
        }
    }

    if(dist[endNode] == numeric_limits<double>::infinity()) {
        cout << "No path from " << start << " to " << end << ".\n";
        return;
    }

    stack<AirportNode*> path;
    for(AirportNode* at = endNode; at != nullptr; at = prev[at]) {
        path.push(at);
    }

    cout << "Shortest path from " << start << " to " << end << ":\n";
    while(!path.empty()) {
        cout << path.top()->getCode();
        path.pop();
        if(!path.empty()) cout << " -> ";
    }

    cout << "\nTotal " << (useCost ? "cost" : "distance") << ": " << dist[endNode] << "\n";
}

void Graph::dijkstraToState(const string& originCode, const string& stateCode, bool useCost) {
    AirportNode* origin = getAirport(originCode);
    if(!origin) {
        cout << "Origin airport not found.\n";
        return;
    }

    unordered_map<AirportNode*, double> dist;
    unordered_map<AirportNode*, AirportNode*> prev;
    unordered_map<AirportNode*, bool> visited;

    for(auto* airport : adjacencyList) {
        dist[airport] = numeric_limits<double>::infinity();
        prev[airport] = nullptr;
        visited[airport] = false;
    }

    dist[origin] = 0;

    while(true) {
        AirportNode* current = nullptr;
        double minDist = numeric_limits<double>::infinity();

        for(auto* airport : adjacencyList) {
            if(!visited[airport] && dist[airport] < minDist) {
                minDist = dist[airport];
                current = airport;
            }
        }

        if(!current) break;
        visited[current] = true;

        for(Edge* edge : current->getEdges()) {
            AirportNode* neighbor = edge->to;
            double weight = useCost ? edge->cost : edge->distance;
            if(dist[current] + weight < dist[neighbor]) {
                dist[neighbor] = dist[current] + weight;
                prev[neighbor] = current;
            }
        }
    }

    // Output paths to airports in matching state
    bool found = false;
    for(auto* airport : adjacencyList) {
        if(airport == origin) continue;
        if(airport->getState() == stateCode && dist[airport] < numeric_limits<double>::infinity()) {
            found = true;
            stack<AirportNode*> path;
            for(AirportNode* at = airport; at != nullptr; at = prev[at])
                path.push(at);

            cout << "\nPath to " << airport->getCode() << " (" << airport->getCity() << ", " << airport->getState() << "): ";
            while(!path.empty()) {
                cout << path.top()->getCode();
                path.pop();
                if(!path.empty()) cout << " -> ";
            }

            cout << "\nTotal " << (useCost ? "cost" : "distance") << ": " << dist[airport] << "\n";
        }
    }

    if(!found) {
        cout << "No reachable airports found in state " << stateCode << ".\n";
    }
}

void Graph::shortestPathWithStops(string originCode, string destCode, int stops, bool useCost) {
    AirportNode* origin = getAirport(originCode);
    AirportNode* destination = getAirport(destCode);

    if(!origin || !destination) {
        cout << "Origin or destination not found.\n";
        return;
    }

    double bestValue = numeric_limits<double>::infinity();
    vector<AirportNode*> bestPath;

    function<void(AirportNode*, int, double, vector<AirportNode*>&)> dfs;
    dfs = [&](AirportNode* current, int remainingStops, double currentValue, vector<AirportNode*>& path) {
        path.push_back(current);

        if(remainingStops == 0) {
            if(current == destination && currentValue < bestValue) {
                bestValue = currentValue;
                bestPath = path;
            }
            path.pop_back();
            return;
        }

        for(Edge* edge : current->getEdges()) {
            double nextValue = currentValue + (useCost ? edge->cost : edge->distance);
            dfs(edge->to, remainingStops - 1, nextValue, path);
        }

        path.pop_back();
    };

    vector<AirportNode*> path;
    dfs(origin, stops, 0, path);

    if(bestPath.empty()) {
        cout << "No path from " << originCode << " to " << destCode << " with exactly " << stops << " stops.\n";
        return;
    }

    cout << "Best path from " << originCode << " to " << destCode
         << " with exactly " << stops << " stops:\n";

    for(size_t i = 0; i < bestPath.size(); ++i) {
        cout << bestPath[i]->getCode();
        if(i + 1 < bestPath.size()) cout << " -> ";
    }

    cout << "\nTotal " << (useCost ? "cost" : "distance") << ": " << bestValue << "\n";
}

void Graph::displayConnectionStats() const {
    struct Stat {
        string code;
        int inbound = 0;
        int outbound = 0;

        int total() const { 
            return inbound + outbound; 
        }
    };

    unordered_map<string, Stat> stats;

    // First pass: initialize stats
    for(const auto* airport : adjacencyList) {
        string code = airport->getCode();
        stats[code].code = code;
        stats[code].outbound = static_cast<int>(airport->getEdges().size());
    }

    // Second pass: count inbound connections
    for(const auto* airport : adjacencyList) {
        for(Edge* edge : airport->getEdges()) {
            string destCode = edge->to->getCode();
            stats[destCode].inbound++;
        }
    }

    // Move to vector and sort
    vector<Stat> result;
    for(const auto& pair : stats) {
        result.push_back(pair.second);
    }

    sort(result.begin(), result.end(), [](const Stat& a, const Stat& b) {
        return a.total() > b.total();  // sort by total connections descending
    });

    // Print
    cout << "\n=== Airport Connection Stats ===\n";
    cout << "Code\tInbound\tOutbound\tTotal\n";
    for(const Stat& s : result) {
        cout << s.code << "\t" << s.inbound << "\t" << s.outbound << "\t\t" << s.total() << "\n";
    }
}

void Graph::createUndirectedGraph() {
    undirectedEdges.clear();

    unordered_map<string, unordered_map<string, double>> minCostEdges;

    for(auto* airport : adjacencyList) {
        string fromCode = airport->getCode();
        
        for(Edge* edge : airport->getEdges()) {
            string toCode = edge->to->getCode();
            double cost = edge->cost;
            
            if(minCostEdges[fromCode].find(toCode) == minCostEdges[fromCode].end() && 
               minCostEdges[toCode].find(fromCode) == minCostEdges[toCode].end()) {
                minCostEdges[fromCode][toCode] = cost;
            } else if(minCostEdges[fromCode].find(toCode) != minCostEdges[fromCode].end()) {
                minCostEdges[fromCode][toCode] = min(minCostEdges[fromCode][toCode], cost);
            } else if(minCostEdges[toCode].find(fromCode) != minCostEdges[toCode].end()) {
                if(cost < minCostEdges[toCode][fromCode]) {
                    minCostEdges[toCode].erase(fromCode);
                    minCostEdges[fromCode][toCode] = cost;
                }
            }
        }
    }

    for(const auto& fromPair : minCostEdges) {
        string fromCode = fromPair.first;
        AirportNode* fromNode = getAirport(fromCode);
        
        for(const auto& toPair : fromPair.second) {
            string toCode = toPair.first;
            double cost = toPair.second;
            
            AirportNode* toNode = getAirport(toCode);
            
            undirectedEdges.push_back(UndirectedEdge(fromNode, toNode, cost));
        }
    }

    cout << "Undirected graph with " << undirectedEdges.size() << " edges created." << endl;
}

void Graph::primMST() {
    // Create undirected graph if not already done
    if(undirectedEdges.empty()) {
        createUndirectedGraph();
    }
    
    // Check if we have airports
    if(adjacencyList.empty()) {
        cout << "No airports in the graph." << endl;
        return;
    }
    
    // Set of airports included in MST
    unordered_map<string, bool> inMST;
    
    // Priority queue to find minimum weight edge
    priority_queue<pair<double, pair<AirportNode*, AirportNode*>>, 
                  vector<pair<double, pair<AirportNode*, AirportNode*>>>,
                  greater<pair<double, pair<AirportNode*, AirportNode*>>>> pq;
    
    // Store MST edges
    vector<pair<pair<string, string>, double>> mstEdges;
    
    // Start with first airport
    AirportNode* startAirport = adjacencyList[0];
    
    // Build adjacency list for undirected graph
    unordered_map<string, vector<pair<string, double>>> adjList;
    for(const auto& edge : undirectedEdges) {
        string fromCode = edge.from->getCode();
        string toCode = edge.to->getCode();
        double cost = edge.cost;
        
        adjList[fromCode].push_back({toCode, cost});
        adjList[toCode].push_back({fromCode, cost}); // Add reverse edge for undirected graph
    }
    
    // Add all edges from starting airport to priority queue
    string startCode = startAirport->getCode();
    inMST[startCode] = true;
    
    for(const auto& neighbor : adjList[startCode]) {
        string toCode = neighbor.first;
        double cost = neighbor.second;
        pq.push({cost, {startAirport, getAirport(toCode)}});
    }
    
    double totalCost = 0;
    
    cout << "\n=== Minimal Spanning Tree (Prim's Algorithm) ===\n";
    cout << "Edge\t\tWeight\n";
    
    // Process until priority queue is empty
    while(!pq.empty() && mstEdges.size() < adjacencyList.size() - 1) {
        auto top = pq.top();
        pq.pop();
        
        double cost = top.first;
        AirportNode* from = top.second.first;
        AirportNode* to = top.second.second;
        
        string toCode = to->getCode();
        
        // Skip if destination airport is already in MST
        if(inMST[toCode]) continue;
        
        // Add destination to MST
        inMST[toCode] = true;
        
        // Add edge to MST
        mstEdges.push_back({{from->getCode(), toCode}, cost});
        totalCost += cost;
        
        // Print edge
        cout << from->getCode() << " - " << toCode << "\t" << cost << "\n";
        
        // Add all edges from destination airport to priority queue
        for(const auto& neighbor : adjList[toCode]) {
            string nextCode = neighbor.first;
            if(!inMST[nextCode]) {
                double nextCost = neighbor.second;
                pq.push({nextCost, {to, getAirport(nextCode)}});
            }
        }
    }
    
    // Check if MST was created successfully
    if(mstEdges.size() != adjacencyList.size() - 1) {
        cout << "Could not form a Minimal Spanning Tree. The graph is disconnected.\n";
    } else {
        cout << "Total Cost of MST: " << totalCost << "\n";
    }
}

void Graph::kruskalMST() {
    // Create undirected graph if not already done
    if(undirectedEdges.empty()) {
        createUndirectedGraph();
    }
    
    // Sort edges by cost
    vector<UndirectedEdge> sortedEdges = undirectedEdges;
    sort(sortedEdges.begin(), sortedEdges.end());
    
    // Disjoint Set data structure for cycle detection
    unordered_map<string, string> parent;
    
    // Initialize each airport as its own set
    for(auto* airport : adjacencyList) {
        string code = airport->getCode();
        parent[code] = code;
    }
    
    // Find function for disjoint set with path compression
    function<string(string)> find = [&](string code) {
        if(parent[code] != code)
            parent[code] = find(parent[code]);
        return parent[code];
    };
    
    // Union function for disjoint set
    auto unionSets = [&](string x, string y) {
        parent[find(x)] = find(y);
    };
    
    vector<UndirectedEdge> mstEdges;
    double totalCost = 0;
    
    cout << "\n=== Minimal Spanning Tree (Kruskal's Algorithm) ===\n";
    cout << "Edge\t\tWeight\n";
    
    for(const auto& edge : sortedEdges) {
        string fromCode = edge.from->getCode();
        string toCode = edge.to->getCode();
        
        // If including this edge doesn't form a cycle, include it in MST
        if(find(fromCode) != find(toCode)) {
            mstEdges.push_back(edge);
            totalCost += edge.cost;
            
            // Print edge
            cout << fromCode << " - " << toCode << "\t" << edge.cost << "\n";
            
            // Union the sets
            unionSets(fromCode, toCode);
        }
    }
    
    // Count the number of components
    unordered_set<string> components;
    for(auto* airport : adjacencyList) {
        components.insert(find(airport->getCode()));
    }
    
    if(components.size() > 1) {
        cout << "The graph is disconnected, forming a forest with " << components.size() << " components.\n";
    }
    
    cout << "Total Cost of MST/Forest: " << totalCost << "\n";
}
