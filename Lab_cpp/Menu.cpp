#include "Menu.h"
#include "additionalFunctions.h"

Pipe Menu::addPipe() {
    Pipe::id++;
    Pipe p;
    std::cout << "Adding Pipe\n";
    
    std::cout << "Input name:\n";
    std::cin >> p.name;

    std::cout << "Input diameter:\n";
    p.diameter = 0;
    while (p.diameter <= 0) {
        p.diameter = inputInteger();
    }

    std::cout << "Input length:\n";
    p.length = 0;
    while (p.length <= 0) {
        p.length = inputDouble();
    }

    p.startID = 0;
    p.endID = 0;

    p.isWorking = false;

    return p;
}

Station Menu::addStation() {
    Station::id++;
    Station s;
    std::cout << "Adding Station\n";

    std::cout << "Input name:\n";
    cin >> s.name;

    std::cout << "Input number of workshops:\n";
    s.numberOfWorkshops = 0;
    while (s.numberOfWorkshops <= 0) {
        s.numberOfWorkshops = inputInteger();
    }

    std::cout << "Input number of working workshops:\n";
    s.numberOfWorkingWorkshops = -1;
    while (s.numberOfWorkingWorkshops < 0 || s.numberOfWorkingWorkshops > s.numberOfWorkshops) {
        s.numberOfWorkingWorkshops = inputInteger();
        if (s.numberOfWorkingWorkshops > s.numberOfWorkshops) {
            std::cout << "Wrong input\n";
            std::cout << "Try again:\n";
        }
    }

    std::cout << "Input Efficiency (0 < e <= 100):\n";
    s.efficiency = 0;
    while (s.efficiency <= 0 || s.efficiency > 100) {
        s.efficiency = inputInteger();
        if (s.efficiency <= 0 || s.efficiency > 100) {
            std::cout << "Wrong input\n";
            std::cout << "Try again:\n";
        };
    }

    return s;
}

void Menu::output(unordered_map<int, Pipe>& pipesMap, unordered_map<int, Station>& stationsMap) {
    outputMap(pipesMap);
    outputMap(stationsMap);
}

set<int> Menu::getIDs(int maxID)
{
    set<int> setOfIDs;
    
    if (maxID == 0) {
        std::cout << "No objects" << std::endl;
        return setOfIDs;
    }
    
    std::cout << "\nInput Id's or 0 to exit" << std::endl;
    int choice;
    do {
        choice = choose(maxID);
        if (choice != 0)
            setOfIDs.insert(choice);

    } while (choice != 0);

    return setOfIDs;
}

std::string Menu::getStr()
{
    std::cout << "\nInput name\n";

    std::string str;
    std::cin >> str;

    return str;
}

std::tuple<int, int, int> Menu::getIDsForConnect(unordered_map<int, Pipe>& pipesMap, unordered_map<int, Station>& stationsMap)
{
    if (pipesMap.size() == 0) {
        std::cout << "No pipes" << std::endl;
        return { -1, -1, -1 };
    }

    if (stationsMap.size() == 0) {
        std::cout << "No stations" << std::endl;
        return { -1, -1, -1 };
    }

    std::cout << "\nInput ID of pipe or 0 to exit:\n";

    int pipeID = inputID(stationsMap);
    if (pipeID == 0)
        return {-1, -1, -1};
    if (pipesMap[pipeID].startID != 0) {
        std::cout << "Pipe is connected" << std::endl;
        return { -1, -1, -1 };
    }

    std::cout << "\n\nInput ID of start station or 0 to exit:\n";

    int startID = inputID(stationsMap);
    if (startID == 0)
        return { -1, -1, -1 };
    if (stationsMap[startID].numberOfWorkshops <= (stationsMap[startID].numberOfInPipes + stationsMap[startID].numberOfOutPipes)) {
        std::cout << "All workshops are using";
        return { -1, -1, -1 };
    }

    std::cout << "\nInput ID of end station or 0 to exit:\n";

    int endID = inputID(stationsMap);
    if (endID == 0)
        return { -1, -1, -1 };
    if (endID == startID) {
        std::cout << "Start station and end station can't match\n";
        return { -1, -1, -1 };
    }
    if (stationsMap[endID].numberOfWorkshops <= (stationsMap[startID].numberOfInPipes + stationsMap[startID].numberOfOutPipes)) {
        std::cout << "All workshops are using";
        return { -1, -1, -1 };
    }

    return { pipeID, startID, endID };
}
