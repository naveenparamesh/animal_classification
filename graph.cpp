#include "graph.h"

// graph constructor takes in the file name and reads each line of the file
// into a string s using a input file stream. Then the line of each file gets 
// passed to the function storeInfoInGraph so that it can dissect each line and 
// get the species and subspecies properly and store them in the graph
// so that in the end the graph can represent a structure such of an adjaceny linked list
Graph::Graph(string file){
    ifstream infile(file.c_str());
    
    while(infile){
        string s = "";
        if(!getline(infile, s)) break;
        storeInfoInGraph(s);
    }
}

// since each species is the head of the linked list in each index of the vector,
// this function goes through each index checking if the given species name is actually
// contained within the vector, if it is, it returns the index at which the species is located in the vector
// else it just returns -1 indicating its not located in the vector at all
int Graph::getIndex(string name){
    for(int v = 0; v < subclasses.size(); v++){
        if (subclasses.at(v)->name == name){
            return v;
        }
    }
    return -1;
}

// this function was only used in the developmental stages and was used to test whether
// the graph was correctly formed
void Graph::print(){
 for(int v = 0; v < subclasses.size(); v++){
       cout << subclasses.at(v)->name; // list the species name
       for(Species* sType = subclasses.at(v)->next; sType != NULL; sType = sType->next){
           cout << " --> " << sType->name;
       }
       cout << endl;
   } 
}

// This function takes in a string and returns a string that is modified
// meaning "RED ApPLE" becomes "red_apple" because every letter is lower cased
// and every space is replaced with an underscore
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

// this function is the bulk of how information is stored in the graph, using the underlying 
// adjaceny linked list data structure(formed using a vector and the species class)
// it takes in a line from a file, and iterates through it using an input string stream variable
// the istringstream variable iterates through recording characters until the given delimeter
// is given such as ":" or ";" and then stores the recorded characters into s, which then get used to store
// the species and even the subtypes. Later using this data the species and subtypes are added to the graph
void Graph::storeInfoInGraph(string fileLine){
	istringstream ss(fileLine);
 	string species = "";
 	vector<string> subtypes; // holds subtype of each species
 	
 	while(ss){ // while there is still more to read from the line
 		string s = "";
 		
 		if(getline(ss, s, ':')){ // gets the species name basically and store in s
 			s = editFormat(s); // properly formats it
	 		species = s; // sets to species
	 		s = "" ; // clears s for later use
 		}
 		while(true){
	 		if(!getline(ss, s, ',')) break; // if there is no more to read from the file exit the loop	
	 		s = s.substr(1); // strips begining whitespace so " apples" becomes "apples"
	 		s = editFormat(s);
		 	subtypes.push_back(s); // adds a subtype of the species is added to this list 
		 	s = "";
 		}
 	}
 	
 	int speciesIndex = getIndex(species); // gets the index of the species in the vector
 	if(speciesIndex == -1){ //not found within graph so far, so add it
 	    subclasses.push_back(new Species(species, NULL)); // adds this species, setting the rest of the linked list to null
 	    speciesIndex = subclasses.size() - 1; // sets the variable keeping track of where its gets added for later use
 	}
 	
 	// iterates through list of subtypes and adds each subtype onto the front of the linked list
 	// in that index of the vector. So basically it adds a new species(subspecies) in front of the species(head node)
 	// and sets this new species'(that was just added) next attribute to point to whatever the head node (the species itself) was pointing to
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
