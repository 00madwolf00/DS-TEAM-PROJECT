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

    return 0;
}
