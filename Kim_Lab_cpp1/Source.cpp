#include <iostream>


struct Pipe {
    int id; 
    int diameter;
    int length;
    bool isWorking;  
};

Pipe AddPipe(int id)
{
    std::cout << "AddPipe\n";


    Pipe p{ 0 };

    std::cout << "Input diameter:\n";
    std::cin >> p.diameter;

    std::cout << "Input length:\n";
    std::cin >> p.length;


    while (p.diameter <= 0) {
        std::cin >> p.diameter;
        std::cout << "Wrong diameter, try again\n";
        continue;
    }

    while (p.length <= 0) {
        std::cin >> p.length;
        std::cout << "Wrong length, try again\n";
        continue;
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

    Station s{ 0 };

    std::cout << "Input name:\n";
    std::cin >> s.name;
    while (s.name.length() <= 0) {
        std::cin >> s.name;
        std::cout << "Wrong name, try again";
        continue;
    }

    std::cout << "Input number of workshops:\n";
    std::cin >> s.number_of_workshops;

    std::cout << "Input number of working workshops:\n";
    std::cin >> s.number_of_working_workshops;
    
    std::cout << "Input Efficiency (0 <= e <= 1):\n";
    std::cin >> s.Efficiency;
    while (s.Efficiency <= 0 && s.Efficiency > 1) {
        std::cin >> s.Efficiency;
        std::cout << "Wrong Efficiency, try again";
        continue;
    }

    return s;
}

Station StationEdit(Station s) {
    std::cout << "Editing station\n";
    std::cin >> s.Efficiency;
    return s;
}
    

void Output(Pipe& p)
{
    std::cout << "Output Pipe(s)\n";
    std::cout << "Id: " << p.id;
    std::cout << "\nDiameter: " << p.diameter;
    std::cout << "\nLength: " << p.length << "\n";
}

void Output(Station& s) {
    std::cout << "Output station(s)\n";
    std::cout << "Id: " << s.id;
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

    bool menu = true;

    while (menu) {

        std::cout << "menu\n";
        
        Station s;

        int choose;
        std::cin >> choose;

        switch(choose){
            case 0:
                std::cout << "\nExit\n";
                menu = false;
                break;

            case 1:
                Pipe p1 = AddPipe(pipe_counter);
                break;

            case 2:
                //Station s1 = AddStation(station_counter);
                break;

            case 3:
                Output(p1);
                //Output(s1);
                break;

            case 4:
                PipeEdit(p1);
                break;

            case 5:
                //StationEdit(s1);
                break;

            case 6: 
                break;

            case 7:
                break;

            default:
                break;
            }

        //break;
    }
    return 0;
}