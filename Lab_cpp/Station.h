#pragma once
#include <string>
#include "additionalFunctions.h"
#include <iostream>

using namespace std;

class Station {
public:
    string name;
    int numberOfWorkshops;
    int numberOfWorkingWorkshops;
    int efficiency;
    static int id;

    Station();

    Station(string name, int numberOfWorkshops, int numberOfWorkingWorkshops, int efficiency);

    ~Station();

    void output();

    void edit();


private:
};