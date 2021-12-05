#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include "Station.h"
#include "Pipe.h"
#include <set>

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
    do {
        result = inputInteger();
        if (result < 0 || result > number)
            cout << "Out of range\n";
    }
    while (result < 0 || result > number); 
    
    return result;
}

void Save(const map<int, Pipe>& pipesMap, const map<int, Station>& stationsMap) {
    ofstream file;

    cout << "Input File name\n";
    string fileName;
    cin >> fileName;
    fileName += ".txt";

    file.open(fileName);
    if (file.good()) {
        if (pipesMap.size() != 0) {
            for (const auto& item : pipesMap) {
                file << "Pipe:\n";
                file << item.first << "\n";
                file << item.second.name << "\n";
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
                file << item.second.numberOfWorkshops << "\n";
                file << item.second.numberOfWorkingWorkshops << "\n";
                file << item.second.efficiency << "\n";
            }
        }
        file.close();
        cout << "Saved\n";
    }
}

void Load(map<int, Pipe>& pipesMap, map<int, Station>& stationsMap) {

    ifstream file;

    cout << "Input File name:\n";
    string fileName;
    cin >> fileName;
    fileName += ".txt";
    file.open(fileName);
    if (file.good()) {

        pipesMap.clear();
        stationsMap.clear();

        Pipe::id = 0;
        Station::id = 0;

        while (!file.eof()) {
            string type;
            file >> type;
            if (type == "Pipe:") {

                int id;
                file >> id;

                string name;
                file >> name;

                int diameter;
                file >> diameter;

                int length;
                file >> length;

                bool isWorking;
                file >> isWorking;

                pipesMap.insert(pair<int, Pipe>(id, Pipe(name, diameter, length, isWorking)));
                // pipesMap[id] = Pipe(name, diameter, length, isWorking);  Why is it cause 2 constructor?
            }
            
            if (type == "Station:") {

                int id;
                file >> id;

                string name;
                file >> name;

                int numberOfWorkshops;
                file >> numberOfWorkshops;

                int numberOfWorkingWorkshops;
                file >> numberOfWorkingWorkshops;

                int efficiency;
                file >> efficiency;

                stationsMap.insert(pair<int, Station>(id, Station(name, numberOfWorkshops, numberOfWorkingWorkshops, efficiency)));
            }
        }
        cout << "Loaded\n";
        
        for (auto& item : pipesMap) {
            if (Pipe::id < item.first)
                Pipe::id = item.first;
        }
        
        for (auto& item : stationsMap) {
            if (Station::id < item.first)
                Station::id = item.first;
        }
    }
    else {
        cout << "File not found 404\n";
    }
}

vector<int> search(const map<int, Pipe>& pipesMap) {
    vector<int> vectorID;

    if (pipesMap.size() == 0)
        return vectorID;

    cout << "\nSearch by:\n1) name\n2) is working?\n0) Exit\n";

    string name;
    bool isWorking;

    switch (choose(2))
    {
    case 0:
        return vectorID;
    case 1:
        cout << "\nInput name:\n";
        cin >> name;
        for (auto& item : pipesMap) {
            if (item.second.name == name) {
                vectorID.push_back(item.first);
            }
        }
        break;
    case 2:
        cout << "\nIs working?\n0) No\n1) Yes\n";
        isWorking = choose(1);
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
    cout << "\n";
    return vectorID;
}

vector<int> search(const map<int, Station>& stationsMap) {
    vector<int> vectorID;

    if (stationsMap.size() == 0)
        return vectorID;

    int choice;
    cout << "\nSearch by:\n1) name\n2) percent of non working stations?\n0) Exit\n";
    
    choice = choose(2);

    string name;
    double percentOfWorkshops;
    switch (choice)
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
        cout << "\nInput percent of non working stations or 0 to exit\n";
        do
        {
            percentOfWorkshops = inputDouble();
        } while (percentOfWorkshops <= 0 || percentOfWorkshops > 100);
        if (percentOfWorkshops == 0)
            return vectorID;
        
        cout << "\n1) less\n2) more\n0) exit\n";
        choice = choose(2);

        if (choice == 1)
            for (auto& item : stationsMap) {
                cout << (1.0 * item.second.numberOfWorkingWorkshops / (1.0 * item.second.numberOfWorkshops)) * 100.0;
                if ((1.0 * item.second.numberOfWorkingWorkshops / (1.0 * item.second.numberOfWorkshops)) * 100.0 < percentOfWorkshops)
                    vectorID.push_back(item.first);
            }
                
        else if (choice == 2)
            for (auto& item : stationsMap)
                if ((1.0 * item.second.numberOfWorkingWorkshops / (1.0 * item.second.numberOfWorkshops)) * 100.0 >= percentOfWorkshops)
                    vectorID.push_back(item.first);
        break;
    default:
        break; 
    }
    cout << "ID: ";
    for (int i : vectorID)
        cout << i << "  ";
    cout << "\n";
    return vectorID;
}

void filtration(map<int, Pipe>& pipesMap, vector<int> vectorID) {
    cout << "\nEdit all or set of stations?\n0) all\n1) set\n";

    switch (choose(1)) {
    case 0:

        //for (int id : vectorID) {
        //    cout << "Id: " << id;
        //    pipesMap[id].Output();
        //    pipesMap[id].edit();
        //}
        
        for (int id : vectorID) {
            cout << "\nId: " << id;
            pipesMap[id].Output();
            pipesMap[id].isWorking = !pipesMap[id].isWorking;
        }

        break;
    case 1:

        for (int id : vectorID) {
            cout << "\nId: " << id;
            pipesMap[id].Output();
        }

        cout << "\nInput id(s), which you want to change or 0 to exit\n";

        set<int> setOfChangeable;
        int choice;

        do {
            choice = choose(pipesMap.size());
            if (choice == 0)
                break;
            if (find(vectorID.begin(), vectorID.end(), choice) != vectorID.end())
                setOfChangeable.insert(choice);
            else
                cout << "Out of set\n";
        } while (choice != 0);

        for (int id : setOfChangeable) {
            pipesMap[id].isWorking = !pipesMap[id].isWorking;  
        }
        break;
    }
}

void filtration(map<int, Station>& stationsMap, vector<int> vectorID) {
    if (vectorID.size() == 0)
        return;

    cout << "Edit all or set of stations?\n0) all\n1) set\n";
    switch (choose(1)) {
    case 0:
        for (int id : vectorID) {
            cout << "Id: " << id;
            stationsMap[id].Output();
            stationsMap[id].edit();
        }
        break;

    case 1:

        for (int id : vectorID) {
            cout << "\nId: " << id;
            stationsMap[id].Output();
        }

        cout << "\nInput id(s), which you want to change or 0 to exit\n";

        set<int> setOfChangeable;
        int choice;

        do {
            choice = choose(stationsMap.size());
            if (choice == 0)
                break;
            if (find(vectorID.begin(), vectorID.end(), choice) != vectorID.end())
                setOfChangeable.insert(choice);
            else
                cout << "Out of set\n";
        } while (choice != 0);

        for (int id : setOfChangeable) {
            stationsMap[id].Output();
            stationsMap[id].edit();
        }
        break;
    }
}