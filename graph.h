#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "species.h"

using namespace std;

class Graph{
  
    public:
        // this vector holds a species in each bucket and each species 
        // has a pointer to a subtype, and each subtype has a pointer to another
        // subtype, thus its basically a adjacency linked list in each bucket 
        // of the vector
        vector<Species*> subclasses; 
        Graph(string file);
        int indexForName(string name);
        void print();
        string editFormat(string s);
        void storeInfoInGraph(string theString);
        
    
    private:
    
};
