#pragma once
#include <string>

using namespace std;

class Pipe {
public:
    static int id;
    string name;
    int diameter;
    double length;
    bool isWorking;

    Pipe();

    Pipe(string name, int diameter, double length, bool isWorking);

    ~Pipe();

    void PipeEdit();

    void Output();
private:

};  


