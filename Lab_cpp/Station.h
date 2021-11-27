#pragma once
#include <string>

using namespace std;

class Station {
public:
    string name;
    int numberOfWorkshops;
    int numberOfWorkingWorkshops;
    int efficiency;

    Station();

    Station(string name, int numberOfWorkshops, int numberOfWorkingWorkshops, int efficiency);

    ~Station();

    void Output();

    void edit();

    static void setId(int newID);

    static int getId();

private:
    static int id;
};