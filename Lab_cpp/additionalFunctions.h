#pragma once
#include <map>
#include "Station.h"
#include "Pipe.h"

int inputInteger();

double inputDouble();

void Save(const std::map<int, Pipe>&pipesMap, const std::map<int, Station>& stationsMap);

void printMenu();

void Load(std::map<int, Pipe>& pipesMap, std::map<int, Station>& stationsMap);

void filter(std::map<int, Pipe>);

void filter(std::map<int, Station>);