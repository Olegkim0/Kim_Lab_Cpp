#include <iostream>
#include <limits>
#include <string>


struct Pipe {
    int id;
    int diameter;
    int length;
    bool isWorking;
};

Pipe AddPipe(int id)
{
    std::cout << "Adding Pipe\n";

    Pipe p;

    std::cout << "Input diameter:\n";
    p.diameter = 0;

    while (p.diameter <= 0) {
        std::string str_diameter;
        std::cin.ignore();
        std::cin >> str_diameter;
        if (str_diameter.find_first_not_of("0123456789") != std::string::npos) {
            std::cout << "The input contains not only digits\n";
            std::cout << "Try again: \n";
        }
        else {
            p.diameter = std::stoi(str_diameter);
        }
    }

    std::cout << "Input length:\n";
    p.length = 0;

    while (p.length <= 0) {
        std::string str_length;
        std::cin.ignore();
        std::cin >> str_length;
        if (str_length.find_first_not_of("0123456789") != std::string::npos) {
            std::cout << "The input contains not only digits\n";
            std::cout << "Try again: \n";
        }
        else {
            p.length = std::stoi(str_length);
        }
    }

    return p;
}

Pipe PipeEdit(Pipe p) {
    std::cout << "Pipe edited\n";
    p.isWorking = !p.isWorking;
    std::cout << "Is pipe working? " << p.isWorking << "\n";
    return p;
}

struct Station {
    int id;
    std::string name;
    int number_of_workshops;
    int number_of_working_workshops;
    int Efficiency;
};

Station AddStation(int id) {

    std::cout << "Adding Station\n";

    Station s;

    std::cout << "Input name:\n";
    std::cin >> s.name;

    std::cout << "Input number of workshops:\n";
    s.number_of_workshops = 0;
    while (s.number_of_workshops <= 0) {
        std::string str_number_of_workshop;
        std::cin.ignore();
        std::cin >> str_number_of_workshop;
        if (str_number_of_workshop == "0") {
            std::cout << "Wrong input";
        }
        if (str_number_of_workshop.find_first_not_of("0123456789") != std::string::npos) {
            std::cout << "The input contains not only digits\n";
            std::cout << "Try again: \n";
        }
        else {
            s.number_of_workshops = std::stoi(str_number_of_workshop);
        }
    }

    std::cout << "Input number of working workshops:\n";
    s.number_of_working_workshops = -1;
    while (s.number_of_working_workshops < 0 || s.number_of_working_workshops > s.number_of_workshops) {
        std::string str_number_of_working_workshops;
        std::cin.ignore();
        std::cin >> str_number_of_working_workshops;

        if (str_number_of_working_workshops.find_first_not_of("0123456789") != std::string::npos) {
            std::cout << "Wrong input\n";
            std::cout << "Try again: \n";
            continue;
        }
        else {
            s.number_of_working_workshops = std::stoi(str_number_of_working_workshops);
        }

        if (s.number_of_working_workshops > s.number_of_workshops) {
            std::cout << "number of working workshops > number of workshops\n";
        }
    }


    std::cout << "Input Efficiency (0 < e <= 100):\n";
    s.Efficiency = 0;
    while (s.Efficiency <= 0 || s.Efficiency > 100) {
        std::string str_Efficiency;
        std::cin.ignore();
        std::cin >> str_Efficiency;
        if (str_Efficiency.find_first_not_of("0123456789") != std::string::npos) {
            std::cout << "The input contains not only digits\n";
            std::cout << "Try again: \n";
        }
        else {
            s.Efficiency = std::stoi(str_Efficiency);
        }
    }

    return s;
}

Station StationEdit(Station s) {
    std::cout << "Editing station\n";
    std::cin >> s.number_of_working_workshops;
    return s;
}


void Output(Pipe& p)
{
    std::cout << "\nOutput Pipe(s)";
    std::cout << "\nId: " << p.id;
    std::cout << "\nDiameter: " << p.diameter;
    std::cout << "\nLength: " << p.length << "\n";
}

void Output(Station& s) {
    std::cout << "\nOutput station(s)";
    std::cout << "\nId: " << s.id;
    std::cout << "\nname: " << s.name;
    std::cout << "\nnumber of workshops: " << s.number_of_workshops;
    std::cout << "\nnumber of working workshops: " << s.number_of_working_workshops;
    std::cout << "\nEfficiency: " << s.Efficiency << "\n";
}

int main()
{
    int pipe_counter = 0;
    int station_counter = 0;
    int choose;
    Station s1;
    Pipe p1;
    bool menu = true;

    while (menu) {

        std::cout << "menu\n";

        int choose;
        std::cin >> choose;

        switch (choose) {
        case 0:
            std::cout << "\nExit\n";
            menu = false;
            break;

        case 1:
            p1 = AddPipe(pipe_counter);
            break;

        case 2:
            s1 = AddStation(station_counter);
            break;

        case 3:
            // if (vector_of_Pipes.length != 0){}
            Output(p1);
            // if (vector_of_Station.length != 0){}
            Output(s1);
            break;

        case 4:
            PipeEdit(p1);
            break;

        case 5:
            StationEdit(s1);
            break;

        case 6:
            //Save();
            break;

        case 7:
            //Load();
            break;

        default:
            break;
        }
    }
    return 0;
}