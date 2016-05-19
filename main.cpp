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

  cout << "Initial statistics on '" << store << "' from supermarket Vende++:" << endl;
  cout << supermarket << endl;
  mainOption(supermarket);
  cout << endl;
  cout << "Final statistics on '" << store << "' from supermarket Vende++:" << endl;
  cout << supermarket << endl;
  cout << "See you soon!" << endl;
  return 0;
    
}
