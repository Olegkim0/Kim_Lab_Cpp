#pragma once
#include "Pipe.h"
#include "Station.h"
#include <unordered_map>
#include "additionalFunctions.h"
#include <iostream>

using namespace std;

class Network {
public:
	unordered_map<int, Pipe> pipesMap;
	unordered_map<int, Station> stationsMap;

	void output();

	//void load();

	//void save();

private:

};
