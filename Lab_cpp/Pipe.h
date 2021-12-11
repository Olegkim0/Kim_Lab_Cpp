#pragma once
#include <string>

using namespace std;

class Pipe {
public:
    string name;
    int diameter;
    double length;
    bool isWorking;
    static int id;
    int startID = 0;
    int endID = 0;

    Pipe();

    Pipe(string name, int diameter, double length, bool isWorking);

    ~Pipe();

    void edit();

    void output();

private:

};  


