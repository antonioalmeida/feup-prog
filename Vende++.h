#pragma once

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <climits>


#include "defs.h"
#include "Date.h"
#include "Client.h"
#include "Transaction.h"
#include "Product.h"
#include "utils.h"


//using namespace std;

class VendeMaisMais{
 private:
  string storeName;
  string clientsFile, productsFile, transactionsFile;
  bool transactionsAltered;
  bool clientsAltered;
  unsigned int maxClientID;
  vector<Client> clientsVector;
  vector<Product> productsVector;
  vector<Transaction> transactionsVector;
  map<string, int> clientIdx;
  map<string, int> productIdx;
  multimap<int, int> transactionIdx;

 public:
  VendeMaisMais(string store, string clientsFileName, string productsFileName, string transactionsFileName);
  string getStoreName() const;
  void listClientsAlphabetically() const;
  void listProductsAlphabetically() const;
  void showSpecificClient(string name) const;
  void editSpecificClient(string name);
  void saveChanges() const;

  friend ostream& operator<<(ostream &out, const VendeMaisMais &supermercado);
  friend string readClientName(const VendeMaisMais &supermercado); //Loops until a valid client name is read
};
