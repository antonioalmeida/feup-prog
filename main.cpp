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

  cout << endl << "Initial statistics on '" << store << "' on Sell++ platform:" << endl;
  cout << supermarket << endl;
  pressToContinue();
  mainOption(supermarket);
  cout << endl << endl << "Final statistics on '" << store << "' on Sell++ platform:" << endl;
  cout << supermarket << endl;
  cout << "See you soon!" << endl;
  return 0;

}
