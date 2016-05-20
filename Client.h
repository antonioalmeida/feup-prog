#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <climits>
#include <iomanip>

#include "Date.h"
#include "utils.h"

using namespace std;


class Client {
private:
  unsigned int id;
  string name;
  Date joinDate;
  float shopVolume;

public:
  Client(ifstream &in);
  Client(string name, Date joinDate);
  string getName() const;
  unsigned int getId() const;
  float getShopVolume() const;
  Date getJoinDate() const;
  void changeClientName(string newName);
  void changeClientJoinDate(Date newDate);
  void updateShopVolume(float sum);
  void changeClientId(unsigned int newId);
  void save(ofstream &out) const;
  friend ostream& operator<<(ostream &out, const Client &cli);
  friend bool operator<(const Client &cli1, const Client &cli2);
};
