#pragma once
#include "additionalFunctions.h"
#include "Network.h"

class Menu {
public:
	Pipe addPipe();

	Station addStation();

	void output(unordered_map<int, Pipe>& pipesMap, unordered_map<int, Station>& stationsMap);

	set<int> getIDs(int maxID);
	
	std::string getStr();

	std::tuple<int, int, int> getIDsForConnect(unordered_map<int, Pipe>& pipesMap, unordered_map<int, Station>& stationsMap);
	/*
	void filtration();

	void connect();

	void disconnect();
	*/

	template<typename classType>
	void outputMap(unordered_map<int, classType>& map);
	
private:
};

template<typename classType>
inline void Menu::outputMap(unordered_map<int, classType>& map)
{
	if (map.size()) {
		for (auto& item : map) {
			std::cout << "\nID: " << item.first;
			item.second.output();
		}
	}
}