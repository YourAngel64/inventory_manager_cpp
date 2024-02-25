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

-Purchase(kinds like writting into a file):
We are gonna code this by somehow implementing some kind of class maybe?
First:
How many individual products you want to add to the inventory?

Second:
Name -> 
Year -> 
Company -> 
Console ->  
Quantity -> 
How much it costed (By 1 individual item) -> 
How much is going to be sold for (By 1 individual item) -> 
Solds so far:
profit so far:

Extra details:

-Sell(kinds like reading into a file):
First: 
Ingress name of item. if item is found then proceed, if not then error and reset program

Second:
How many are we selling? -> if items available and can be sold then proceed
For how much? -> then we can calculate the profit

if everything goes well then SOLD SUCCESSFULLY

-Check:
Print everything in the inventory available in the order of the details of being purchased
Maximum of 3 items per page
ex (1/4)

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
-whenever basics of program is done, then we should add 2 more functions for deleting and for editing items in inventory
*/


int main(){
    int* choice = option();
    
    //Check user input if is 1 or 2 or 3. If input is not valid then program is gonna close
    if(*choice == 1 || *choice == 2 || *choice == 3){}
    else{exit(1);}

    //Depending of the choise of the user is gonna call the correct function
    switch(*choice){
        case 1:
            cout << "woahh" << endl;
            purchase();
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