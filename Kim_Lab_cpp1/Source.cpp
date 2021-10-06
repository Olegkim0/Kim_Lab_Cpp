#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void printMenu() {
    cout << "\nMenu:\n";
    cout << "1. Add pipe\n";
    cout << "2. Add station\n";
    cout << "3. Output\n";
    cout << "4. Edit pipe\n";
    cout << "5. Edit station\n";
    cout << "6. Save\n";
    cout << "7. Load\n";
    cout << "0. Exit\n\n";
}

int input() {
    string str;
    cin.ignore();
    cin >> str;
    if (str.find_first_not_of("0123456789") != string::npos) {
        cout << "Wrong input\n";
        cout << "Try again: \n";
    }
    else {
        return stoi(str);
    }
    return -1;
}

struct Pipe {
    int id;
    int diameter;
    int length;
    bool isWorking = true;
};

Pipe AddPipe(int id)
{
    cout << "Adding Pipe\n";
    Pipe p;

    cout << "Input diameter:\n";
    p.diameter = 0;
    while (p.diameter <= 0) {    
        p.diameter = input();
    }

    cout << "Input length:\n";
    p.length = 0;
    while (p.length <= 0) {
        p.length = input();
    }
    return p;
}

Pipe PipeEdit(Pipe& p) {
    p.isWorking = !p.isWorking;
    cout << "Pipe edited\n";
    cout << "Is pipe working? " << p.isWorking << "\n";
    return p;
}

struct Station {
    int id;
    string name;
    int number_of_workshops;
    int number_of_working_workshops;
    int Efficiency;
};

Station AddStation(int id) {
    cout << "Adding Station\n";
    Station s;

    cout << "Input name:\n";
    cin >> s.name;

    cout << "Input number of workshops:\n";
    s.number_of_workshops = 0;
    while (s.number_of_workshops <= 0) {
        s.number_of_workshops = input();
    }

    cout << "Input number of working workshops:\n";
    s.number_of_working_workshops = -1;
    while (s.number_of_working_workshops < 0 || s.number_of_working_workshops > s.number_of_workshops) {
        s.number_of_working_workshops = input();
        if (s.number_of_working_workshops > s.number_of_workshops) {
            cout << "Wrong input\n";
            cout << "Try again:\n";
        }
    }

    cout << "Input Efficiency (0 < e <= 100):\n";
    s.Efficiency = 0;
    while (s.Efficiency <= 0 || s.Efficiency > 100) {
        s.Efficiency = input();
    }
    return s;
}

void StationEdit(Station& s) {
    cout << "Editing station\n";
    cout << "Input number of working workshops:\n";
    s.number_of_working_workshops = -1;
    while (s.number_of_working_workshops < 0 || s.number_of_working_workshops > s.number_of_workshops) {
        s.number_of_working_workshops = input();
        if (s.number_of_working_workshops > s.number_of_workshops) {
            cout << "Wrong input\n";
            cout << "Try again:\n";
        }
    }
}

void Output(Pipe p, Station s)
{
    cout << "Output\n";
    if (p.length > 0) {
        cout << "\nOutput Pipe(s)";
        cout << "\nId: " << p.id;
        cout << "\nDiameter: " << p.diameter;
        cout << "\nLength: " << p.length << "\n";
    }
    if (s.name != "") {
        cout << "\nOutput station(s)";
        cout << "\nId: " << s.id;
        cout << "\nname: " << s.name;
        cout << "\nnumber of workshops: " << s.number_of_workshops;
        cout << "\nnumber of working workshops: " << s.number_of_working_workshops;
        cout << "\nEfficiency: " << s.Efficiency << "\n";
    }
}

void Save(Pipe p, Station s) {
    ofstream file;
    file.open("database.txt");
    // if(arrayStation.length() != 0) {}
    // for (int i; i < arrayStation.length(); i++){}
    if (file.good()) {
        if (p.length > 0) {
            file << "Pipe:\n";
            file << p.id << "\n";
            file << p.diameter << "\n";
            file << p.length << "\n";
            file << p.isWorking << "\n";
        }
        if (s.name != "") {
            file << "Station:\n";
            file << s.id << "\n";
            file << s.name << "\n";
            file << s.number_of_workshops << "\n";
            file << s.number_of_working_workshops << "\n";
            file << s.Efficiency;
        }
        file.close();
        cout << "Saved\n";
    }
}

void Load(Pipe& p, Station& s) {
    ifstream file;
    file.open("database.txt");
    if (file.good()) {
        while (!file.eof()) {
            string type;
            file >> type;
            if (type == "Pipe:") {
                file >> p.id;
                file >> p.diameter;
                file >> p.length;
                file >> p.isWorking;
            }
            if (type == "Station:") {
                file >> s.id;
                file >> s.name;
                file >> s.number_of_workshops;
                file >> s.number_of_working_workshops;
                file >> s.Efficiency;
            }
        }
    }
    cout << "Loaded\n";
}

int main()
{
    Pipe p1;
    p1.length = -1;  // костыль
    Station s1;
    s1.name = "";  // костыль
    bool menu = true;
    while (menu) {
        printMenu();
        int choose;
        cin >> choose;
        switch (choose) {
        case 0:
            cout << "\nExit\n";
            menu = false;
            break;
        case 1:
            p1 = AddPipe(0);
            break;
        case 2:
            s1 = AddStation(0);
            break;
        case 3:
            // if (vector_of_Pipes.length != 0){}
            Output(p1, s1);
            // if (vector_of_Station.length != 0){}
            break;
        case 4:
            PipeEdit(p1);
            break;
        case 5:
            StationEdit(s1);
            break;
        case 6:
            // При первом сейве сделать проверку на vector.length 
            Save(p1, s1);
            break;
        case 7:
            Load(p1, s1);
            break;
        default:
            break;
        }
    }
    return 0;
}