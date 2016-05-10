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

  VendeMaisMais supermercado(store, clientsFileName, productsFileName, transactionsFileName);

  cout << "Informacao da loja '" << store << " do supermercado Vende++:" << endl;
  cout << supermercado << endl;

  mainOption(supermercado);
  return 0;
}
