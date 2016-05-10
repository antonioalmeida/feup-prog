#pragma once

#include "Transaction.h"
#include "utils.h"

Transaction::Transaction(ifstream &in) {
    string line;
    string productTemp; //To store each product bought on a transaction before inserting it in the vector
    getline(in, line);
    istringstream readTemp;
    readTemp.str(line);
    readTemp >> clientId;
    readTemp.ignore(numeric_limits<int>::max(),';');
    getline(readTemp,line,';');
    DeleteWhitespace(line);
    dateOfTransaction = Date(line);
    while(getline(readTemp, line, ',')) {
        DeleteWhitespace(line);
        productsBought.push_back(line);
    }
}

unsigned int Transaction::getClientId() const {
  return clientId;
}


Date Transaction::getDateOfTransaction() const {
    return dateOfTransaction;
}

vector<string> Transaction::getProductsBought() const {
    return productsBought;
}

void Transaction::save(ofstream &out) const {
    out << clientId << " ; ";
    dateOfTransaction.save(out);
    out << " ; ";
    int amountOfProducts = productsBought.size();
    for(int index = 0; index < amountOfProducts; index++) {
            out << productsBought.at(index);
            if(amountOfProducts > 1) { //If there is only one product, commas are not necessary
                    if (index != amountOfProducts - 1) //If index does not correspond to the last element
                        out << ", ";
            }
        out << endl;
    }
}

ostream& operator<<(ostream& out, const Transaction &trans) {
    out << "ID Nr." << trans.getClientId() << " on " << trans.getDateOfTransaction() << " bought ";
    for (int index = 0; index < trans.getProductsBought().size(); index++) {
		out << trans.getProductsBought().at(index);
						/*Logical test: If there are more than 2 products left to show, after the first one is shown a comma is inserted.
						If there are 2 products left, an 'and' is inserted. However, this is only done if there is more than one product.
						If there is only one product, nothing is added after such product*/
						if(trans.getProductsBought().size() > 1) {
                            if (index < trans.getProductsBought().size() - 2)
                                out << ", ";
                            else if (index == trans.getProductsBought().size() - 2)
                                out << " and ";
                        }
    }
    return out;
}
