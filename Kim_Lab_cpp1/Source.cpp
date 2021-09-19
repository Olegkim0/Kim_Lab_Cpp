#include <iostream>



struct Pipe {
    int id;
    int diameter;
    int length;
    bool working;  // being_repaired

};

struct Station {
    int id;
    std::string name;
    int number_of_workshops;
    int number_of_working_workshops;
    int Efficiency;

};

    

void Output(Pipe& p)
{
    std::cout << "Id: " << p.id;
    std::cout << "\nDiameter: " << p.diameter;
    std::cout << "\nLength: " << p.length;
}

Pipe AddPipe(int id)
{
    
    Pipe p{ 0 };

    std::cout << "Input diameter:\n";
    if (p.diameter < 0) {

    }

    std::cin >> p.diameter;
    
    std::cout << "Input length:\n";
    std::cin >> p.length;

    return p;
}

int main()
{
    int pipe_counter = 0;
    int station_counter = 0;
    int choose;

    bool menu = true;

    while (menu) {

        std::cout << "start\n";
        std::cin >> choose;

        //  !isdigit(choose)
        //  std::cin.fail()
        if (!std::cin.fail() && choose >= 0 && choose <= 7) {

            switch (choose) {

            case 0:
                std::cout << "\nExit\n";
                menu = false;
                break;

            case 1:
                Pipe p1 = AddPipe(pipe_counter);
                std::cout << 213;
                break;

            case 2:
                std::cout << "AddStation\n";
                //  AddStation(station_counter);
                break;

            case 3:
                std::cout << "Output\n";
                //  Output(vector);
                break;

            case 4:
                std::cout << "Editing\n";
                //  Editing(int id);
                break;

            case 5:
                break;

            case 6:
                break;

            case 7:
                break;

            default:
                break;
            }
        }

        else {
            std::cout << "The entered data is incorrect\n" << "Input new value:\n";
            continue;
        }

        //break;
    }
    return 0;
}