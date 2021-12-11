#pragma once
#include <iostream>
#include "Station.h"
#include "additionalFunctions.h"


using namespace std;

Station::Station()
{

    id++;

    std::cout << "Adding Station\n";

    std::cout << "Input name:\n";
    cin >> name;

    std::cout << "Input number of workshops:\n";
    numberOfWorkshops = 0;
    while (numberOfWorkshops <= 0) {
        numberOfWorkshops = inputInteger();
    }

    std::cout << "Input number of working workshops:\n";
    numberOfWorkingWorkshops = -1;
    while (numberOfWorkingWorkshops < 0 || numberOfWorkingWorkshops > numberOfWorkshops) {
        numberOfWorkingWorkshops = inputInteger();
        if (numberOfWorkingWorkshops > numberOfWorkshops) {
            std::cout << "Wrong input\n";
            std::cout << "Try again:\n";
        }
    }

    std::cout << "Input Efficiency (0 < e <= 100):\n";
    efficiency = 0;
    while (efficiency <= 0 || efficiency > 100) {
        efficiency = inputInteger();
        if (efficiency <= 0 || efficiency > 100) {
            std::cout << "Wrong input\n";
            std::cout << "Try again:\n";
        };
    }
}

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
