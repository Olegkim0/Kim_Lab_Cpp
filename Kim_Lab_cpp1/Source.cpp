#include <iostream>



struct Pipe {
    int id;
    int diameter;
    int length;
    bool working;  // being_repaired

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

    while (true) {
        std::cin >> choose;

        switch (choose) {
        
        case 0:
            break;

        case 1:
            Pipe p1 = AddPipe(pipe_counter);
            break;

        case 2:
            //  AddStation(station_counter;
            break;

        case 3:
            //  Output(vector);
            break;

        case 4:
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



        Output(p1);



        counter++;
        break;
    }
    return 0;
}