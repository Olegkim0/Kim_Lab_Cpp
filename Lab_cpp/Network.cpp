#include "Network.h"

void Network::output() {
    Network::outputMap(pipesMap);
    Network::outputMap(stationsMap);
}

void Network::save() {
    ofstream file;

    std::cout << "Input File name\n";
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
                file << item.second.startID << "\n";
                file << item.second.endID << "\n";
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
                file << item.second.numberOfInPipes << "\n";
                file << item.second.numberOfOutPipes << "\n";
                file << item.second.efficiency << "\n";
            }
        }
        std::cout << "Saved\n";
    }
    file.close();

}

void Network::load() {
    ifstream file;

    std::cout << "Input File name:\n";
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

            Pipe pipe = Pipe("-1", -1, -1, 0);
            Station station = Station("-1", -1, -1, -1);
            string type;
            file >> type;
            if (type == "Pipe:") {

                int id;
                file >> id;
                file >> pipe.name;
                file >> pipe.diameter;
                file >> pipe.length;
                file >> pipe.startID;
                file >> pipe.endID;
                file >> pipe.isWorking;

                pipesMap.insert(pair<int, Pipe>(id, pipe));
                // pipesMap[id] = Pipe(name, diameter, length, isWorking);  Why is it cause 2 constructor?
            }

            if (type == "Station:") {

                int id;
                file >> id;
                file >> station.name;
                file >> station.numberOfWorkshops;
                file >> station.numberOfWorkingWorkshops;
                file >> station.numberOfInPipes;
                file >> station.numberOfOutPipes;
                file >> station.efficiency;
                stationsMap.insert(pair<int, Station>(id, station));
            }
        }
        std::cout << "Loaded\n";

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
        std::cout << "File not found 404\n";
    }
}

void Network::connect() {
    Network::outputMap(pipesMap);
    std::cout << "\nInput ID of pipe or 0 to exit:\n";

    int pipeID = inputID(pipesMap);
    if (pipeID == 0)
        return;

    Network::outputMap(stationsMap);
    std::cout << "\n\nInput ID of start station or 0 to exit:\n";

    int startID = inputID(stationsMap);
    if (startID == 0)
        return;
    if (stationsMap[startID].numberOfWorkshops <= (stationsMap[startID].numberOfInPipes + stationsMap[startID].numberOfOutPipes)) {
        std::cout << "All workshops are using";
        return;
    }

    std::cout << "\nInput ID of end station or 0 to exit:\n";

    int endID = inputID(stationsMap);
    if (endID == 0)
        return;
    if (stationsMap[endID].numberOfWorkshops <= (stationsMap[startID].numberOfInPipes + stationsMap[startID].numberOfOutPipes)) {
        std::cout << "All workshops are using";
        return;
    }

    stationsMap[startID].numberOfOutPipes++;
    stationsMap[endID].numberOfInPipes++;


    pipesMap[pipeID].startID = startID;
    pipesMap[pipeID].endID = endID;
}

void Network::disconnect() {
    int pipeID = inputID(pipesMap);
    if (pipesMap[pipeID].startID != 0) {
        stationsMap[pipesMap[pipeID].startID].numberOfInPipes--;
        stationsMap[pipesMap[pipeID].endID].numberOfOutPipes--;
        pipesMap[pipeID].startID = 0;
        pipesMap[pipeID].endID = 0;
        std::cout << "Pipe is disconnected";
    }
}
/*
void Network::topologicalSort(unordered_map<int, Pipe> pipesMap, unordered_map<int, Station> stationsMap) {
    vector<int> queue;
    unordered_map<int, int> pairIDAndTopologicNumber;
    int topologicNumber = 0;
    
    for (auto& item : stationsMap)
        if (item.second.numberOfInPipes == 0) {
            queue.push_back(item.first);
            item.second.numberOfInPipes--;
        }

    for (int i : queue) {
        std::cout << "zxc: " << i << endl;
    }

    while (queue.size() != 0) {
        
        for (int i : queue) {
            pairIDAndTopologicNumber[i] = ++topologicNumber;
        }

        for (int i : queue) {
            for (auto item : pipesMap) {
                if (item.second.startID == i)
                    item.second.startID = 0;
            }
        }
        // queue keep IDs of stations
        


        queue.clear();

        for (auto& item : stationsMap)
            if (item.second.numberOfInPipes == 0)
                queue.push_back(item.first);
    } 

    std::cout << queue.size();


    for (auto& item : pairIDAndTopologicNumber) {
        std::cout << "item first: " << item.first << endl;
        std::cout << "item second: " << item.second << endl;
    }
}
*/

