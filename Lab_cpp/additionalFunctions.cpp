#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include "Station.h"
#include "Pipe.h"
#include <vector>

using namespace std;

int inputInteger() {
    string str;
    cin.ignore();
    cin >> str;
    if (str.find_first_not_of("0123456789") != string::npos) {
        cout << "Wrong input\n";
        cout << "Try again: \n";
    }
    else {
        return stoi(str);
    }
return -1;
}

double inputDouble() {
    string str;
    cin.ignore();
    cin >> str;
    if (str.find_first_not_of("0123456789.") != string::npos || str.length() == count(str.begin(), str.end(), '.')) {
        cout << "Wrong input\n";
        cout << "Try again: \n";
    }
    else {
        return stod(str);
    }
    return -1;
}

void Save(const map<int, Pipe>& pipesMap, const map<int, Station>& stationsMap) {
    ofstream file;
    file.open("database.txt");
    if (file.good()) {
        if (pipesMap.size() != 0) {
            for (const auto& item : pipesMap) {
                file << "Pipe:\n";
                file << item.first << "\n";
                file << item.second.diameter << "\n";
                file << item.second.length << "\n";
                file << item.second.isWorking << "\n";
            }
        }
        if (stationsMap.size() != 0) {
            for (const auto& item : stationsMap) {
                file << "Station:\n";
                file << item.first << "\n";
                file << item.second.name << "\n";
                file << item.second.number_of_workshops << "\n";
                file << item.second.number_of_working_workshops << "\n";
                file << item.second.Efficiency << "\n";
            }
        }
        file.close();
        cout << "Saved\n";
    }
}

void printMenu() {
    cout << "\nMenu:\n";
    cout << "1. Add pipe\n";
    cout << "2. Add station\n";
    cout << "3. Output\n";
    cout << "4. Edit pipe\n";
    cout << "5. Edit station\n";
    cout << "6. Save\n";
    cout << "7. Load\n";
    cout << "0. Exit\n\n";
}

void Load(map<int, Pipe>& pipesMap, map<int, Station>& stationsMap) {
    ifstream file;
    file.open("database.txt");
    if (file.good()) {
        while (!file.eof()) {
            string type;
            file >> type;
            if (type == "Pipe:") {
                Pipe tempPipe;
                file >> tempPipe.id;
                file >> tempPipe.diameter;
                file >> tempPipe.length;
                file >> tempPipe.isWorking;
                pipesMap.insert(pair<int, Pipe>(pipesMap.size(), tempPipe));
            }

            if (type == "Station:") {
                Station tempStation;
                file >> tempStation.id;
                file >> tempStation.name;
                file >> tempStation.number_of_workshops;
                file >> tempStation.number_of_working_workshops;
                file >> tempStation.Efficiency;
                stationsMap.insert(pair<int, Station>(stationsMap.size(), tempStation));
            }
        }
    }
    cout << "Loaded\n";
}

void filter(map<int, Pipe>& pipesMap) {
    int choose;
    cout << "Filter by:\n1) name\n2) is working?\n0) Exit";
    do
        choose = inputInteger();
    while (choose != 0 || choose != 1 || choose != 2);
    
    string name;
    bool isWorking;
    vector<int> vectorID;
    switch (choose)
    {
    case 0:
        return;
    case 1:
        cout << "Input name:";
        cin >> name;

        for (auto& item : pipesMap) {
            if (item.second.name == name) {
                vectorID.push_back(item.first);
            }
        }
    case 2:
        do
        {
            isWorking = inputInteger();
        } while (isWorking != 0 || isWorking != 1);
        for (auto& item : pipesMap)
            if (item.second.isWorking == isWorking)
                vectorID.push_back(item.first);
        break;
    default:
        break;

        for (auto i : vectorID)
            cout << i;
    }
}

void filter(map<int, Station>& stationsMap) {
    int choose;
    cout << "Filter by:\n1) name\n2) percent of non working stations?\n0) Exit";
    do
        choose = inputInteger();
    while (choose != 0 || choose != 1 || choose != 2);

    string name;
    bool isWorking;
    vector<int> vectorID;
    switch (choose)
    {
    case 0:
        return;
    case 1:
        cout << "Input name:";
        cin >> name;

        for (auto& item : stationsMap) {
            if (item.second.name == name) {
                vectorID.push_back(item.first);
            }
        }
    case 2:
        do
        {
            isWorking = inputInteger();
        } while (isWorking != 0 || isWorking != 1);
        for (auto& item : stationsMap)
            if (item.second.isWorking == isWorking)
                vectorID.push_back(item.first);
        break;
    default:
        break;

        for (auto i : vectorID)
            cout << i;
    }
}