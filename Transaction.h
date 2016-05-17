#pragma once


#include <iostream>
#include <iomanip>
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
  Transaction(const vector<int> &idVec, const map<string, int> &productMaping); //Structures called to make sure given ID and each product name are valid
  unsigned int getClientId() const;
  Date getDateOfTransaction() const;
  vector<string> getProductsBought() const;
  void save(ofstream &out) const;
  friend ostream& operator<<(ostream &out, const Transaction &trans);
};
