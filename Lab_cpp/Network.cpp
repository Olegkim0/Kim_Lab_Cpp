#include "Network.h"

void Network::output() {
    Network::outputMap(pipesMap);
    Network::outputMap(stationsMap);
}

void Network::save() {
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
        cout << "Saved\n";
    }
    file.close();

}

void Network::load() {
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

/*vector<int> Network::search(unordered_map<int, Pipe>& map) {
    vector<int> vectorID;
    if (map.size() == 0) {
        cout << "Map is empty";
        return vectorID;
    }

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
}
*/

/*vector<int> Network::search(unordered_map<int, Station>& map) {
    vector<int> vectorID;
    if (map.size() == 0) {
        cout << "Map is empty";
        return vectorID;
    }

    cout << "\nSearch by:\n1) name\n2) percent of non working stations?\n0) Exit\n";

    string name;
    double percentOfWorkshops;
    switch (choose(2))
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
        switch (choose(2)) {
        case 0:
            return vectorID;
        case 1:
            for (auto& item : stationsMap) {
                cout << (1.0 * item.second.numberOfWorkingWorkshops / (1.0 * item.second.numberOfWorkshops)) * 100.0;
                if ((1.0 * item.second.numberOfWorkingWorkshops / (1.0 * item.second.numberOfWorkshops)) * 100.0 < percentOfWorkshops)
                    vectorID.push_back(item.first);
            }
            break;
        case 2:
            for (auto& item : stationsMap)
                if ((1.0 * item.second.numberOfWorkingWorkshops / (1.0 * item.second.numberOfWorkshops)) * 100.0 >= percentOfWorkshops)
                    vectorID.push_back(item.first);
            break;
        }

    default:
        break;
    }
    cout << "ID: ";
    for (int i : vectorID)
        cout << i << "  ";
    cout << "\n";
}
*/