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
 

    return 0;
}
