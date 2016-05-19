#include "Product.h"
using namespace std;

Product::Product(ifstream &in){
  string line;
  getline(in, line);
  istringstream readTemp;
  readTemp.str(line);
  getline(readTemp, name, ';');
  DeleteWhitespace(name);
  readTemp >> cost;
}

string Product::getName() const {
  return name;
}

float Product::getCost() const {
  return cost;
}

ostream& operator<<(ostream& out, const Product & prod){
    out << prod.getName() << " || Costs " << prod.getCost();
    return out;
}


bool operator<(const Product &prod1, const Product &prod2){
    string prod1Name = prod1.getName();
    string prod2Name = prod2.getName();
    if(prod1Name < prod2Name)
        return true;
    return false;
}
