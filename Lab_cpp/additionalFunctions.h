#pragma once
#include <map>
#include <vector>
#include "Station.h"
#include "Pipe.h"

using namespace std;

void printMenu();

int inputInteger();

double inputDouble();

int choose(int number);

void Save(const map<int, Pipe>& pipesMap, const map<int, Station>& stationsMap);

void Load(map<int, Pipe>& pipesMap, map<int, Station>& stationsMap);

vector<int> search(const map<int, Pipe>& pipesMap);

vector<int> search(const map<int, Station>& stationsMap);

void filtration(map<int, Pipe>& pipesMap, vector<int> vectorID);

void filtration(map<int, Station>& stationsMap, vector<int> vectorID);