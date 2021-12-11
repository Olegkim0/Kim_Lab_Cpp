#pragma once
#include "Network.h"
#include "Menu.h"

using namespace std;

int Pipe::id = 0;
int Station::id = 0;

int main()
{
    Menu menu;
    Network net;

    while (true) {
        printMenu();
        switch (choose(14)) {
        case 0:
            std::cout << "\nExit\n";
            return 0;
        case 1:
            net.pipesMap.insert({Pipe::id, menu.addPipe()});
            break;
        case 2:
            net.stationsMap.insert({Station::id, menu.addStation()});
            break;
        case 3:
            menu.output(net.pipesMap, net.stationsMap);
            break;
        case 4:
            menu.outputMap(net.pipesMap);
            net.editing(menu.getIDs(Pipe::id), net.pipesMap);
            break;
        case 5:
            menu.outputMap(net.stationsMap);
            net.editing(menu.getIDs(Station::id), net.stationsMap);
            break;
        case 6:
            menu.outputMap(net.pipesMap);
            net.deleting(menu.getIDs(Pipe::id), net.pipesMap);
            break;
        case 7:
            menu.outputMap(net.stationsMap);
            net.deleting(menu.getIDs(Station::id), net.stationsMap);
            break;
        case 8:
            net.filtration(net.pipesMap, net.search(net.pipesMap));
            break;
        case 9:
            net.filtration(net.stationsMap, net.search(net.stationsMap));
            break;
        case 10:
            net.connect(menu.getIDsForConnect(net.pipesMap, net.stationsMap));
            break;
        case 11:
            net.disconnect(menu.getIDs(Pipe::id));
            break;
        case 12:
            net.topologicalSort(net.pipesMap, net.stationsMap);
            break;
        case 13:
            net.save(menu.getStr());
            break;
        case 14:
            net.load(menu.getStr());
        default:
            break;
        }
    }
    return 0;
}