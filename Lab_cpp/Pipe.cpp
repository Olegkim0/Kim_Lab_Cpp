#pragma once
#include <iostream>
#include "Pipe.h"
#include "additionalFunctions.h"


using namespace std;

Pipe::Pipe()
{
    id++;

    cout << "Adding Pipe\n";

    cout << "Input name:\n";

    cin >> name;

    cout << "Input diameter:\n";
    diameter = 0;
    while (diameter <= 0) {
        diameter = inputInteger();
    }

    cout << "Input length:\n";
    length = 0;
    while (length <= 0) {
        length = inputDouble();
    }

    isWorking = true;
}

Pipe::Pipe(string name, int diameter, double length, bool isWorking)
{
    this->name = name;
    this->diameter = diameter;
    this->length = length;
    this->isWorking = isWorking;
}

Pipe::~Pipe()
{
}

void Pipe::PipeEdit() {
    cout << "is work?\n0) Yes\n1) No\n";
        if (choose(1) == 0)
            isWorking = true;
        else
            isWorking = false;
    cout << "Pipe edited\n";
    cout << "Is pipe working? " << isWorking << "\n";
}

void Pipe::Output() {
    cout << "\nDiameter: " << diameter;
    cout << "\nLength: " << length;
    cout << "\nIs working?: " << isWorking << "\n";
}

