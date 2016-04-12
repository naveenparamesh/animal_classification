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
       for(Species* sType = subclasses.at(v)->subtype; sType != NULL; sType = sType->subtype){
           cout << " --> " << sType->name;
       }
       cout << endl;
   } 
}

void Graph::printResults(vector<Species*> results){
   
   for(int i = 0; i < results.size(); i++){
       cout << results.at(i)->name << endl;
   }
   cout << endl;
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
 	    subclasses.at(speciesIndex)->subtype = new Species(subtypes.at(i), subclasses.at(speciesIndex)->subtype);
 	}
 	
}

void Graph::optionOne(int num_subtypes, string sp, int order){
    queue<Species*> my_queue;
    vector<Species*> results;
    for(int v = 0; v < subclasses.size(); v++){
        subclasses.at(v)->state = "undiscovered";
        subclasses.at(v)->parent = NULL;
       for(Species* sType = subclasses.at(v)->subtype; sType != NULL; sType = sType->subtype){
            sType->state = "undiscovered";
            sType->parent = NULL;
       }
   }
   int indexOfSource = indexForName(sp);
   Species* source;
   if(indexOfSource != -1){
       source = subclasses.at(indexOfSource);
   }
   else{//has no subtypes
       cout << "Has no subtypes" << endl;
       return;
   }
   
   source->state = "discovered";
   source->distance = 0;
   my_queue.push(source);
   
   while(!my_queue.empty()){
       Species* u = my_queue.front(); //dequeue's the species in the front of the line
       my_queue.pop();
        if(results.size() >= num_subtypes){
            break; //breaks out of while so it can print the results
        }
        //process u here
         if(u->distance == order){//if it reached the given order
            results.push_back(u);
         }
       int indexOfSpecies = indexForName(u->name);
       if(indexOfSpecies != -1){//meaning that species has subclasses
        //cout << u ->name <<" distance is: " << u->distance << endl;
        Species* start = subclasses.at(indexOfSpecies)->subtype;
         for(Species* v = start; v != NULL; v = v->subtype){
            //process edge (u, v) here
            //cout << v->name << " is in line" << endl;
            if (v->state == "undiscovered"){
                v->state = "discovered";
                v->parent = u;
                v->distance = u->distance + 1;
                my_queue.push(v);
            }
         }
       }
       u->state = "processed";
   }//end of while loop
   
       
    //cout << "THE SIZE OF RESULTS IS: " << results.size() << endl;
    cout << num_subtypes << " subtypes of " << sp << " of order " << order << " are: " << endl;
    printResults(results);
}

void Graph::optionTwo(string sp){
    queue<Species*> my_queue;
    int indexOfSource = indexForName(sp);
    Species* source;
    if(indexOfSource != -1){
        source = subclasses.at(indexOfSource);
    }
    else{//has no subtypes
        cout << "Has no subtypes" << endl;
        return;
    }
    my_queue.push(source);
    while(!my_queue.empty()){
       Species* u = my_queue.front(); //dequeue's the species in the front of the line
       my_queue.pop();
       int indexOfSpecies = indexForName(u->name);
       if(indexOfSpecies != -1){//only proceed if it has a subclass
           Species* start = subclasses.at(indexOfSpecies)->subtype;
           for(Species* s = start; s != NULL; s = s->subtype){
            cout << s->name << endl;
            my_queue.push(s);
           }
       }
       
    }
}

void Graph::optionThree(string firstSpecies, string secondSpecies){
    
}


