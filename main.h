#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>
#include <cmath>

using std::cout;
using std::cin;
using std::endl;

class product{
public:
    
protected:

};


//First choose what option the user wants to perform
int* option(){
    int* choice = new int;

    cout << "Please select the action you want to perform:" << endl;
    cout << "1)Purchase item and save it to inventory" << endl;
    cout << "2)Sell item from available inventory" << endl;
    cout << "3)Check Inventory information" << endl;
    cin >> *choice;

    return choice;
}

//Algorithm for first option
void purchase(){

}

//Algorithm for second option
void sell(){

}

//algorithm for third option
void check(){

}

#endif