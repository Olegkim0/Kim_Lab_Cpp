
#include <iostream>



struct Pipe {
    int id;
    int d;

};


int main()
{
    using namespace std;

    Pipe p{ 0 };
    
    cout << "Input diameter\n";
    cin >> p.d;
    cout << "Id: ";
    cout << p.id + "\n";
    cout << p.d;

    return 0;
}