void Network::topologicalSort(unordered_map<int, Pipe> pipesMap, unordered_map<int, Station> stationsMap) {
    int topologicalID = 0;
    unordered_map<int, int> pairOfIDAndTopologicalNumber;
    while (pairOfIDAndTopologicalNumber.size() != stationsMap.size()) {
        for (auto& station : stationsMap) {
            if (station.second.numberOfInPipes == 0) {
                pairOfIDAndTopologicalNumber.insert({ station.first, ++topologicalID });

                // Change stations and pipes
                stationsMap[station.first].numberOfInPipes--;
                for (auto& pipe : pipesMap) {
                    if (pipe.second.startID == station.first) {
                        stationsMap[pipe.second.endID].numberOfInPipes--;
                    }
                }
            }
        }
    }
    for (auto item : pairOfIDAndTopologicalNumber) {
        std::cout << "ID: " << item.first << std::endl;
        std::cout << "Topological ID: " << item.second << std::endl;
    }
}

vector<int> Network::search(unordered_map<int, Pipe>& map) {
    vector<int> vectorID;
    if (map.size() == 0) {
        std::cout << "Map is empty";
        return vectorID;
    }

    std::cout << "\nSearch by:\n1) name\n2) is working?\n0) Exit\n";

    string name;
    bool isWorking;
    switch (choose(2))
    {
    case 0:
        return vectorID;
    case 1:
        std::cout << "\nInput name:\n";
        cin >> name;
        for (auto& item : pipesMap) {
            if (item.second.name == name) {
                vectorID.push_back(item.first);
            }
        }
        break;
    case 2:
        std::cout << "\nIs working?\n0) No\n1) Yes\n";
        isWorking = choose(1);
        for (auto& item : pipesMap)
            if (item.second.isWorking == isWorking)
                vectorID.push_back(item.first);
        break;
    default:
        break;
    }
    std::cout << "ID: ";
    for (int i : vectorID)
        std::cout << i << "  ";
    std::cout << "\n";

    return vectorID;
}

vector<int> Network::search(unordered_map<int, Station>& map) {
    vector<int> vectorID;
    if (map.size() == 0) {
        std::cout << "Map is empty";
        return vectorID;
    }

    std::cout << "\nSearch by:\n1) name\n2) percent of non working stations?\n0) Exit\n";

    string name;
    double percentOfWorkshops;
    switch (choose(2))
    {
    case 0:
        return vectorID;
    case 1:
        std::cout << "\nInput name:\n";
        cin >> name;
        for (auto& item : stationsMap) {
            if (item.second.name == name) {
                vectorID.push_back(item.first);
            }
        }
        break;
    case 2:
        std::cout << "\nInput percent of non working stations or 0 to exit\n";
        do
        {
            percentOfWorkshops = inputDouble();
        } while (percentOfWorkshops <= 0 || percentOfWorkshops > 100);
        if (percentOfWorkshops == 0)
            return vectorID;

        std::cout << "\n1) less\n2) more\n0) exit\n";
        switch (choose(2)) {
        case 0:
            return vectorID;
        case 1:
            for (auto& item : stationsMap) {
                std::cout << (1.0 * item.second.numberOfWorkingWorkshops / (1.0 * item.second.numberOfWorkshops)) * 100.0;
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
    std::cout << "ID: ";
    for (int i : vectorID)
        std::cout << i << "  ";
    std::cout << "\n";

    return vectorID;
}

void Network::deleting(unordered_map<int, Pipe>& map) {
    Network::outputMap(map);
	std::cout << "\nInput ID(s) or 0 to exit\n";
	
	int choice;
	do {
		choice = choose(Pipe::id);
		if (choice == 0)
			break;
		if (map.count(choice))
            if (map[choice].startID != 0) {
                map.erase(choice);
            }
            else {
                std::cout << "Pipes is connected\n";
            }
		else
			std::cout << "Out of map\n";
	} while (choice != 0);
}

void Network::deleting(unordered_map<int, Station>& map) {
    Network::outputMap(map);
    std::cout << "\nInput ID(s) or 0 to exit\n";

    int choice;
    do {
        choice = choose(Pipe::id);
        if (choice == 0)
            break;
        if (map.count(choice)) {
            map.erase(choice);
        }
        else
            std::cout << "Out of map\n";
    } while (choice != 0);
}