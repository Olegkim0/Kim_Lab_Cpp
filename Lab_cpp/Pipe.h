#pragma once
#include <string>

using namespace std;

class Pipe {
public:
    string name;
    int diameter;
    double length;
    bool isWorking;

    Pipe();

    Pipe(string name, int diameter, double length, bool isWorking);

    ~Pipe();

    void PipeEdit();

    void Output();

    static void setId(int newID);

    static int getId();
private:
    static int id;

};  


