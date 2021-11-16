#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include "Station.h"
#include "Pipe.h"

using namespace std;

void printMenu() {
    cout << "\n\nMenu:\n";
    cout << "1. Add pipe\n";
    cout << "2. Add station\n";
    cout << "3. Output\n";
    cout << "4. Edit pipe\n";
    cout << "5. Edit station\n";
    cout << "6. Delete pipe\n";
    cout << "7. Delete station\n";
    cout << "8. Filter pipes\n";
    cout << "9. Filter stations\n";
    cout << "10. Save\n";
    cout << "11. Load\n";
    cout << "0. Exit\n\n";
}

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

int choose(int number) {
    int result;
    do
        result = inputInteger();
    while (result < 0 || result > number);
    
    return result;
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

vector<int> search(map<int, Pipe>& pipesMap) {

    vector<int> vectorID;

    if (pipesMap.size() == 0)
        return vectorID;

    cout << "Filter by:\n1) name\n2) is working?\n0) Exit\n";

    string name;
    bool isWorking;
    switch (choose(2))
    {
    case 0:
        return vectorID;
    case 1:
        cout << "Input name:\n";
        cin >> name;
        for (auto& item : pipesMap) {
            if (item.second.name == name) {
                vectorID.push_back(item.first);
            }
        }
        break;
    case 2:
        do
        {
            isWorking = inputInteger();
        } while (isWorking < 0 || isWorking > 1);
        for (auto& item : pipesMap)
            if (item.second.isWorking == isWorking)
                vectorID.push_back(item.first);
        break;
    default:
        break;
    }
    cout << "ID: ";
    for (int i : vectorID)
        cout << i << "  ";
    return vectorID;
}

vector<int> search(map<int, Station>& stationsMap) {
    vector<int> vectorID;
    if (stationsMap.size() == 0)
        return vectorID;

    int choose;
    cout << "\nFilter by:\n1) name\n2) percent of non working stations?\n0) Exit\n";
    do
        choose = inputInteger();
    while (choose < 0 || choose > 2);

    string name;
    double percentOfWorkshops;
    switch (choose)
    {
    case 0:
        return vectorID;
    case 1:
        cout << "\nInput name:\n";
        cin >> name;
        for (auto& item : stationsMap) {
            if (item.second.name == name) {
                vectorID.push_back(item.first);
            }
        }
        break;
    case 2:
        cout << "\nInput percent of non working stations\n";
        do
        {
            percentOfWorkshops = inputDouble();
        } while (percentOfWorkshops <= 0 || percentOfWorkshops > 100);
        if (percentOfWorkshops == 0)
            return vectorID;
        
        do
        {
            cout << "\n1) less\n2) more\n0) exit\n";
            choose = inputInteger();
        } while (choose < 0 || choose > 2);

        if (choose == 1)
            for (auto& item : stationsMap)
                if ((1.0 * item.second.number_of_working_workshops / (1.0 * item.second.number_of_workshops)) * 100 < percentOfWorkshops)
                    vectorID.push_back(item.first);
        else if (choose == 2)
            for (auto& item : stationsMap)
                if ((1.0 * item.second.number_of_working_workshops / (1.0 * item.second.number_of_workshops)) * 100 >= percentOfWorkshops)
                    vectorID.push_back(item.first);
        break;
    default:
        break; 
    }
    cout << "ID: ";
    for (int i : vectorID)
        cout << i << "  ";
    return vectorID;
}

void filtration(map<int, Pipe>& pipesMap, vector<int> vectorID) {
    cout << "Edit all or set of stations?\n0) all\n 1)set\n";
    switch (choose(1)) {
    case 0:
        for (auto& item : pipesMap) {
            item.second.PipeEdit();
        }
        break;
    case 1:
        for (int id : vectorID)
            pipesMap[id].Output;
        
        cout << "Do you want to change \n0) All\n1)set";
            
        for (int id : vectorID) {
            pipesMap[id].PipeEdit();
        }
        break;
    }
}

void filtration(map<int, Station>& stationsMap, vector<int> vectorID) {
    cout << "Edit all or set of stations?\n0) all\n 1)set\n";
    switch (choose(1)) {
    case 0:
        for (auto& item : stationsMap) {
            item.second.StationEdit();
        }
        break;
    case 1:
        for (int id : vectorID) {   
            stationsMap[id].StationEdit();
        }
        break;
    }
}