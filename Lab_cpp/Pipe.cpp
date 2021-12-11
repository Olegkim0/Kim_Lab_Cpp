#include <iostream>
#include "Pipe.h"
#include "additionalFunctions.h"
#include <unordered_map>

using namespace std;
Pipe::Pipe() {}

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
    isWorking = !isWorking;
    //std::cout << "is working?\n0) No\n1) Yes\n";
    //int choice = choose(1);
    //    if (choice == 0)
    //        isWorking = false;
    //    else if (choice == 1)
    //        isWorking = true;
    //std::cout << "Pipe edited\n";
    //std::cout << "Is pipe working? " << isWorking << "\n";
}

void Pipe::output() {
    std::cout << "\nPipe:";
    std::cout << "\nName: " << name;
    std::cout << "\nDiameter: " << diameter;
    std::cout << "\nLength: " << length;
    if (startID != 0) {
        std::cout << "\nStart is station with ID: " << startID;
        std::cout << "\nEnd is station with ID: " << endID;
    }
    std::cout << "\nIs working?: " << isWorking << "\n";
}
