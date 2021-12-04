#pragma once
#include "Network.h"

using namespace std;

int Pipe::id = 0;
int Station::id = 0;

int main()
{
    Network net;

    unordered_map<int, Pipe> mapOfPipes;
    unordered_map<int, Station> mapOfStation;

    int tempID;

    vector<int> vectorID;

    while (true) {
        printMenu();
        switch (choose(11)) {
        case 0:
            cout << "\nExit\n";
            return 0;
        case 1:
            net.pipesMap.insert(pair<int, Pipe>(Pipe::id, Pipe()));
            break;
        case 2:
            net.stationsMap.insert(pair<int, Station>(Station::id, Station()));
            break;
        case 3:
            net.output();
            break;
        case 4:
            cout << "\ninput id or 0 to exit\n";
            tempID = choose(Pipe::id);
            if (mapOfPipes.count(tempID))
                mapOfPipes[tempID].edit();
            break;

        case 5: 
            cout << "\ninput id\n";
            tempID = choose(Pipe::id);
            if (mapOfStation.count(tempID))
                mapOfStation[tempID].edit();
            break;
        case 6:
            cout << "Input ID or 0 to exit]\n";
            if (mapOfPipes.size() != 0 )
                mapOfPipes.erase(choose(Pipe::id));
            else
                cout << "No pipes";
            break;
        case 7:
            cout << "Input ID or 0 to exit]\n";
            if (mapOfStation.size() != 0)
                mapOfStation.erase(choose(Station::id));
            else
                cout << "No stations";
            break;
        case 8:
            //net.filtration(net.search<unordered_map<int, Pipe>(net.pipesMap));  //  devide search and filtration and ask user about change
            //net.search(net.pipesMap);
            break;
        case 9:
            //net.filtration(net.search(net.pipesMap));  //  devide search and filtration and ask user about change

            //filtration(mapOfStation, search(mapOfStation));
            break;
        case 10:
            //net.save();
            break;
        case 11:
            //net.load();
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