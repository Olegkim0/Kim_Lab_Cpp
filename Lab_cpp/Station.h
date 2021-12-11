#pragma once
#include <string>

using namespace std;

class Station {
public:
    string name;
    int numberOfWorkshops;
    int numberOfWorkingWorkshops;
    int efficiency;
    int numberOfInPipes = 0;
    int numberOfOutPipes = 0;
    static int id;

    Station();

    Station(string name, int numberOfWorkshops, int numberOfWorkingWorkshops, int efficiency);

    ~Station();

    void output();

    void edit();

private:
};