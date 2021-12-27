#pragma once
#include <unordered_map>
#include "Pipe.h"
#include "Station.h"
#include <iostream>
#include <fstream>
#include "additionalFunctions.h"
#include <typeinfo>
#include "Node.h"
#include "Verge.h"


using namespace std;

class Network {
public:
	unordered_map<int, Pipe> pipesMap;
	unordered_map<int, Station> stationsMap;
	
	template <typename classType>
	void outputMap(unordered_map<int, classType>& map);
	
	void output();
	
	unordered_map<int, Node> toNodesMap(const unordered_map<int, Station>& stationsMap);

	unordered_map<int, Verge> toVergesMap(const unordered_map<int, Pipe>& pipesMap);
	
	void save(std::string fileName);

	void load(std::string fileName);

	void connect(const std::tuple<int, int, int> pipeIdStartIDEndId);

	void disconnect(set<int> setOfIDs);

	void topologicalSort(unordered_map<int, Pipe> pipesMap, unordered_map<int, Station> stationsMap);

	void dijkstra(unordered_map<int, Node> nodeMap, unordered_map<int, Verge> vergeMap, int startID);

	vector<int> search(unordered_map<int, Pipe>& map);

	vector<int> search(unordered_map<int, Station>& map);

	void deleting(set<int> setOfIDs, unordered_map<int, Pipe>& map);

	void deleting(set<int> setOfIDs, unordered_map<int, Station>& map);

	template <typename classType>
	bool existByID(const unordered_map<int, classType>& map, const int ID);

	//template <typename classType>
	//void deleting(unordered_map<int, classType>& map);

	template <typename classType>
	void editing(set<int> setOfIDs, unordered_map<int, classType>& map);

	template <typename classType>
	void editObjectById(unordered_map<int, classType>& map);

	//template <typename classType>
	//	vector<int> search(unordered_map<int, classType>& map);

	template <typename classType>
	void filtration(unordered_map<int, classType>& map, vector<int> vectorID);
private:
};

template<typename classType>
inline void Network::outputMap(unordered_map<int, classType>& map)
{
	if (map.size()) {
		for (auto& item : map) {
			std::cout << "\nID: " << item.first;
			item.second.output();
		}
	}
}

//template<typename classType>
//inline void Network::deleting(unordered_map<int, classType>& map) {
//	Network::outputMap(map);
//	std::cout << "\nInput ID(s) or 0 to exit\n";
//	
//	int choice;
//	do {
//		choice = choose(classType::id);
//		if (choice == 0)
//			break;
//		if (map.count(choice))
//			map.erase(choice);
//		else
//			std::cout << "Out of map\n";
//	} while (choice != 0);
//}

template<typename classType>
inline bool Network::existByID(const unordered_map<int, classType>& map, const int ID)
{
	return map.count(ID);
}

template<typename classType>
inline void Network::editing(set<int> setOfIDs, unordered_map<int, classType>& map) {
	for (int i : setOfIDs) {
		map[i].edit();
	}
}

template<typename classType>
inline void Network::editObjectById(unordered_map<int, classType>& map) {
	Network::outputMap(map);
	if (map.size()) {
		std::cout << "\ninput id\n";
		int tempID = choose(classType::id);
		if (map.count(tempID)) {
			map[tempID].edit();
		}
		else {
			std::cout << "\nWrong id\n";
		}
	}
}

/*template<typename classType>
inline vector<int> Network::search(unordered_map<int, classType>& map)
{
	vector<int> vectorID;
	if (map.size() == 0) {
		std::cout << "Map is empty";
		return vectorID;
	}

	if (typeid(classType) == typeid(Pipe)) {
		std::cout << "\nSearch by:\n1) name\n2) is working?\n0) Exit\n";

		string name;
		bool isWorking;
		switch (choose(2))
		{
		case 0:
			return vectorID;
		case 1:
			std::cout << "\nInput name:\n";
			cin >> name;
			for (auto& item : pipesMap) {
				if (item.second.name == name) {
					vectorID.push_back(item.first);
				}
			}
			break;
		case 2:
			std::cout << "\nIs working?\n0) No\n1) Yes\n";
			isWorking = choose(1);
			for (auto& item : pipesMap)
				if (item.second.isWorking == isWorking)
					vectorID.push_back(item.first);
			break;
		default:
			break;
		}
		std::cout << "\nID: ";
		for (int i : vectorID)
			std::cout << i << "  ";
		std::cout << "\n";
	}
	else {
		std::cout << "\nSearch by:\n1) name\n2) percent of non working stations?\n0) Exit\n";

		string name;
		double percentOfWorkshops;
		switch (choose(2))
		{
		case 0:
			return vectorID;
		case 1:
			std::cout << "\nInput name:\n";
			cin >> name;
			for (auto& item : stationsMap) {
				if (item.second.name == name) {
					vectorID.push_back(item.first);
				}
			}
			break;
		case 2:
			std::cout << "\nInput percent of non working stations or 0 to exit\n";
			do
			{
				percentOfWorkshops = inputDouble();
			} while (percentOfWorkshops <= 0 || percentOfWorkshops > 100);
			if (percentOfWorkshops == 0)
				return vectorID;

			std::cout << "\n1) less\n2) more\n0) exit\n";
			switch (choose(2)) {
			case 0:
				return vectorID;
			case 1:
				for (auto& item : stationsMap) {
					std::cout << (1.0 * item.second.numberOfWorkingWorkshops / (1.0 * item.second.numberOfWorkshops)) * 100.0;
					if ((1.0 * item.second.numberOfWorkingWorkshops / (1.0 * item.second.numberOfWorkshops)) * 100.0 < percentOfWorkshops)
						vectorID.push_back(item.first);
				}
				break;
			case 2:
				for (auto& item : stationsMap)
					if ((1.0 * item.second.numberOfWorkingWorkshops / (1.0 * item.second.numberOfWorkshops)) * 100.0 >= percentOfWorkshops)
						vectorID.push_back(item.first);
				break;
			}
			
		default:
			break;
		}
		std::cout << "\nID: ";
		for (int i : vectorID)
			std::cout << i << "  ";
		std::cout << "\n";
	}
	return vectorID;

}
*/

template<typename classType>
inline void Network::filtration(unordered_map<int, classType>& map, vector<int> vectorID)
{

	if (!vectorID.size()) {
		return;
	}

	for (int i : vectorID)
	{
		std::cout << "\nID: " << i;
		map[i].output();
	}

	std::cout << "\nDo you want to change them (it)?\n0) No\n1) Yes\n";
	if (!choose(1)) {
		return;
	}
	
	std::cout << "\nEdit all or set of objects?\n0) all\n1) set\n";

	switch (choose(1)) {
	case 0:
		for (int id : vectorID) {
			map[id].edit();
			std::cout << "ID: " << id;
			map[id].output();
		}
		break;
	case 1:
		std::cout << "\nInput id(s), which you want to change or 0 to exit\n";

		set<int> setOfChangeable;
		int choice;

		do {
			choice = choose(classType::id);
			if (choice == 0)
				break;
			if (find(vectorID.begin(), vectorID.end(), choice) != vectorID.end())
				setOfChangeable.insert(choice);
			else
				std::cout << "Out of set\n";
		} while (choice != 0);
		for (int id : setOfChangeable) {
			map[id].edit();
			std::cout << "ID: " << id;
			map[id].output();
		}
		break;
	}
}
