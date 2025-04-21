#include <iostream>
#include "Graph.h"
#include "CSVRead.h"

using namespace std;

int main() {
    Graph g;

    CSVReader::loadAirportsCSV("airports.csv", g);

    

    // Display the graph
    g.displayGraph();

     // Dijkstra using cost
     g.dijkstra("ATL", "MIA", true);

     // Dijkstra using distance
     g.dijkstra("ATL", "MIA", false);
     g.dijkstraToState("ORD", "CA", true);  // Or "DFW", "LAX", etc.

     cout << "\n=== Testing shortest path from ATL to LAX with exactly 2 stops (cost) ===\n";
     g.shortestPathWithStops("ABE", "BOS", 2, true);
     
     g.displayConnectionStats();

     cout << "\n=== Generating Undirected Graph Gᵤ ===\n";
Graph* undirected = g.createUndirectedGraph();
cout << "Undirected graph has " << undirected->adjacencyList.size() << " airports.\n";


cout << "\n=== Displaying Undirected Graph ===\n";



undirected->primMST();

    return 0;
}
