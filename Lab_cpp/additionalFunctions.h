#pragma once
#include <map>
#include <vector>
#include "Station.h"
#include "Pipe.h"

using namespace std;

int inputInteger();

double inputDouble();

int choose(int number);

void Save(const std::map<int, Pipe>&pipesMap, const std::map<int, Station>& stationsMap);

void printMenu();

void Load(std::map<int, Pipe>& pipesMap, std::map<int, Station>& stationsMap);

vector<int> search(const map<int, Pipe>& pipesMap);

vector<int> search(const map<int, Station>& stationsMap);

void filtration(map<int, Pipe>& pipesMap, vector<int> vectorID);

void filtration(map<int, Station>& stationsMap, vector<int> vectorID);