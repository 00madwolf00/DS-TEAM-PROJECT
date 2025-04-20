/*
* CSVRead.cpp
* Names: Allicyan Chin, Jaheem Clayton, Jasmine Heymann
* Course: COP-3415
* Last Modified: 04/19/2025
*/

#include "CSVRead.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

bool CSVReader::loadAirportsCSV(const std::string& filename, Graph<string>& graph){
    ifstream file(filename);
    
    if(!file.is_open()){
        cerr << "Error: Could not open file " << filename << endl;
        return false;
    }
    
    string line;
    
    getline(file, line);
    
    int lineCount = 0;
    
    while(getline(file, line)){
        lineCount++;

        stringstream ss(line);
        string origin, destination, originCity, destCity, distStr, costStr;
        
        getline(ss, origin, ',');
        getline(ss, destination, ',');
        getline(ss, originCity, ',');
        getline(ss, destCity, ',');
        getline(ss, distStr, ',');
        getline(ss, costStr, ',');
        
        string originState = "";
        size_t commaPos = originCity.find_last_of(',');

        if(commaPos != string::npos){
            originState = originCity.substr(commaPos + 2); // +2 to skip comma and space
            originCity = originCity.substr(0, commaPos);
        }
        
        string destState = "";
        commaPos = destCity.find_last_of(',');

        if(commaPos != string::npos){
            destState = destCity.substr(commaPos + 2);
            destCity = destCity.substr(0, commaPos);
        }
        
        int distance = 0;
        int cost = 0;
        
        try{
            distance = stoi(distStr);
            cost = stoi(costStr);
        }catch(const exception& e){
            cerr << "Error reading line " << lineCount << ": " << e.what() << endl;
            continue;
        }
        
        Vertex<string> v_origin(origin);
        Vertex<string> v_dest(destination);
        
        graph.insert_vertex(v_origin);
        graph.insert_vertex(v_dest);
        
        graph.add_airport_info(origin, originCity, originState);
        graph.add_airport_info(destination, destCity, destState);
        
        try{
            graph.add_edge(v_origin, v_dest, distance, cost);
        }catch(const string& e){
            cerr << "Error adding the flight: " << e << endl;
        }
    }
    
    file.close();
    cout << "Loaded " << lineCount << " flights from " << filename << endl;
    return true;
}
