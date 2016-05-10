#include "Product.h"


Product::Product(ifstream &in){
  string line;
  getline(in, line);
  istringstream readTemp;
  readTemp.str(line);
  getline(readTemp, name, ';');
  readTemp >> cost;
}

string Product::getName() const {
  return name;
}

float Product::getCost() const {
  return cost;
}

ostream& operator<<(ostream& out, const Product & prod){
    out << Product::getName() << " || Costs " << Product::getCost();
}


bool operator<(const Product &prod1, const Product &prod2){
  string prod1Name = prod1.getName();
  string prod2Name = prod2.getName();
  int prod1NameSize = prod1Name.length();
  int prod2NameSize = prod2Name.length();
  if(prod1NameSize > prod2NameSize)
    int maxNameSize = prod1NameSize;
  else
    int maxNameSize = prod2NameSize;

  for(int index = 0; index < maxNameSize; index++){
    if(prod1Name.at(index) < prod2Name.at(index))
        return true;
  }
  return false; //If end of loop is reached, prod1 name is not alphabetically inferior to prod2's name
}
