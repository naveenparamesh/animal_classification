#include <string>

using namespace std;
class Species{
  public:
    string name;
    Species* next;
    Species* parent;
    bool visited;
    int distance; // to node 
    string state;// discovered/ undiscovered
    Species(string name, Species* next);
  private:
    
};