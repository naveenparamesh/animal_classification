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
    graph->print();
    
    //then do graph and method names, like find subspecies or whatever 
    // you're supposed to do
    
    
    delete graph;
    return 0;
}