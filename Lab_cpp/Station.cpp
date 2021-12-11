#pragma once
#include <iostream>
#include "Station.h"
#include "additionalFunctions.h"


using namespace std;

Station::Station() {}

Station::Station(string name, int numberOfWorkshops, int numberOfWorkingWorkshops, int efficiency) {
    this->name = name;
    this->numberOfWorkshops = numberOfWorkshops;
    this->numberOfWorkingWorkshops = numberOfWorkingWorkshops;
    this->efficiency = efficiency;
}

Station::~Station()
{
}

void Station::output() {
    std::cout << "\nStation:";
    std::cout << "\nname: " << name;
    std::cout << "\nnumber of workshops: " << numberOfWorkshops;
    std::cout << "\nnumber of working workshops: " << numberOfWorkingWorkshops;
    std::cout << "\nnumber of in pipes: " << numberOfInPipes;
    std::cout << "\nnumber of out pipes: " << numberOfOutPipes;
    std::cout << "\nEfficiency: " << efficiency << "\n";
}

void Station::edit() {
    std::cout << "\nEditing station";
    Station::output();
    std::cout << "\nInput number of working workshops:\n";
    do {
        numberOfWorkingWorkshops = choose(numberOfWorkshops);
    } while (numberOfWorkingWorkshops < 0 || numberOfWorkingWorkshops > numberOfWorkshops);
}
