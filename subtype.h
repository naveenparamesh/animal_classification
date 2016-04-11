#include <string>
using namespace std;

class Subtype{
  public:
    string name;
    Subtype* nextSubtype;
    Subtype(string name, Subtype* nextSubtype);
  private:
    
};