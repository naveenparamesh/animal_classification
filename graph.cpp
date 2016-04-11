#include "graph.h"

Graph::Graph(string file){
    ifstream infile(file.c_str());
    
    while(infile){
        string s = "";
        if(!getline(infile, s)) break;
        storeInfoInGraph(s);
    }
    
    
}

int Graph::indexForName(string name){
    for(int v = 0; v < subclasses.size(); v++){
        if (subclasses.at(v)->name == name){
            return v;
        }
    }
    return -1;
}

void Graph::print(){
   for(int v = 0; v < subclasses.size(); v++){
       cout << subclasses.at(v)->name; // list the species name
       for(Subtype* sType = subclasses.at(v)->subtypeList; sType != NULL; sType = sType->nextSubtype){
           cout << " --> " << sType->name;
       }
       cout << endl;
   } 
}

string Graph::editFormat(string s){
	string result = "";
	for(int i = 0; i < s.length(); i++){
		if(s[i] ==  ' '){
			result += "_";
		}
		else {
			result += tolower(s[i]);	
		}
	}
	return result;
}

void Graph::storeInfoInGraph(string theString){
	istringstream ss(theString);
 	string species = "";
 	vector<string> subtypes;
 	
 	while(ss){
 		string s = "";
 		
 		if(getline(ss, s, ':')){
 			s = editFormat(s);
	 		species = s;
	 		s = "" ;
 		}
 		while(true){
	 		if(!getline(ss, s, ',')) break;		
	 		s = s.substr(1);
	 		s = editFormat(s);
		 	subtypes.push_back(s);
		 	s = "";
 		}
 	}
 	
 	int speciesIndex = indexForName(species);
 	if(speciesIndex == -1){ //not found within graph so far, so add it
 	    subclasses.push_back(new Species(species, NULL));
 	    speciesIndex = subclasses.size() - 1;
 	}
 	
 	for(int i = 0; i < subtypes.size(); i++){
 	    subclasses.at(speciesIndex)->subtypeList = new Subtype(subtypes.at(i), subclasses.at(speciesIndex)->subtypeList);
 	}
 	
}
