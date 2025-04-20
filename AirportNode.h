#ifndef AIRPORTNODE_H
#define AIRPORTNODE_H

#include <iostream>
#include <vector>

using namespace std;

class Edge;

class AirportNode{
private:
    string code;
    string city;
    string state;
    bool visited;
    vector<Edge*> outgoingEdges;

public:
    AirportNode(string& code, string& city, string& state)
        : code(code), city(city), state(state), visited(false) {}
    //constructor
    AirportNode(string code) : code(code), visited(false) {}
    
    ~AirportNode();
    
    // Getters
    string getCode() const{
        return code;
    }

    string getCity()const{
        return city;
    }

    string getState()const{
        return state;
    }

    bool isVisited()const{
        return visited;
    }
    
    // Setters
    void setVisited(bool v){
        visited = v;
    }
    void setCity(const string& c) {
         city = c; }

     void setState(const string& s) {
         state = s; }
    // Edge
    void addEdge(Edge* edge) { outgoingEdges.push_back(edge); }
    vector<Edge*>& getEdges() { return outgoingEdges; }

    bool operator==(const AirportNode& other){
        return code == other.code;
    }
};

#endif //AIRPORT_H