/*
* Edge.cpp
* Names: Allicyan Chin, Jaheem Clayton, Jasmine Heymann
* Course: COP-3415
* Last Modified: 04/20/2025
*/

#include "Edge.h"


//gonna be turning the destinations into index's instead of names for faster sortinh purposes
Edge::Edge(AirportNode* dest, double dist, double c) {
    to = dest;
    distance = dist;
    cost = c;
}
