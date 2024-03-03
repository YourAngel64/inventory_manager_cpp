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

void update_data(fstream file, fstream file_update, string product_name, string area, int new_data){
    string x, repeated_data_check;
    int counter = 0;
    bool is_update_product = false, is_old_data = false;


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

    file = use_file("Inventory.txt", "write");
    file_update = use_file("Inventory_fast.txt", "read");

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

#endif