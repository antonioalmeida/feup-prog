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

void Client::save(ofstream &out) const {
    out << id << " ; " << name << " ; " << shopVolume << endl;
}

ostream& operator<<(ostream& out, const Client &cli) {
  out << "ID Nr." << cli.id << " is named " << cli.name << ", joined on " << cli.joinDate << " and spent a total amount of " << cli.shopVolume << endl;
}


bool operator<(const Client &cli1, const Client &cli2) { //NOTE: Returns true if cli1 is "inferior" to cli2 in the name, aka if his name comes first alphabetically
  string nameCli1 = cli1.getName();
  string nameCli2 = cli2.getName();
  int cli1NameSize = nameCli1.length();
  int cli2NameSize = nameCli2.length();
  int maxNameLength;
  if(cli1NameSize > cli2NameSize)
    maxNameLength = cli1NameSize;
  else
    maxNameLength = cli2NameSize;

  for(int index = 0; index < maxNameLength; index++){
    if(nameCli1.at(index) < nameCli2.at(index))
        return true;
  }
  return false; //If loop is completed, the name does not come first alphabetically
}
