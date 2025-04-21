/*
* AirportNode.h
* Names: Allicyan Chin, Jaheem Clayton, Jasmine Heymann
* Course: COP-3415
* Last Modified: 04/20/2025
*/

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
    const vector<Edge*>& getEdges() const; 

    bool operator==(const AirportNode& other){
        return code == other.code;
    }
};

#endif //AIRPORT_H
