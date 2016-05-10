#pragma once


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


using namespace std;



class Product {
 private:
  string name;
  float cost;


 public:
  Product(ifstream &in);
  string getName() const;
  float getCost() const;
  int ProductIndex(string nome); // uso do map para "traduzir" o nome em indice no vetor de produtos
  friend ostream& operator<<(ostream& out, const Product &prod);
  friend bool operator<(const Product &prod1, const Product &prod2);
};