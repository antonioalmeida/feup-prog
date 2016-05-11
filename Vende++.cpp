#include "Vende++.h"


VendeMaisMais::VendeMaisMais(string store, string clientsFileName, string productsFileName, string transactionsFileName){
  storeName = store;
  clientsFile = clientsFileName;
  productsFile = productsFileName;
  transactionsFile = transactionsFileName;
  transactionsAltered = false;
  clientsAltered = false;
  ifstream clientsRead, productsRead, transactionsRead;
  clientsRead.open(clientsFile);
  productsRead.open(productsFile);
  transactionsRead.open(transactionsFile);

  unsigned int numberOfClients;
  clientsRead >> numberOfClients;
  clientsRead.ignore(numeric_limits<int>::max(), '\n');
  for(int counter = 0; counter < numberOfClients; counter++) {
    Client c1 = Client(clientsRead);
    clientsVector.push_back(c1);
  }

  unsigned int numberOfProducts;
  productsRead >> numberOfProducts;
  productsRead.ignore(numeric_limits<int>::max(), '\n');
  for(int counter = 0; counter < numberOfProducts; counter++) {
    Product p1 = Product(productsRead);
    productsVector.push_back(p1);
  }

  unsigned int numberOfTransactions;
  transactionsRead >> numberOfTransactions;
  transactionsRead.ignore(numeric_limits<int>::max(), '\n');
  for(int counter = 0; counter < numberOfTransactions; counter++) {
    Transaction t1 = Transaction(transactionsRead);
    transactionsVector.push_back(t1);
  }

  clientsRead.close();
  productsRead.close();
  transactionsRead.close();

  int lastElement = clientsVector.size() - 1;

  maxClientID = clientsVector.at(lastElement).getId();

  //<string,int> map - Each client's name to its position on the clients vector
  for(int counter = 0; counter < numberOfClients; counter++){
    clientIdx[clientsVector.at(counter).getName()] = counter;
  }

  //<string,int> map - Each product's name to its position on the products vector
  for(int counter = 0; counter < numberOfProducts; counter++){
    productIdx.insert(pair<string,int>(productsVector.at(counter).getName(), counter));
  }

  //<int,int> multimap - Each client's ID to each of his transactions' position on the transactions vector
  for(int maincounter = 0; maincounter < numberOfClients; maincounter++){
    for(int secondarycounter = 0; secondarycounter < numberOfTransactions; secondarycounter++){
        if(clientsVector.at(maincounter).getId() == transactionsVector.at(secondarycounter).getClientId()) //If current transaction is from the client treated in the current iteration
            transactionIdx.insert(pair<int,int>(clientsVector.at(maincounter).getId(),secondarycounter));
    }
  }
}

string VendeMaisMais::getStoreName() const {
    return storeName;
}

void VendeMaisMais::listClientsAlphabetically() const {

    vector<Client> clientsVectorTemp = clientsVector;

    sort(clientsVectorTemp.begin(), clientsVectorTemp.end());

    int numberOfClients = clientsVectorTemp.size();

    cout << endl << "Showing Clients Alphabetically" << endl << endl;

    for(int index = 0; index < numberOfClients; index++)
        //cout << "- " << clientsVectorTemp.at(index).getName() << " ; ID: " << clientsVectorTemp.at(index).getId() << endl;
        cout << clientsVectorTemp.at(index) << endl;
}

void VendeMaisMais::showSpecificClient(string name) const {

    map<string,int>::const_iterator p = clientIdx.find(name);

    cout << clientsVector.at(p->second);
}

void VendeMaisMais::listProductsAlphabetically() const {

    vector<Product> productsVectorTemp = productsVector;

    sort(productsVectorTemp.begin(), productsVectorTemp.end());

    int numberOfProducts = productsVectorTemp.size();

    for(int index = 0; index < numberOfProducts; index++)
        cout << "- " << productsVectorTemp.at(index).getName() << "/ Cost: " << productsVectorTemp.at(index).getCost() << endl;
}

void VendeMaisMais::editSpecificClient(string name) {

    //Search for client
    map<string,int>::const_iterator p = clientIdx.find(name);

    cout << "The client's current name is " << clientsVector.at(p->second).getName() << ", would you like to change it? (yes or no) ";

    //Verify and save answer
    string answer = readYesNo();

    if(answer == "yes") {
        cout << "What is the client's new name? : ";
        string newName;
        getline(cin, newName);
        DeleteWhitespace(newName);

        //Change name in vector
        clientsVector.at(p->second).changeClientName(newName);

        //Change name in map
        clientIdx.insert(p, pair<string,int>(newName, p->second));

        //supermercado.changesMade();
    }


}

void VendeMaisMais::addTransaction() {
    Transaction newTransaction = Transaction(transactionIdx,productIdx);
    transactionsVector.push_back(newTransaction);
    transactionsAltered = true;

    //Loop to update the client's total shopping volume
    unsigned int newTranId = newTransaction.getClientId();
    vector<string> newTranProd = newTransaction.getProductsBought();
    float sum = 0;
    for(int counter = 0; counter < newTranProd.size(); counter++){
        int currentProductIndex = productIdx.find(newTranProd.at(counter))->second;
        float currentProductCost = productsVector.at(currentProductIndex).getCost();
        sum = sum + currentProductCost;
    }

    for(int index = 0; index < clientsVector.size(); index++){
        if(clientsVector.at(index).getId() == newTranId){
            clientsVector.at(index).updateShopVolume(sum);
            break;
        }
    }
    clientsAltered = true;
}

void VendeMaisMais::saveChanges() const{
    if(clientsAltered){
        ofstream clientsWrite;
        clientsWrite.open(clientsFile);
        clientsWrite << clientsVector.size() << endl;
        for(int index = 0; index < clientsVector.size(); index++){
            clientsVector.at(index).save(clientsWrite);
        }
    }

    if(transactionsAltered){
        ofstream transactionsWrite;
        transactionsWrite.open(transactionsFile);
        transactionsWrite << transactionsVector.size() << endl;
        for(int index = 0; index < transactionsVector.size(); index++){
            transactionsVector.at(index).save(transactionsWrite);
        }
    }
}

ostream& operator<<(ostream &out, const VendeMaisMais &supermercado){
    out << "Supermercado " << supermercado.getStoreName() << endl << "Conta atualmente com:" << endl << supermercado.clientsVector.size() <<
    " clientes" << endl << supermercado.productsVector.size() << " produtos no stock" << endl << supermercado.transactionsVector.size() << "transacoes realizadas, num valor total de " << /*adicionar funcao para calcular valor total gasto? << */ endl;
    for(int index = 0; index < supermercado.clientsVector.size(); index++)
        out << supermercado.clientsVector.at(index) << endl;
    for(int index = 0; index < supermercado.productsVector.size(); index++)
        out << supermercado.productsVector.at(index) << endl;
    for(int index = 0; index < supermercado.transactionsVector.size(); index++)
        out << supermercado.transactionsVector.at(index) << endl;

    return out;
    //out.flush();
}

string readClientName(const VendeMaisMais &supermercado) {
    string clientName;
    bool nameExists = false;
    int numberOfClients = supermercado.clientsVector.size();
    do{
        getline(cin, clientName);
        for(int index = 0; index < numberOfClients; index++){
            if(supermercado.clientsVector.at(index).getName() == clientName){
                nameExists = true;
                break;
            }
        }
    if(!nameExists)
        cout << "ERROR: Client not found, please insert a valid name: ";
    }while(!nameExists);

    return clientName;
}


