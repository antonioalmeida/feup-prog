#include "Client.h"

Client::Client(ifstream &in) {
    string line;
    getline(in, line);
    istringstream readTemp;
    readTemp.str(line);
    readTemp >> id;
    readTemp.ignore(numeric_limits<int>::max(),';');
    getline(readTemp,name,';');
    DeleteWhitespace(name);
    getline(readTemp,line,';');
    joinDate = Date(line);
    readTemp >> shopVolume;
}

//Version to add clients in menu
Client::Client(string name, Date joinDate) {

    this->name = name;
    this->joinDate = joinDate;
    shopVolume = 0;
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

void Client::changeClientJoinDate(Date newDate) {
    joinDate = newDate;
}

void Client::updateShopVolume(float sum) {
    shopVolume = shopVolume + sum;
}

void Client::changeClientId(unsigned int newId) {
    id = newId;
}

void Client::save(ofstream &out) const {
    out << id << " ; " << name << " ; ";
    joinDate.save(out);
    out << " ; " << shopVolume << endl;
}

ostream& operator<<(ostream& out, const Client &cli) {
  //out << "ID: " << cli.id << " ; Name: " << cli.name << " ; Joined on: " << cli.joinDate << " ; Total Spent: " << cli.shopVolume << endl;
    
    out << setw(4) << cli.id;
    out << setw(22) << cli.name;
    out << setw(10) << cli.joinDate;
    out << setw(10) << cli.shopVolume;
    out << endl;
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
