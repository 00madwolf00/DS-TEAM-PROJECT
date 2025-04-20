#include "Edge.h"


//gonna be turning the destinations into index's instead of names for faster sortinh purposes
Edge::Edge(AirportNode* dest, double dist, double c) {
    to = dest;
    distance = dist;
    cost = c;
}
