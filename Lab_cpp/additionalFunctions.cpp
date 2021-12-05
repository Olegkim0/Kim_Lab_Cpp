#include "additionalFunctions.h"

using namespace std;

void printMenu() {
    cout << "\n\nMenu:\n";
    cout << "1. Add pipe\n";
    cout << "2. Add station\n";
    cout << "3. Output\n";
    cout << "4. Edit pipe\n";
    cout << "5. Edit station\n";
    cout << "6. Delete pipe\n";
    cout << "7. Delete station\n";
    cout << "8. Search (and filter) pipes\n";
    cout << "9. Search (and filter) stations\n";
    cout << "10. Save\n";
    cout << "11. Load\n";
    cout << "0. Exit\n\n";
}

int inputInteger() {
    string str;
    cin.ignore();
    cin >> str;
    if (str.find_first_not_of("0123456789") != string::npos) {
        cout << "Wrong input\n";
    }
    else {
        return stoi(str);
    }
    return -1;
}

double inputDouble() {
    string str;
    cin.ignore();
    cin >> str;
    if (str.find_first_not_of("0123456789.") != string::npos || str.length() == count(str.begin(), str.end(), '.')) {
        cout << "Wrong input\n";
        cout << "Try again: \n";
    }
    else {
        return stod(str);
    }
    return -1;
}

int choose(int number) {
    int result;
    do {
        result = inputInteger();
        if (result < 0 || result > number)
            cout << "Out of range\n";
    }
    while (result < 0 || result > number); 
    
    return result;
}

