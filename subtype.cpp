#include "subtype.h"

Subtype::Subtype(string name, Subtype* nextSubtype){
    this->name = name;
    this->nextSubtype = nextSubtype;
}