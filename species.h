#include <string>

using namespace std;
class Species{
  public:
    string name;
    Species* subtype;
    Species* parent;
    int distance; // to node 
    string state;
    Species(string name, Species* subtype);
  private:
    
};