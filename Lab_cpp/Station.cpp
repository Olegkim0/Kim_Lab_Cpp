#include <iostream>
#include "Station.h"
#include "additionalFunctions.h"

#pragma once

using namespace std;

Station::Station()
{

    id++;

    cout << "Adding Station\n";

    cout << "Input name:\n";
    cin >> name;

    cout << "Input number of workshops:\n";
    number_of_workshops = 0;
    while (number_of_workshops <= 0) {
        number_of_workshops = inputInteger();
    }

    cout << "Input number of working workshops:\n";
    number_of_working_workshops = -1;
    while (number_of_working_workshops < 0 || number_of_working_workshops > number_of_workshops) {
        number_of_working_workshops = inputInteger();
        if (number_of_working_workshops > number_of_workshops) {
            cout << "Wrong input\n";
            cout << "Try again:\n";
        }
    }

    cout << "Input Efficiency (0 < e <= 100):\n";
    Efficiency = 0;
    while (Efficiency <= 0 || Efficiency > 100) {
        Efficiency = inputInteger();
    }
}

Station::~Station()
{
}

void Station::StationEdit() {
    cout << "Editing station\n";
    cout << "Input number of working workshops:\n";
    number_of_working_workshops = -1;
    while (number_of_working_workshops < 0 || number_of_working_workshops > number_of_workshops) {
        number_of_working_workshops = inputInteger();
        if (number_of_working_workshops > number_of_workshops) {
            cout << "Wrong input\n";
            cout << "Try again:\n";
        }
    }
}

void Station::Output() {
    cout << "\nname: " << name;
    cout << "\nnumber of workshops: " << number_of_workshops;
    cout << "\nnumber of working workshops: " << number_of_working_workshops;
    cout << "\nEfficiency: " << Efficiency << "\n";
}