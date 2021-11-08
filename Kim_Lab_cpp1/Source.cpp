#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

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

int input_integer() {
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

double input_double() {
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

struct Pipe {
    int id = 0;
    int diameter;
    double length;
    bool isWorking = true;
};

Pipe AddPipe(int i)
{
    cout << "Adding Pipe\n";
    Pipe p;

    cout << "Input diameter:\n";
    p.diameter = 0;
    while (p.diameter <= 0) {    
        p.diameter = input_integer();
    }

    cout << "Input length:\n";
    p.length = 0;
    while (p.length <= 0) {
        p.length = input_double();
    }
    return p;
}

void PipeEdit(Pipe& p) {
    /*if (pipesStation.size() != 0) {
        cout << "Input Id, if dsafdsa input -1";
        int id = -2;
        while (id != -1) {
            id = input_integer();

        }

    }*/
    //if (PiExists(p)) {
        p.isWorking = !p.isWorking;
        cout << "Pipe edited\n";
        cout << "Is pipe working? " << p.isWorking << "\n";
    //}
    //else {
        //cout << "\nNo pipes\n";
    //}
}

struct Station {
    int id = 0;
    string name;
    int number_of_workshops;
    int number_of_working_workshops;
    int Efficiency;
};

Station AddStation(int id) {
    cout << "Adding Station\n";
    Station s;

    cout << "Input name:\n";
    cin >> s.name;

    cout << "Input number of workshops:\n";
    s.number_of_workshops = 0;
    while (s.number_of_workshops <= 0) {
        s.number_of_workshops = input_integer();
    }

    cout << "Input number of working workshops:\n";
    s.number_of_working_workshops = -1;
    while (s.number_of_working_workshops < 0 || s.number_of_working_workshops > s.number_of_workshops) {
        s.number_of_working_workshops = input_integer();
        if (s.number_of_working_workshops > s.number_of_workshops) {
            cout << "Wrong input\n";
            cout << "Try again:\n";
        }
    }

    cout << "Input Efficiency (0 < e <= 100):\n";
    s.Efficiency = 0;
    while (s.Efficiency <= 0 || s.Efficiency > 100) {
        s.Efficiency = input_integer();
    }
    return s;
}

void StationEdit(Station& s) {
    // if (array_of_stations != 0){}
    //if (StExists(s)) {
        cout << "Editing station\n";
        cout << "Input number of working workshops:\n";
        s.number_of_working_workshops = -1;
        while (s.number_of_working_workshops < 0 || s.number_of_working_workshops > s.number_of_workshops) {
            s.number_of_working_workshops = input_integer();
            if (s.number_of_working_workshops > s.number_of_workshops) {
                cout << "Wrong input\n";
                cout << "Try again:\n";
            }
        }
    //}
    //else {
        //cout << "\nNo stations\n";
    //}
}

void Output(const map<int, Pipe>& pipesMap, const map<int, Station>& stationsMap)
{

    cout << "\nOutput\n";
    if (pipesMap.size() != 0) {
        for (auto& item : pipesMap) {
            cout << "\nOutput Pipe(s)";
            cout << "\nId: " << item.first;
            cout << "\nDiameter: " << item.second.diameter;
            cout << "\nLength: " << item.second.length << "\n";
        }
    }

    if (stationsMap.size() != 0) {
        for (auto& item : stationsMap) {
            cout << "\nOutput station(s)";
            cout << "\nId: " << item.first;
            cout << "\nname: " << item.second.name;
            cout << "\nnumber of workshops: " << item.second.number_of_workshops;
            cout << "\nnumber of working workshops: " << item.second.number_of_working_workshops;
            cout << "\nEfficiency: " << item.second.Efficiency << "\n";
        }
    }
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

int main()
{
    int pipeID = 0;
    int stationID = 0;

    map<int, Pipe> mapOfPipes;
    map<int, Station> mapOfStation;

    int tempID;
    std::map<int, Pipe>::iterator pipesIterator;  //  https://www.cplusplus.com/reference/map/map/find/
    std::map<int, Station>::iterator stationsIterator;

    while (1) {
        printMenu();
        switch (input_integer()) {
        case 0:
            cout << "\nExit\n";
            return 0;
        case 1:
            mapOfPipes.insert(pair<int, Pipe>(mapOfPipes.size(), AddPipe(mapOfPipes.size())));
            pipeID++;
            break;
        case 2:
            mapOfStation.insert(pair<int, Station>(mapOfStation.size(), AddStation(mapOfStation.size())));
            stationID++;
            break;
        case 3:
            cout << "\n\n\n" << mapOfPipes.size() << "\n\n\n";
            Output(mapOfPipes, mapOfStation);
            break;
        case 4:
            cout << "\ninput id\n";
            tempID = input_integer();
            while (tempID > pipeID)
            {
                cout << "\nWrong input\n";
                tempID = input_integer();
            }
            pipesIterator = mapOfPipes.find(tempID);
            
            if (pipesIterator != mapOfPipes.end())
                PipeEdit(mapOfPipes[tempID]);
            else
            {
                cout << "\nWrong ID\n";
            }
            break;
        case 5:
            cout << "\ninput id\n";
            tempID = input_integer();
            while (tempID > stationID)
            {
                cout << "\nWrong input\n";
                tempID = input_integer();
            }
            stationsIterator = mapOfStation.find(tempID);

            if (stationsIterator != mapOfStation.end())
                StationEdit(mapOfStation[tempID]);
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
        default:
            break;
        }
    }
    return 0;
}