#include <string>

using namespace std;
class Species{
  public:
    string name;
    Species* subtype;
    Species* parent;
    bool visited;
    int distance; // to node 
    string state;// discovered/ undiscovered
    Species(string name, Species* subtype);
  private:
    
};