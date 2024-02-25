#include <iostream>
#include <string>
#include <cmath>
#include "main.h"

using std::cout;
using std::cin;
using std::endl;

/*
Inventory System Algorithm
Algorithm Goal: Create an inventory system (at least start it). To manage an inventory of a company that sells video games
Algorithm Blueprint:

-Purchase:
Add item to inventory. Details include, Information about purchased object and price of it. And pruchased quantity

-Sell:
Sell item to inventory. Details of the object being sold. Quantity being sold, etc

-print details:
Print details on the items available, the information, quantity available, profit so far, etc

Details to learn in the way:
-How to make console interactive with arrow keys
-Learn how file management in c works
-Learn extra details for classes

Goals:
-master the use of classes and information organization of c++
-Have something cool for portfolio
-It may be useful for any future businesses you may have

Extra details:
-When program is functionable, will make a documentation for it and upload it to github
-It may take u days to finish but dw cause ur learning bro
-before starting project write DETAIL BY DETAIL of each step so you don't get lost
*/


int main(){
    int* choice = option();
    
    //Check user input if is 1 or 2 or 3. If input is not valid then program is gonna close
    if(*choice == 1 || *choice == 2 || *choice == 3){}
    else{exit(1);}

    //Depending of the choise of the user is gonna call the correct function
    switch(*choice){
        case 1:

            break;
        
        case 2:

            break;
        
        case 3:

            break;
    }


    delete choice;
    choice = NULL;

    return 0;
}