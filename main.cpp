#include <iostream>
#include "Graph.h"

using namespace std;

int main() {
    Graph g;

    g.loadFromCSV("airports.csv");

    

    // Display the graph
    g.displayGraph();

     // Dijkstra using cost
     g.dijkstra("ATL", "MIA", true);

     // Dijkstra using distance
     g.dijkstra("ATL", "MIA", false);
 

    return 0;
}
