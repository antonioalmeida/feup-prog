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

  //<string,int> map - Each client's name to its position on the clients vector
  for(int counter = 0; counter < numberOfClients; counter++){
    clientIdx[clientsVector.at(counter).getName()] = counter;
  }

  //<string,int> map - Each product's name to its position on the products vector
  for(int counter = 0; counter < numberOfProducts; counter++){
    productIdx[productsVector.at(counter).getName()] = counter;
  }

  //<int,int> multimap - Each client's ID to each of his transactions' position on the transactions vector

  // COMPLETAR
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
        cout << "Name: " << clientsVectorTemp.at(index).getName() << " ; ID: " << clientsVectorTemp.at(index).getId() << endl;
}

void VendeMaisMais::showSpecificClient(string name) const {

    map<string,int>::const_iterator p = clientIdx.begin();
    for (p; p!=clientIdx.end(); p++) {

     if(p->first == name)
        break;
    }

    cout << clientsVector.at(p->second);
}

void VendeMaisMais::listProductsAlphabetically() const {

    vector<Product> productsVectorTemp = productsVector;

    sort(productsVectorTemp.begin(), productsVectorTemp.end());

    int numberOfProducts = productsVectorTemp.size();

    for(int index = 0; index < numberOfProducts; index++)
        cout << productsVectorTemp.at(index).getName() << endl;
}

void VendeMaisMais::editSpecificClient(string name) {
    
    //Search for client
    map<string,int>::const_iterator p = clientIdx.begin();
    for (p; p!=clientIdx.end(); p++) {
        
        if(p->first == name)
            break;
    }
    
    cout << "The client's current name is " << clientsVector.at(p->second).getName() << ", would you like to change it? (yes or no) ";
    
    //Verify and save answer
    string answer = readYesNo();
    
    if(answer == "yes") {
        cout << "What is the client's new name? : ";
        string newName;
        getline(cin, newName);
        DeleteWhitespace(newName);
        
        //Change name
        clientsVector.at(p->second).changeClientName(newName);
        //supermercado.changesMade();
    }
    
    
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


