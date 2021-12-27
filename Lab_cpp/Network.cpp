#include "Network.h"
#include <unordered_set>
#include <iterator>

void Network::output() {
    Network::outputMap(pipesMap);
    Network::outputMap(stationsMap);
}

unordered_map<int, Node> Network::toNodesMap(const unordered_map<int, Station>& stationsMap) {
    unordered_map<int, Node> nodesMap;

    for (auto& item : stationsMap) {
        nodesMap.insert({ item.first, Node(item.second.numberOfInPipes, item.second.numberOfOutPipes, INT_MAX) });
    }

    return nodesMap;
}

unordered_map<int, Verge> Network::toVergesMap(const unordered_map<int, Pipe>& pipesMap) {
    unordered_map<int, Verge> vergeMap;
    for (auto& item : pipesMap) {
        vergeMap.insert({ item.first, Verge(item.second.startID, item.second.endID, item.second.length) });
    }

    return vergeMap;
}

void Network::save(std::string fileName) {
    ofstream file;

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

void Network::load(std::string fileName) {
    ifstream file;

    fileName += ".txt";
    file.open(fileName);
    if (file.good()) {
        
        pipesMap.clear();
        stationsMap.clear();

        Pipe::id = 0;
        Station::id = 0;

        while (!file.eof()) {

            Pipe pipe = Pipe();
            Station station = Station();
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

        for (auto& item : pipesMap) {
            if (Pipe::id < item.first)
                Pipe::id = item.first;
        }

        for (auto& item : stationsMap) {
            if (Station::id < item.first)
                Station::id = item.first;
        }

        std::cout << "Loaded\n";
    }
    else {
        std::cout << "File not found 404\n";
    }
}

void Network::connect(const std::tuple<int, int, int> pipeIdStartIDEndId) {
    if (existByID(pipesMap, std::get<0>(pipeIdStartIDEndId)) && 
        existByID(stationsMap, std::get<1>(pipeIdStartIDEndId)) &&
        existByID(stationsMap, std::get<2>(pipeIdStartIDEndId)) &&
        std::get<0>(pipeIdStartIDEndId) != -1) 
    {
        stationsMap[std::get<1>(pipeIdStartIDEndId)].numberOfOutPipes++;
        stationsMap[std::get<2>(pipeIdStartIDEndId)].numberOfInPipes++;
    
        pipesMap[std::get<0>(pipeIdStartIDEndId)].startID = std::get<1>(pipeIdStartIDEndId);
        pipesMap[std::get<0>(pipeIdStartIDEndId)].endID = std::get<2>(pipeIdStartIDEndId);
    }
}

void Network::disconnect(set<int> setOfIDs) {
    for (int pipeID : setOfIDs) {
        if (existByID(pipesMap, pipeID) && pipesMap[pipeID].startID != 0) {
            stationsMap[pipesMap[pipeID].startID].numberOfOutPipes--;
            stationsMap[pipesMap[pipeID].endID].numberOfInPipes--;
            pipesMap[pipeID].startID = 0; 
            pipesMap[pipeID].endID = 0;
            std::cout << "Pipe with id " << pipeID << " is disconnected";
        }
    }
}

void Network::topologicalSort(unordered_map<int, Pipe> pipesMap, unordered_map<int, Station> stationsMap) {

    int topologicalID = 0;
    unordered_map<int, int> pairOfIDAndTopologicalNumber;
    set<int> queue;

    for (auto& station : stationsMap) {
        if (station.second.numberOfInPipes == 0 && station.second.numberOfOutPipes == 0) {
            queue.insert(station.first);
        }
    }
    Network::deleting(queue, stationsMap);

    do {
        queue.clear();
        for (auto& station : stationsMap) {
            if (station.second.numberOfInPipes == 0) {
                queue.insert(station.first);
            }
        }

        for (int i : queue) {
            pairOfIDAndTopologicalNumber.insert({ ++topologicalID, i });

            // Change stations and pipes
            stationsMap[i].numberOfInPipes--;
            for (auto& pipe : pipesMap) {
                if (pipe.second.startID == i) {
                    stationsMap[pipe.second.endID].numberOfInPipes--;
                }
            }
        }
    } while (queue.size() != 0);

    if (pairOfIDAndTopologicalNumber.size() != stationsMap.size()) {
        std::cout << "\nTopological sort can't be done for this graph" << std::endl;
        return;
    }

    for (auto item : pairOfIDAndTopologicalNumber) {
        std::cout << "Topological ID - station ID:   " << item.first << " - " << item.second << std::endl;
    }
}

void Network::dijkstra(unordered_map<int, Node> nodesMap, unordered_map<int, Verge> vergeMap, int startID) {
    set<int> setOfChangableNodes;

    nodesMap[startID].weight = 0;

    for (auto& item : nodesMap) {
        setOfChangableNodes.insert(item.first);
    }
    
    int workID = startID;

    while (setOfChangableNodes.size() != 0) {

        // change verges
        for (auto& item : vergeMap) {
            if (item.second.startID == workID
                && nodesMap[item.second.startID].weight + item.second.length < nodesMap[item.second.endID].weight) {
                
                nodesMap[item.second.endID].weight = nodesMap[item.second.startID].weight + item.second.length;
            }
        }
        setOfChangableNodes.erase(workID);

        int min = INT_MAX;
        // find next node
        for (int i : setOfChangableNodes) {
            if (nodesMap[i].weight < min) {
                min = nodesMap[i].weight;
                workID = i;
            }
        }
    }

    for (auto& item : nodesMap) {
        std::cout << "ID: " << item.first << std::endl;
        std::cout << "Weight: " << item.second.weight << std::endl;
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

void Network::deleting(set<int> setOfIDs, unordered_map<int, Pipe>& map) {
    for (int i : setOfIDs) {
        if (map[i].startID != 0) {
            std::cout << "\nPipes is connected" << std::endl;
            return;
        }

        if (existByID(map, i)) {
            map.erase(i);
        }

        else {
            std::cout << "\nObject with ID " << i << " doesn't exist!" << std::endl;
        }
    }
}

void Network::deleting(set<int> setOfIDs, unordered_map<int, Station>& map) {
    for (int i : setOfIDs) {
        if (map.count(i) && map[i].numberOfInPipes == 0 && map[i].numberOfOutPipes == 0) {
            map.erase(i);
        }
        else {
            std::cout << "\Station with ID " << i << " can't be deleted" << std::endl;
        }
    }
}
