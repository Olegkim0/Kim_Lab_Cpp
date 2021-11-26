#pragma once
#include "Pipe.h"
#include "Station.h"
#include "additionalFunctions.h"
#include <iostream>

using namespace std;

int Pipe::id = 0;
int Station::id = 0;

int main()
{
    map<int, Pipe> mapOfPipes;
    map<int, Station> mapOfStation;
    vector<int> pipesVectorID;
    vector<int> stationsVectorID;

    int tempID;
    std::map<int, Pipe>::iterator pipesIterator;  //  https://www.cplusplus.com/reference/map/map/find/
    std::map<int, Station>::iterator stationsIterator;

    while (true) {
        printMenu();
        switch (choose(11)) {
        case 0:
            cout << "\nExit\n";
            return 0;
        case 1:
            mapOfPipes.insert(pair<int, Pipe>(Pipe::id, Pipe()));
            break;
        case 2:
            mapOfStation.insert(pair<int, Station>(Station::id, Station()));
            break;
        case 3:
            cout << "\nOutput Pipe(s)";
            for (auto &item : mapOfPipes) {
                cout << "\nID: " << item.first;
                item.second.Output();
            }
            
            cout << "\nOutput station(s)";
            for (auto &item : mapOfStation) {
                cout << "\nID: " << item.first;
                item.second.Output();
            }    
            break;
        case 4:
            cout << "\ninput id\n";
            tempID = inputInteger();
            while (tempID > Pipe::id)
            {
                cout << "\nWrong input\n";
                tempID = inputInteger();
            }
            pipesIterator = mapOfPipes.find(tempID);
            
            if (pipesIterator != mapOfPipes.end())
                mapOfPipes[tempID].PipeEdit();
            else
            {
                cout << "\nWrong ID\n";
            }
            break;
        case 5:
            cout << "\ninput id\n";
            tempID = inputInteger();
            while (tempID > Station::id)
            {
                cout << "\nWrong input\n";
                tempID = inputInteger();
            }
            stationsIterator = mapOfStation.find(tempID);

            if (stationsIterator != mapOfStation.end())
                mapOfStation[tempID].StationEdit();
            else
            {
                cout << "\nWrong ID\n";
            }
            break;
        case 6:
            if (mapOfPipes.size() != 0)
                mapOfPipes.erase(choose(mapOfPipes.size() - 1));
            else
                cout << "No pipes";
            break;
        case 7:
            if (mapOfStation.size() != 0)
                mapOfStation.erase(choose(mapOfStation.size() - 1));
            else
                cout << "No stations";
            break;
        case 8:
            filtration(mapOfPipes, search(mapOfPipes));
            pipesVectorID.clear();
            break;
        case 9:
            filtration(mapOfStation, search(mapOfStation));
            stationsVectorID.clear();
            break;
        case 10:
            Save(mapOfPipes, mapOfStation);
            break;
        case 11:
            Load(mapOfPipes, mapOfStation);
            break;
        case 12:
            //  tests
            break;
        default:
            break;
        }
    }
    return 0;
}