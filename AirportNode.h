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
    AirportNode(string& code, string& city, string& state);

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

    // Edge
    void addEdge(AirportNode* destination, double distance, double cost);
    vector<Edge*>& getEdges(){
        return outgoingEdges;
    }

    bool operator==(const AirportNode& other){
        return code == other.code;
    }
};

#endif //AIRPORT_H