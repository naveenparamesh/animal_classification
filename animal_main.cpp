#include <iostream>
#include <cstdlib>
#include <string>
#include "graph.h"

using namespace std;

int main(){
    
    string fileName = "";
    cout << "Enter file name: " << endl;
    cin >> fileName;
    Graph* graph = new Graph(fileName);
    
   
    cout << "Welcome to our graph analysis of the animal heirarchy class. Here are our operations: " << endl;
    cout << endl;
    cout << "1. Display NUMBER/All of the subtypes of a given species of a given order." << endl;
    cout << "2. Display the number of subspecies of a given species." << endl;
    cout << "3. Display  the lowest common ancestor between two given species starting from (SP01)." << endl; 

    
    int choice = 0;
    string species_name = "";
    int order_num = 0;
    string other_name = "";
    int numSubTypes = 0;
    
    cout << "Enter 1, 2, or 3 to continue: " << endl;
    cin >> choice;
    
    switch(choice){
        case 1: 
                while (getline(cin, species_name))
                {
                    if (species_name == ""){
                        cout << "Enter a species name (string): " << endl;    
                    }
                    else {
                        break;
                    }
                }
                species_name = graph->editFormat(species_name);
                cout << "Enter the number of subtypes wanted (int): " << endl;
                cin >> numSubTypes;
                cout << "Enter an order (int): " << endl;
                cin >> order_num;
                graph->optionOne(numSubTypes, species_name, order_num);
                break;
                
        case 2: 
                while (getline(cin, species_name))
                {
                    if (species_name == ""){
                        cout << "Enter a species name (string): " << endl;    
                    }
                    else {
                        break;
                    }
                    
                }
                species_name = graph->editFormat(species_name);
                graph->optionTwo(species_name);
                break;
        case 3: 
                while (getline(cin, species_name))
                {
                    if (species_name == ""){
                        cout << "Enter the first species (string): " << endl;
                    }
                    else {
                        break;
                    }
                }
                species_name = graph->editFormat(species_name);
                
                while (getline(cin, other_name))
                {
                     if (other_name == ""){
                        cout << "Enter the second species (string): " << endl;
                    }
                    else {
                        break;
                    }
                }
                other_name = graph->editFormat(other_name);
                graph->optionThree(species_name, other_name);
                break;
        default: cout << "Invalid input!" << endl;
                break;
        
    }

    delete graph;
    return 0;
}