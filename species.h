#include "subtype.h"
#include <string>
class Species{
  public:
    string name;
    Subtype* subtypeList;
    Species(string name, Subtype* subtypeList);
  private:
    
};