#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::string;

class product{
public:
    string name;
    int year;
    string company;
    string platform;
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

//function that deals with saving and reading inventory items
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
    file.close();
}

void update(string new_info){
    std::fstream file;
    file.open("Inventory.txt", std::ios::in);
    int line = 0, number_of_item, calculation, file_length = 0;
    string x;

    while(file){
        file >> x;
        if(x.find(purchase_product.name) == 0)
            break;
        if(file.eof())
            break;
        line++;
    }

    number_of_item = floor(line/26);
    calculation = (line - (16 * number_of_item));

    while(file){

        if(file.eof()){
            break;
        }
        file_length++;
    }

    cout << file_length;
    /*
    26 is the difference between the outputs
    16 is the difference of the difference of goal and OP
    EX:

    Goal: (unknown)                 OP:
    11        +17                   27 (+ 26)=
    21        +33                   53 (+ 26)=
    31        +49                   79 (+ 26)=

    17 + 16 = 33 + 16 = 49...
    */
   
   string file_change[] = {};
   
   while(file){
        file >> x;
        for(int i = 0; i < file_length; i++){
            file_change->append(x);
        }

        if(file.eof()){break;}
   }
    

   
   
    cout << file_change;
}

//Algorithm for first option
void purchase(){
    std::fstream file;
    file.open("Inventory.txt", std::ios::in);
    string x;
    bool item_exists = false; 

    cout << "Enter details of the product: " << endl;

    cout << "Name: ";
    cin >> purchase_product.name;

    while(file){
        file >> x;
        if(x.find(purchase_product.name) == 0)
            item_exists = true;
        if(file.eof())
            break;
    }

    if(item_exists){
        cout << "Item exists already. Want to update quantity? [yes/no]?";
        cin >> x;
        
        for(int i = 0; i < x.length(); i++){
            x[i] = std::tolower(x[i]);
        }

        if(x.compare("yes") == 0){
            update("ola");
        }
        else if(x.compare("no") == 0){} //Programs continues
        else{
            cout << "Invalid Input"; 
            exit(1);
        }
    }

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