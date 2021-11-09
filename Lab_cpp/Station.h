#pragma once
#include <string>

class Station {
public:
    static int id;
    std::string name;
    int number_of_workshops;
    int number_of_working_workshops;
    int Efficiency;

    Station();

    ~Station();

    void StationEdit();

    void Output();
};