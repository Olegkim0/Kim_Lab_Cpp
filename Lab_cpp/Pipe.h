#pragma once
#include <string>

class Pipe {
public:
    static int id;
    std::string name;
    int diameter;
    double length;
    bool isWorking = true;

    Pipe();

    ~Pipe();

    void PipeEdit();

    void Output();


};  


