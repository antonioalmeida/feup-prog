#include "Client.h"


Client::Client(ifstream &in) {
    string line;
    getline(in, line);
    istringstream readTemp;
    readTemp.str(line);
    readTemp >> id;
    readTemp.ignore(INT_MAX,';');
    getline(readTemp,name,';');
    DeleteWhitespace(name);
    getline(readTemp,line,';');
    joinDate = Date(line);
    readTemp >> shopVolume;
}


string Client::getName() const {
  return name;
}

unsigned int Client::getId() const {
  return id;
}

float Client::getShopVolume() const {
  return shopVolume;
}

Date Client::getJoinDate() const {
    return joinDate;
}

void Client::changeClientName(string newName) {
    name = newName;
}

void Client::save(ofstream &out) const {
    out << id << " ; " << name << " ; " << shopVolume << endl;
}

ostream& operator<<(ostream& out, const Client &cli) {
  out << "ID: " << cli.id << " ; Name: " << cli.name << " ; Joined on: " << cli.joinDate << " ; Total Spent: " << cli.shopVolume << endl;
    return out;
}


bool operator<(const Client &cli1, const Client &cli2) { //Returns true if cli1 is "inferior" to cli2 in the name, aka if his name comes first alphabetically
  string nameCli1 = cli1.getName();
  string nameCli2 = cli2.getName();
  if(nameCli1 < nameCli2)
    return true;
  else
    return false;
}
