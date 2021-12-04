#pragma once
#include "Network.h"

void Network::output() {
    if (pipesMap.size() != 0) {
        cout << "\nOutput pipe(s)";
        for (auto& item : pipesMap) {
            cout << "\nID: " << item.first;
            item.second.output();
        }
    }
    
    if (stationsMap.size() != 0) {
        cout << "\nOutput station(s)";
        for (auto& item : stationsMap) {
            cout << "\nID: " << item.first;
            item.second.output();
        }
    }
}
