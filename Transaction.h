#pragma once


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <climits>
#include <map>

#include "Date.h"



using namespace std;


class Transaction {
 private:
  unsigned int clientId;
  Date dateOfTransaction;
  vector<string> productsBought;

 public:
  Transaction(ifstream &in);
  Transaction(const multimap<int, int> &transactionMaping, const map<string, int> &productMaping); //Map and multimap are called to make sure given ID and each product name is valid
  unsigned int getClientId() const;
  Date getDateOfTransaction() const;
  vector<string> getProductsBought() const;
  void save(ofstream &out) const;
  friend ostream& operator<<(ostream &out, const Transaction &trans);
};
