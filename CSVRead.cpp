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
#include <algorithm>

using namespace std;

bool CSVReader::loadAirportsCSV(const string& filename, Graph& graph) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return false;
    }

    string line;
    getline(file, line); // Skip header
    int lineCount = 0;

    auto parseCityState = [](const string& input, string& city, string& state) {
        size_t commaPos = input.find_last_of(',');
        if (commaPos != string::npos) {
            city = input.substr(0, commaPos);
            state = input.substr(commaPos + 1);
            city.erase(city.find_last_not_of(" \t\r\n") + 1);
            state.erase(0, state.find_first_not_of(" \t\r\n"));
        } else {
            city = input;
            state = "";
        }
    };

    while (getline(file, line)) {
        lineCount++;

        stringstream ss(line);
        string fields[6];

        for (int i = 0; i < 6 && getline(ss, fields[i], ','); ++i) {
            if (!fields[i].empty() && fields[i][0] == '\"' && fields[i].back() != '\"') {
                string continuation;
                while (getline(ss, continuation, ',')) {
                    fields[i] += "," + continuation;
                    if (!continuation.empty() && continuation.back() == '\"') break;
                }
            }

            // Strip quotes
            if (!fields[i].empty() && fields[i].front() == '\"') fields[i] = fields[i].substr(1);
            if (!fields[i].empty() && fields[i].back() == '\"') fields[i].pop_back();
        }

        string origin         = fields[0];
        string destination    = fields[1];
        string originCityRaw  = fields[2];
        string destCityRaw    = fields[3];
        string distStr        = fields[4];
        string costStr        = fields[5];

        string originCity, originState, destCity, destState;
        parseCityState(originCityRaw, originCity, originState);
        parseCityState(destCityRaw, destCity, destState);

        int distance = 0;
        int cost = 0;

        try {
            distance = stoi(distStr);
            cost = stoi(costStr);
        } catch (const exception& e) {
            cerr << "Error reading line " << lineCount << ": " << e.what() << endl;
            cerr << "  distance: '" << distStr << "', cost: '" << costStr << "'" << endl;
            continue;
        }

        graph.addAirport(origin);
        graph.addAirport(destination);

        AirportNode* originNode = graph.getAirport(origin);
        AirportNode* destNode = graph.getAirport(destination);

        if (originNode) {
            originNode->setCity(originCity);
            originNode->setState(originState);
        }

        if (destNode) {
            destNode->setCity(destCity);
            destNode->setState(destState);
        }

        graph.addFlight(origin, destination, distance, cost);
    }

    file.close();
    cout << "Loaded " << lineCount << " flights from " << filename << endl;
    return true;
}
