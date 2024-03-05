#ifndef FILE_FUNC
#define FILE_FUNC

//Using libs
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
using std::fstream;


/*
std::fstream use_file
Closes file and then it re-opens it again.
1st arg: file_name - file of the name that you want to use
2nd arg: mode- "read" for "std::ios::in" and "write" for "std::ios::out"
*/
fstream use_file(string file_name, string mode){
    fstream file;
    file.open(file_name, std::ios::in);
    file.close();
    
    if(mode.compare("read") == 0){
        file.open(file_name, std::ios::in);
        return file;
    }
    else if(mode.compare("write") == 0){
        file.open(file_name, std::ios::out);
        return file;
    }
    else{
        cout << "Invalid mode input" << endl;
        exit(1);
    }
}

/*
int get_data
Will get data from a specific area of the product
1st arg: fstream file- file in which all the products are located. Normally will be "Inventory.txt"
2nd arg: string name_of_product - name of the product that is being located. pruchased_product.name
3rd arg: string area_of_data - name of the area that is being used. for example: "Quantity:" !!Dont't forget ":"
Will return int with the number of the data that is being searched
*/
int get_data(fstream file, string name_of_product, string area_of_data){
    string x;
    int data;
    bool is_update_product = false, is_area = false;

    while(file){
        file >> x;

        if(x.compare(name_of_product) == 0){
            is_update_product = true;
        }
        else if(is_update_product && x.compare(area_of_data) == 0){
            file >> x;
            is_area = true;
        }
        
        if(is_update_product && is_area){
            data = stoi(x);
            is_area = false;
            is_update_product = false;
            break;
        }

        if(file.eof()){break;}
    }

    return data;
}

/*
void update_data
Updates data on the file my moving everything to a temporaly file and then moving everything back
to the original file. It does both because its easier like this lmao
1st arg: fstream file - Base file
2nd arg: string product_name - name of the product in which we are going to perform the action to
3rd arg: string area - area of the product in whcih we are going to change EX: "Quantity:"
4th arg: int new_data - new data that is going to be replaced by
*/
void update_data(fstream file, string product_name, string area, int new_data){
    fstream file_update = use_file("Inventory_fast.txt", "write");
    string x, repeated_data_check;
    int counter = 0;
    bool is_update_product = false, is_old_data = false;

    //step 1: move everything to temporal file by changing the values we want to change in the area we want to change
    while(file_update){
        file >> x;
        if(x == repeated_data_check){ //checks if x is being repeated twice. if so then break
            break;
        }

        if(counter >= 2){
            
            if(is_update_product == true && x.compare(area) == 0){
                file_update << "\n" << area << " " << new_data;
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
        else if(x.compare(product_name) == 0){
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

    //Close and open all files. Now we are going to write to file and read from file_update
    file = use_file("Inventory.txt", "write");
    file_update = use_file("Inventory_fast.txt", "read");

    //make sure variables are clean before continue
    x = "";
    counter = 0;
    
    //step 2: move everything back to main file
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

    //close all files and also removing temporal file cause we don't need it no more
    file_update.close();
    std::remove("./Inventory_fast.txt"); //delete file after use. only used to update values

    file.close();
}

/*
Will return bool true if item is found in the inventory. False if it's not found
1st arg- string product_name - name of the product is being looked in the inventory
*/
bool item_exists(string product_name){
    fstream file = use_file("Inventory.txt", "read");
    string x;
    bool item_exists_bool = false;

    while(file){
        file >> x;
        if(x.find(product_name) == 0)
            item_exists_bool = true;
        if(file.eof())
            break;
    }

    return item_exists_bool;
}

/*
void print_one - will print to the console all the details of 1 especific object on the inventory
1st arg- string product_name - name of the product of which the information is going to be printed
*/
void print_one(string product_name){
    fstream file;
    string x;
    int counter = 1;
    bool item_area = false;

    file = use_file("Inventory.txt", "read");
    
    while(file){
        file >> x;

        if(x.compare(product_name) == 0){
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

/*
void print_all - prints everything on the inventory
no args
*/
void print_all(){
    fstream file = use_file("Inventory.txt", "read");
    int counter = 0, number_of_item = 1;
    string x, repeated_data;

    while(file){
        file >> x;
        if(x == repeated_data){
            break;
        }

        if(x.compare("Name:") == 0){ //if prints Name: again means that we dont need this anymore
            if(number_of_item == 1){
                cout << number_of_item << ")" << endl;
                cout << x;
                repeated_data = x;
                number_of_item++;
                counter++;
            }
            else{
                cout << "\n";
                cout << "\n";
                cout << number_of_item << ")" << endl;
                cout << x;
                repeated_data = x;
                counter = 1;
                number_of_item++;
            }
        }
        else if(counter == 2){
            cout << "\n";
            cout << x;
            repeated_data = x;
            counter = 1;
        }
        else{
            cout << x;
            repeated_data = x;
            counter++;
        }
    

        if(file.eof()){break;}
    }

}
#endif