#pragma once
#include <unordered_map>
#include "Pipe.h"
#include "Station.h"
#include <iostream>
#include <fstream>

using namespace std;

class Network {
public:
	unordered_map<int, Pipe> pipesMap;
	unordered_map<int, Station> stationsMap;
	
	void output();

	void save();

	void load();

private:
};