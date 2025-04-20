#include "AirportNode.h"
#include "Edge.h"

AirportNode::AirportNode(string& code, string& city, string& state) : code(code), city(city), state(state), visited(false) {}

AirportNode::~AirportNode(){
    for(Edge* edge : outgoingEdges){
        delete edge;
    }

    outgoingEdges.clear();
}

void AirportNode::addEdge(AirportNode* destination, double distance, double cost){
    Edge* newEdge = new Edge(destination, distance, cost);
    outgoingEdges.push_back(newEdge);
}
