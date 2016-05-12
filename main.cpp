#include <iostream>
#include <string>
#include <vector>

#include "Vende++.h"
#include "Menus.h"
#include "utils.h"

int main(){
  string store, clientsFileName, productsFileName, transactionsFileName;

  bool validState = initialInformation(store, clientsFileName, productsFileName, transactionsFileName);
  if(!validState)
    return -1;

  VendeMaisMais supermarket(store, clientsFileName, productsFileName, transactionsFileName);

  cout << "Informacao da loja '" << store << " do supermarket Vende++:" << endl;
  cout << supermarket << endl;
  mainOption(supermarket);
  return 0;
}
