#pragma once
#include <map>
#include <vector>
#include "Station.h"
#include "Pipe.h"
#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <unordered_map>

using namespace std;

void printMenu();

int inputInteger();

double inputDouble();

int choose(int number);

template <typename classType>
int inputID(unordered_map<int, classType>& map)  {
    int choice = choose(classType::id);
    if (choice == 0)
        return 0;
    if (map.count(choice)) {
        return choice;
    }
    else {
        std::cout << "Not found 404\n";
    }
    return 0;
}
