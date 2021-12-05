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
    id++;
    this->name = name;
    this->diameter = diameter;
    this->length = length;
    this->isWorking = isWorking;
}

Pipe::~Pipe()
{
}

void Pipe::edit() {
    cout << "is working?\n0) No\n1) Yes\n";
    int choice = choose(1);
        if (choice == 0)
            isWorking = false;
        else if (choice == 1)
            isWorking = true;
    cout << "Pipe edited\n";
    cout << "Is pipe working? " << isWorking << "\n";
}

void Pipe::Output() {
    cout << "\nName: " << name;
    cout << "\nDiameter: " << diameter;
    cout << "\nLength: " << length;
    cout << "\nIs working?: " << isWorking << "\n";
}

