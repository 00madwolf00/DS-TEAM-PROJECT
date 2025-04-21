/*
* main.cpp
* Names: Allicyan Chin, Jaheem Clayton, Jasmine Heymann
* Course: COP-3415
* Last Modified: 04/20/2025
*/

#include <iostream>
#include "Graph.h"
#include "CSVRead.h"

using namespace std;

int main(){
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

    // Add the MST functionality calls
    cout << "\n=== Creating undirected graph ===\n";
    g.createUndirectedGraph();
    
    cout << "\n=== Running Prim's MST algorithm ===\n";
    g.primMST();
    
    cout << "\n=== Running Kruskal's MST algorithm ===\n";
    g.kruskalMST();

    return 0;
}
