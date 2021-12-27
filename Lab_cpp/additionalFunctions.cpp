#include "additionalFunctions.h"
#include <limits>

using namespace std;

void printMenu() {
    std::cout << "\n\nMenu:\n";
    std::cout << "1. Add pipe\n";
    std::cout << "2. Add station\n";
    std::cout << "3. Output\n";
    std::cout << "4. Edit pipe\n";
    std::cout << "5. Edit station\n";
    std::cout << "6. Delete pipe\n";
    std::cout << "7. Delete station\n";
    std::cout << "8. Search (and filter) pipes\n";
    std::cout << "9. Search (and filter) stations\n";
    std::cout << "10. Connect pipe\n";
    std::cout << "11. Disconnect pipe\n";
    std::cout << "12. Topological sort\n";
    std::cout << "13. Save\n";
    std::cout << "14. Load\n";
    std::cout << "0. Exit\n\n";
}

int inputInteger() {
    string str;
    
    cin >> str;
    if (str.find_first_not_of("0123456789") != string::npos) {
        std::cout << "Wrong input\n";
    }
    else {
        return stoi(str);
    }
    cin.ignore();
    return -1;
}

double inputDouble() {
    string str;
    cin.ignore();
    cin >> str;
    if (str.find_first_not_of("0123456789.") != string::npos || str.length() == count(str.begin(), str.end(), '.')) {
        std::cout << "Wrong input\n";
        std::cout << "Try again: \n";
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
            std::cout << "Out of range\n";
    } while (result < 0 || result > number); 
    
    return result;
}
