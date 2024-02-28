#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

int main(){
    string number;
    int number_str;

    cout << "Input number" << endl;
    cin >> number;

    try
    {
        number_str = stoi(number);
        cout << number_str << endl;
    }
    catch(const std::exception& e)
    {
        cout << "Invelid input" << endl;
    }

    

    return 0;
}