#pragma once

#include "Transaction.h"
#include "utils.h"

Transaction::Transaction(ifstream &in) {
    string line;
    string pline; //To store each product bought on a transaction before inserting it in the vector
    getline(in, line);
    istringstream readTemp;
    readTemp.str(line);
    readTemp >> clientId;
    readTemp.ignore(numeric_limits<int>::max(),';');
    getline(readTemp,line,';');
    DeleteWhitespace(line);
    dateOfTransaction = Date(line);
    while(getline(readTemp, pline, ',')) {
        DeleteWhitespace(pline);
        productsBought.push_back(pline);
    }
}

Transaction::Transaction(const vector<int> &idVec, const map<string, int> &productMaping) {
    //Reading ID of client who made the transaction
    unsigned int customerId;
    bool foundId;
    cout << "Insert the transaction's author's ID: ";
    do{
        foundId = false;
        cin >> customerId;
        for(int index = 0; index < idVec.size(); index++){
            if(idVec.at(index) == customerId){
                foundId = true;
                break;
            }
        }
        if(!foundId) //Means that ID was not found
            cout << "ERROR: Invalid client ID, please insert a valid value: ";
    }while(!foundId);

    clientId = customerId;

    //Reading transaction date
    cin.ignore(numeric_limits<int>::max(), '\n'); //Because of mixed use of cin and getline
    string newTransactionDate;
    cout << "Insert the transaction's date: ";
    getline(cin, newTransactionDate);
    DeleteWhitespace(newTransactionDate);
    dateOfTransaction = Date(newTransactionDate);

    //Reading products bought
    string newProduct;
    map<string,int>::const_iterator p_it;
    do{
        cout << "Insert a product bought (0 to finish): ";
        getline(cin, newProduct);
        DeleteWhitespace(newProduct);
        p_it = productMaping.find(newProduct);
        if(p_it == productMaping.end()) { //Means that product was not found
           if(newProduct != "0") //Invalid product inserted
                cout << "ERROR: Invalid product, please insert a valid product name" << endl;
        }
        else
            productsBought.push_back(newProduct);
    }while(newProduct != "0");
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
                    if (index != amountOfProducts - 1) //If current element is not the last, a comma is inserted
                        out << ", ";
            }
    }
    out << endl;
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
