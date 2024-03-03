#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>
#include <cmath>
#include <fstream> //lib to manage the files
#include <cstdio> // lib to delete files
#include "file_functions.h" //function to deal with these pesky files

//Most common using
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::fstream;

//Class with attributes to create the product. is public for all the functions
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
//Returns pointer to one int for the option that the user wants to perform
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
void inventory_file(){
    fstream file;
    file = use_file("Inventory.txt", "read");

    file << "\n";
    file << "Name: " << purchase_product.name << endl;
    file << "Year: " << purchase_product.year << endl;
    file << "Company: " << purchase_product.company << endl;
    file << "Console: " << purchase_product.platform << endl;
    file << "Quantity: " << purchase_product.quantity << endl;
    file << "Cost_of_purchase: " << purchase_product.purchase_cost << endl;
    file << "Cost_of_selling: " << purchase_product.sell_cost << endl;
    file <<  "Sold_so_far: " << purchase_product.sold << endl;
    file << "profit: " << purchase_product.profit;
    
    file.close();
}

//Print simple information of the object that is about to be sold
void sell_print_information(){
    fstream file;
    string x;
    int counter = 1;
    bool item_area = false;

    file = use_file("Inventory.txt", "read");
    
    while(file){
        file >> x;

        if(x.compare(purchase_product.name) == 0){
            cout << "--------------------------" << endl;
            cout << "Name: ";
            item_area = true;
        }

        if(item_area){
            if(x.compare("Name:") == 0){ //if prints Name: again means that we dont need this anymore
                cout << "\n";
                cout << "--------------------------" << endl;
                break;
            }
            else if(counter == 2){
                cout << "\n";
                cout << x;
                counter = 1;
            }
            else{
                cout << x;
                counter++;
            }
        }

        if(file.eof()){break;}
    }

    file.close();
}

//Whenever object is sold, will update: Quantity, sold_so_far and profit
void sell_object(int amount){
    int counter = 0, old_amount = 0, sold_so_far = 0, profit = 0, sell_price = 0; //int vars
        
    //Get quantity:
    old_amount = get_data(use_file("Inventory.txt", "read"), purchase_product.name, "Quantity:");

    //Sold_so_far:
    sold_so_far = get_data(use_file("Inventory.txt", "read"), purchase_product.name, "Sold_so_far:");
    
    //profit:
    profit = get_data(use_file("Inventory.txt", "read"), purchase_product.name, "profit:");
    

    //Cost_of_selling //sell_cost:
    sell_price = get_data(use_file("Inventory.txt", "read"), purchase_product.name, "Cost_of_selling:");


    //variables to update document
    old_amount -= amount;
    sold_so_far += amount;
    profit = (sell_price * amount) + profit;

    if(old_amount < 0){
        cout << "To sell such quantity is not possible. Not enough" << endl;
        exit(1);
    }

    update_data(use_file("Inventory.txt", "read"), use_file("Inventory_fast.txt", "write"), purchase_product.name , "Quantity:", old_amount);
    update_data(use_file("Inventory.txt", "read"), use_file("Inventory_fast.txt", "write"), purchase_product.name , "Sold_so_far:", sold_so_far);
    update_data(use_file("Inventory.txt", "read"), use_file("Inventory_fast.txt", "write"), purchase_product.name , "profit:", profit);

}
//Now it is time for the functions that the main function call:
//*This functions use and call the functions above
//Algorithm for first option

void purchase(){
    fstream file;
    string x, amount;
    int amount_int;
    bool item_exists = false; 

    file = use_file("Inventory.txt", "read");

    cout << "Enter details of the product: " << endl;

    cout << "Name: ";
    cin >> purchase_product.name;

    //Check if name item is already in the inventory
    while(file){
        file >> x;
        if(x.find(purchase_product.name) == 0)
            item_exists = true;
        if(file.eof())
            break;
    }

    //if does exists then asks user if wish to change quantity. If so then update() will be called
    //With an arguments having the new data
    if(item_exists){

        cout << "Item exists already. Want to update quantity? [yes/no]? ";
        cin >> x;
        
        for(int i = 0; i < x.length(); i++){
            x[i] = std::tolower(x[i]);
        }

        if(x.compare("yes") == 0){
            cout << "New quantity:";
            cin >> amount;

            try{
                amount_int = stoi(amount);
            }
            catch(const std::exception& e){
                cout << "Invalid new amount. Please input a number" << endl;
            }
            
            update_data(use_file("Inventory.txt", "read"), use_file("Inventory_fast.txt", "write"), purchase_product.name , "Quantity:", amount_int);
            exit(0);
        }
        else if(x.compare("no") == 0){
            exit(0);
        } 
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

    cout << "Profit: ";
    cin >> purchase_product.profit;

    inventory_file();
}

//Algorithm for second option
void sell(){
    fstream file;
    string x, amount;
    int amount_int;
    bool item_exists = false; 

    file = use_file("Inventory.txt", "read");

    cout << "Enter the name of the product to sell: " << endl;

    cout << "Name: ";
    cin >> purchase_product.name;

    //Check if name item is already in the inventory
    while(file){
        file >> x;
        if(x.find(purchase_product.name) == 0)
            item_exists = true;
        if(file.eof())
            break;
    }

    //If item does not exists, program will close
    if(!item_exists){
        cout << "Item does no exits, please check the name properly";    
        exit(1);
    }

    sell_print_information();

    cout << "How many you want to sell?" << endl;
    cin >> amount;

    //Check if input is valid
    try{
        amount_int = stoi(amount);
    }
    catch(const std::exception& e){
        cout << "Invalid input. Please input a number" << endl;
        exit(1);
    }
    
    sell_object(amount_int);
    
}

//algorithm for third option
void check(){

}

#endif