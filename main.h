#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;

class product{
public:
    std::string name;
    int year;
    std::string company;
    std::string platform;
    int quantity;
    float purchase_cost;
    float sell_cost;
    int sold;
    float profit;
};

product purchase_product; //global obj created from product class that is being used through whole program


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


void inventory_file(int file_mode){
    std::fstream file;

    switch(file_mode){
        case 0: //0 for writting into the file
            file.open("Inventory.txt", std::ios::app);
            file << "Name: " << purchase_product.name << endl;
            file << "Year: " << purchase_product.year << endl;
            file << "Company: " << purchase_product.company << endl;
            file << "Console: " << purchase_product.platform << endl;
            file << "Quantity: " << purchase_product.quantity << endl;
            file << "Cost of purchase: " << purchase_product.purchase_cost << endl;
            file << "Cost of selling: " << purchase_product.sell_cost << endl;
            file << "Sold so far: " << purchase_product.sold << endl;
            file << "Profit so far: " << purchase_product.profit << endl;
            file << "\n";
            break;
        case 1: //1 for reading the file
            file.open("Inventory.txt", std::ios::in);        
            break;
    }
    
}


//Algorithm for first option
void purchase(){

    cout << "Enter details of the product: " << endl;

    cout << "Name: ";
    cin >> purchase_product.name;

    cout << "Year: ";
    cin >> purchase_product.year;

    cout << "Company: ";
    cin >> purchase_product.company;

    cout << "Console: ";
    cin >> purchase_product.platform;

    cout << "Quantity: ";
    cin >> purchase_product.quantity;

    cout << "Cost of purchase: ";
    cin >> purchase_product.purchase_cost;

    cout << "Cost of selling: ";
    cin >> purchase_product.sell_cost;

    cout << "Sold so far: ";
    cin >> purchase_product.sold;

    cout << "Profit so far: ";
    cin >> purchase_product.profit;

    inventory_file(0);
}

//Algorithm for second option
void sell(){



  
}

//algorithm for third option
void check(){

}
#endif