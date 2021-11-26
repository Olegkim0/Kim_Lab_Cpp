#pragma once
#include <string>

using namespace std;

class Station {
public:
    static int id;
    string name;
    int numberOfWorkshops;
    int numberOfWorkingWorkshops;
    int efficiency;

    Station();

    Station(string name, int numberOfWorkshops, int numberOfWorkingWorkshops, int efficiency);

    ~Station();

    void StationEdit();

    void Output();
private:
};