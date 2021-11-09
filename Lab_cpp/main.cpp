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

    int tempID;
    std::map<int, Pipe>::iterator pipesIterator;  //  https://www.cplusplus.com/reference/map/map/find/
    std::map<int, Station>::iterator stationsIterator;

    while (1) {
        printMenu();
        switch (inputInteger()) {
        case 0:
            cout << "\nExit\n";
            return 0;
        case 1:
            mapOfPipes.insert(pair<int, Pipe>(mapOfPipes.size(), Pipe()));
            Pipe::id++;
            break;
        case 2:
            mapOfStation.insert(pair<int, Station>(mapOfStation.size(), Station()));
            Station::id++;
            break;
        case 3:
            cout << "\nOutput Pipe(s)";
            for (auto item : mapOfPipes) {
                cout << "\nID: " << item.first;
                item.second.Output();
            }

            cout << "\nOutput station(s)";
            for (auto item : mapOfStation) {
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
            Save(mapOfPipes, mapOfStation);
            break;
        case 7:
            Load(mapOfPipes, mapOfStation);
            break;
        case 8:
            filter(mapOfPipes);
            break;
        default:
            break;
        }
    }
    return 0;
}