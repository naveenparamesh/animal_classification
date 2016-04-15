#include "species.h"

Species::Species(string name, Species* next){
    this->name = name;
    this->next = next;
}
