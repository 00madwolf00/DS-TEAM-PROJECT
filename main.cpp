#include <iostream>
#include "Graph.h"

using namespace std;

int main() {
    Graph g;

    // Add sample airports
    g.addAirport("ATL");
    g.addAirport("MIA");
    g.addAirport("JFK");

    // Add flights
    g.addFlight("ATL", "MIA", 595, 123);
    g.addFlight("ATL", "JFK", 740, 199);
    g.addFlight("JFK", "MIA", 1090, 250);

    // Display the graph
    g.printGraph();

    return 0;
}
