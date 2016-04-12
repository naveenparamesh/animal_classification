#include "species.h"

Species::Species(string name, Species* subtype){
    this->name = name;
    this->subtype = subtype;
}
