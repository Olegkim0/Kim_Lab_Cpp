#pragma once
#include <unordered_map>
#include <vector>
#include "Station.h"
#include "Pipe.h"
#include <string>
#include <iostream>

using namespace std;

void printMenu();

int inputInteger();

double inputDouble();

int choose(int number);

//void Save(const unordered_map<int, Pipe>& pipesMap, const unordered_map<int, Station>& stationsMap);
//
//void Load(unordered_map<int, Pipe>& pipesMap, unordered_map<int, Station>& stationsMap);
//
//vector<int> search(const unordered_map<int, Pipe>& pipesMap);
//
//vector<int> search(const unordered_map<int, Station>& stationsMap);
//	
//void filtration(unordered_map<int, Pipe>& pipesMap, vector<int> vectorID);
//
//void filtration(unordered_map<int, Station>& stationsMap, vector<int> vectorID);