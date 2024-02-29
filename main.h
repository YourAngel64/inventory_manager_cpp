#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>
#include <cmath>
#include <fstream> //lib to manage the files
#include <cstdio> // lib to delete files

//Most common using
using std::cout;
using std::cin;
using std::endl;
using std::string;

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
void inventory_file(int file_mode){
    std::fstream file;

    switch(file_mode){
        case 0: //0 for writting into the file
            file.open("Inventory.txt", std::ios::app);
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
            break;
        case 1: //1 for reading the file
            file.open("Inventory.txt", std::ios::in);        
            break;
    }
    file.close();
}

//Biggest function so far
void update(string new_info){
    std::fstream file, file_update; //File var
    int counter = 0; //int vars
    string x, repeated_data_check; // Str vars
    bool is_update_product = false, is_old_data = false; //bool vars

    // file.open("Inventory.txt", std::ios::in);
    // while(file){
    //     file >> x;
    //     if(x.find(purchase_product.name) == 0)
    //         break;
    //     if(file.eof())
    //         break;
    //     line++;
    // }

    // number_of_item = floor(line/26);
    // calculation = (line - (16 * number_of_item));


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

   //Check is argument is valid as a quantity
    try{
        stoi(new_info);
    }
    catch(const std::exception& e){
        cout << "Invalid input for quantity. Please input a number" << endl;
    }
    


   //get everything to temporary file to change values and then tranfer all back to Inventory.txt
    file.open("Inventory.txt", std::ios::in);
    file_update.open("Inventory_fast.txt", std::ios::out);

    while(file_update){
        file >> x;
        if(x == repeated_data_check){ //checks if x is being repeated twice. if so then break
            break;
        }

        if(counter >= 2){
            
            if(is_update_product == true && x.compare("Quantity:") == 0){
                file_update << "\n" << "Quantity: " << new_info;
                counter = 1;
                is_update_product = false;
                is_old_data = true;
            }
            else{
                file_update << "\n";
                file_update << x + " ";
                repeated_data_check = x;
                counter = 1;
            }
        }
        else if(x.compare(purchase_product.name) == 0){
            is_update_product = true;
            file_update << x + " ";
            counter++;
        } 
        else if(is_old_data){  //Here we jump that old data we don't wanna write
            is_old_data = false; 
            counter++;
        }
        else{
            file_update << x + " ";
            repeated_data_check = x;
            counter++;
        }
        if(file.eof()){break;}
    }
   

   //Get everything to Inventory.txt
   file.close();
   file_update.close();

   file.open("Inventory.txt", std::ios::out); //now write everything into main file
   file_update.open("Inventory_fast.txt", std::ios::in); //now read everything

    //make sure variables are clean before continue
    x = "";
    counter = 0;
    
    while(file_update){
        file_update >> x;

        if(x == repeated_data_check){
            break;
        }

        if(counter >= 2){
            file << "\n";
            file << x + " ";
            repeated_data_check = x;
            counter = 1;
        }
        else{
            file << x + " ";
            repeated_data_check = x;
            counter++;
        
        if(file_update.eof()){break;}}
    }

    file_update.close();
    std::remove("./Inventory_fast.txt"); //delete file after use. only used to update values
    file.close();
}

//Now it is time for the functions that the main function call:
//*This functions use and call the functions above
//Algorithm for first option

void purchase(){
    std::fstream file;
    string x, amount;;
    bool item_exists = false; 

    file.open("Inventory.txt", std::ios::in);

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
            update(amount);
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

    inventory_file(0);
}

//Algorithm for second option
void sell(){
    std::fstream file;
    string x;
    bool item_exists = false; 

    file.open("Inventory.txt", std::ios::in);

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

    exit(0);
}

//algorithm for third option
void check(){

}

#endif