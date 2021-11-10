#include <iostream>
#include "Pipe.h"
#include "additionalFunctions.h"

#pragma once

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
}

Pipe::~Pipe()
{
}

void Pipe::PipeEdit() {
    isWorking = !isWorking;
    cout << "Pipe edited\n";
    cout << "Is pipe working? " << isWorking << "\n";
}

void Pipe::Output() {
    cout << "\nDiameter: " << diameter;
    cout << "\nLength: " << length;
    cout << "\nIs working?: " << isWorking << "\n";
}

