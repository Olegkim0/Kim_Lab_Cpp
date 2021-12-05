#pragma once
#include "Network.h"

using namespace std;

int Pipe::id = 0;
int Station::id = 0;

int main()
{
    Network net;

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
            net.editObjectById(net.pipesMap);
            break;
        case 5:
            net.editObjectById(net.stationsMap);
            break;
        case 6:
            net.outputMap(net.pipesMap);
            if (net.pipesMap.size() != 0) {
                cout << "\nInput ID or 0 to exit\n";
                net.pipesMap.erase(choose(Pipe::id));
            }
            else
                cout << "No pipes";
            break;
        case 7:
            net.outputMap(net.stationsMap);
            if (net.stationsMap.size() != 0) {
                cout << "\nInput ID or 0 to exit\n";
                net.stationsMap.erase(choose(Station::id));
            }
            else
                cout << "No stations";
            break;
        case 8:
            net.filtration(net.pipesMap, net.search(net.pipesMap));
            break;
        case 9:
            net.filtration(net.stationsMap, net.search(net.stationsMap));
            break;
        case 10:
            net.save();
            break;
        case 11:
            net.load();
            break;
        default:
            break;
        }
    }
    return 0;
}