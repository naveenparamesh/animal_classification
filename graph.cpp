#include "graph.h"

Graph::Graph(string file){
    ifstream infile(file.c_str());
    
    while(infile){
        string s = "";
        if(!getline(infile, s)) break;
        storeInfoInGraph(s);
    }
}

int Graph::getIndex(string name){
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
       for(Species* sType = subclasses.at(v)->next; sType != NULL; sType = sType->next){
           cout << " --> " << sType->name;
       }
       cout << endl;
   } 
}

//THIS FUNCTION IS NOT USED AS OF RIGHT NOW
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

void Graph::storeInfoInGraph(string fileLine){
	istringstream ss(fileLine);
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
 	
 	int speciesIndex = getIndex(species);
 	if(speciesIndex == -1){ //not found within graph so far, so add it
 	    subclasses.push_back(new Species(species, NULL));
 	    speciesIndex = subclasses.size() - 1;
 	}
 	
 	for(int i = 0; i < subtypes.size(); i++){
 	    subclasses.at(speciesIndex)->next = new Species(subtypes.at(i), subclasses.at(speciesIndex)->next);
 	}
 	
}

void Graph::optionOne(int num_subtypes, string sp, int order){
   cout << num_subtypes << " subtypes of " << sp << " of order " << order << " are: " << endl;
   queue<Species*> my_queue;
   int num_results = 0;
   int indexOfSource = getIndex(sp);
   Species* source;
   if(indexOfSource != -1){
       source = subclasses.at(indexOfSource);
   }
   else{//has no subtypes
       cout << "Has no subtypes" << endl;
       return;
   }
   
   source->distance = 0;
   my_queue.push(source);
   
   while(!my_queue.empty()){
       Species* u = my_queue.front(); //dequeue's the species in the front of the line
       my_queue.pop();
        if(num_results >= num_subtypes){
            break; //breaks out of while so it can print the results
        }
        //process u here
         if(u->distance == order){//if it reached the given order
            cout << u->name << endl;
            num_results++;
         }
       int indexOfSpecies = getIndex(u->name);
       if(indexOfSpecies != -1){//meaning that species has subclasses
        Species* start = subclasses.at(indexOfSpecies)->next;
         for(Species* v = start; v != NULL; v = v->next){
            //process edge (u, v) here
                v->distance = u->distance + 1;
                my_queue.push(v);
         }
       }
       //u->state = "processed";
   }//end of while loop
}

void Graph::optionTwo(string sp){
    queue<Species*> my_queue;
    int num_subSpecies = 0;
    int indexOfSource = getIndex(sp);
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
       int indexOfSpecies = getIndex(u->name);
       if(indexOfSpecies != -1){//only proceed if it has a subclass
           Species* start = subclasses.at(indexOfSpecies)->next;
           for(Species* s = start; s != NULL; s = s->next){
            num_subSpecies++;
            my_queue.push(s);
           }
       }
    }
    
    cout << "The number is Subspecies for " << sp << " is: " << num_subSpecies << endl;
}

void Graph::optionThree(string sp1, string sp2, string sp3){
    queue<Species*> my_queue;
    vector<Species*> sp2ANDsp3;
    int indexOfSource = getIndex(sp1);
    Species* source;
    if(indexOfSource != -1){
        source = subclasses.at(indexOfSource);
        source->distance = 0;
        source->visited = false;
    }
    else{//has no subtypes
        cout << "Has no subtypes" << endl;
        return;
    }
    my_queue.push(source);
    while(!my_queue.empty() && sp2ANDsp3.size() < 2){ // exit if queue is empty, or if both sp2 & sp3 are set, cuz no need for more traversal
       Species* u = my_queue.front(); //dequeue's the species in the front of the line
       my_queue.pop();
      if(u->name == sp2){
          sp2ANDsp3.push_back(u);
      }
      if(u->name == sp3){
          sp2ANDsp3.push_back(u);
      }
       int indexOfSpecies = getIndex(u->name);
       if(indexOfSpecies != -1){//only proceed if it has a subclass
           Species* start = subclasses.at(indexOfSpecies)->next;
           for(Species* s = start; s != NULL; s = s->next){
                 s->distance = u->distance + 1;
                 s->parent = u;
                 s->visited = false;
                
                my_queue.push(s);
           }
       }
    }
    if(sp2ANDsp3.size() < 2){ // meant that sp1 was lower in the heirachy than either sp2 or sp3 or both
        cout << "Sorry, next time make sure SP1 is higher up in the classification heirachy than SP2 and SP3" << endl;
        return;
    }
    bool lca_found = false;
    //sp2ANDsp3.at(0) = sp2ANDsp3.at(0)->parent;
    //cout << "That line actually passed" << endl;
    //cout << "sp2's parent is: " << sp2ANDsp3.at(0)->name << endl;
    while(!lca_found){
        if(sp2ANDsp3.at(0)->name != source->name){
            sp2ANDsp3.at(0)->visited = true;
            sp2ANDsp3.at(0) = sp2ANDsp3.at(0)->parent;    
        }
        if(sp2ANDsp3.at(1)->name != source->name){
            sp2ANDsp3.at(1)->visited = true;
            
            sp2ANDsp3.at(1) = sp2ANDsp3.at(1)->parent;    
        }
        if(sp2ANDsp3.at(0)->visited){//this is lca
            lca_found = true;
            cout << "Lowest Common Ancestor is: " << sp2ANDsp3.at(0)->name << endl;
        }
        else if(sp2ANDsp3.at(1)->visited){
            lca_found = true;
            cout << "Lowest Common Ancestor is: " << sp2ANDsp3.at(1)->name << endl;
        }
        else if(sp2ANDsp3.at(0)->name == sp2ANDsp3.at(1)->name){
            lca_found = true;
            cout << "Lowest Common Ancestor is: " << sp2ANDsp3.at(0)->name << endl;
        }
        
    }
    
    
    
    
}
