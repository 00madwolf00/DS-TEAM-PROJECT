#include "Edge.h"

Edge::Edge(AirportNode* dest, double dist, double c) {
    to = dest;
    distance = dist;
    cost = c;
}
