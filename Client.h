#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <climits>

#include "utils.h"
#include "Date.h"

using namespace std;


class Client {
 private:
  unsigned int id;
  string name;
  Date joinDate;
  float shopVolume;

 public:
  Client(ifstream &in);
  string getName() const;
  unsigned int getId() const;
  float getShopVolume() const;
  Date getJoinDate() const;
  void changeClientName(string newName);
  void changeClientJoinDate(Date newDate);
  void updateShopVolume(float sum);
  void save(ofstream &out) const;
  friend ostream& operator<<(ostream &out, const Client &cli);
  friend bool operator<(const Client &cli1, const Client &cli2);
};
