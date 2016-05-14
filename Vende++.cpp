
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
  unsigned int numberOfProducts;
  productsRead >> numberOfProducts;
  unsigned int numberOfTransactions;
  transactionsRead >> numberOfTransactions;

  clientsRead.ignore(numeric_limits<int>::max(), '\n');
  for(int counter = 0; counter < numberOfClients; counter++) {
	Client c1 = Client(clientsRead);
    clientsVector.push_back(c1);
  }


  productsRead.ignore(numeric_limits<int>::max(), '\n');
  for(int counter = 0; counter < numberOfProducts; counter++) {
    Product p1 = Product(productsRead);
    productsVector.push_back(p1);
  }


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
    clientIdx.insert(pair<string,int>(clientsVector.at(counter).getName(), counter));
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

        //Change altered boolean to save changes
        clientsAltered = true;
    }

    cout << "The client's current join date is " << clientsVector.at(p->second).getJoinDate() << ", would you like to change it? (yes or no) ";

    //Verify and save answer
    answer = readYesNo();

    if(answer == "yes") {
        
        string newDate;
        Date newDateClass;
        bool exit = false;
        
        do {
            cout << "What is the client's new join date? (DD/MM/YYYY) : ";
            getline(cin, newDate);
            DeleteWhitespace(newDate);

            //Create temporary date
            Date newDateClass(newDate);
            
            exit = newDateClass.verifyDate();
            
            if(exit) //Change date in vector
                clientsVector.at(p->second).changeClientJoinDate(newDateClass);
            
        } while(!exit);
        
        //Change altered boolean to save changes
        clientsAltered = true;
    }

}

void VendeMaisMais::addClient(Client newClient) {

    //Set client's Id
    newClient.changeClientId(maxClientID+1);
    maxClientID++;

    //Add client to clientsVector
    clientsVector.push_back(newClient);

    //Add client to map
    clientIdx.insert(pair<string, int>(newClient.getName(), clientsVector.size()-1));

    //Update maxClientID
    maxClientID++;
}

void VendeMaisMais::removeSpecificClient(string name) {

    //Search for client
    map<string,int>::const_iterator p = clientIdx.find(name);

    //Remove in vector
    clientsVector.erase(clientsVector.begin() + p->second);

    clientIdx.clear();

    //Change index in map
    //<string,int> map - Each product's name to its position on the products vector
    for( int counter = 0 ; counter < clientsVector.size() ; counter++){

        clientIdx.insert(pair<string,int>(clientsVector.at(counter).getName(), counter));
    }
}


void VendeMaisMais::addTransaction() {
    vector<int> idVector;
    for(int index = 0; index < clientsVector.size(); index++)
        idVector.push_back(clientsVector.at(index).getId());
    Transaction newTransaction = Transaction(idVector,productIdx);
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

    //Loop to update client's shopping volume
    for(int index = 0; index < clientsVector.size(); index++){
        if(clientsVector.at(index).getId() == newTranId){
            clientsVector.at(index).updateShopVolume(sum);
            break;
        }
    }
    clientsAltered = true;

    //Update transaction multimap
    int newTranIndex = transactionsVector.size() - 1;
    transactionIdx.insert(pair<int,int>(newTranId, newTranIndex));
}

void VendeMaisMais::showTransactionsBetweenDates() const {
    cin.ignore(numeric_limits<int>::max(),'\n');
    string date1, date2;
    cout << "Insert the date corresponding to the period beginning: ";
    getline(cin, date1);
    Date d1 = Date(date1);
    cout << "Insert the date corresponding to the period end: ";
    getline(cin, date2);
    Date d2 = Date(date2);

    cout << "Transactions made between " << d1 << " and " << d2 << " (including themselves):" << endl;
    for(int index = 0; index < transactionsVector.size(); index++){
        if(transactionsVector.at(index).getDateOfTransaction() >= d1 && transactionsVector.at(index).getDateOfTransaction() <= d2)
            cout << transactionsVector.at(index) << endl;
    }
}

void VendeMaisMais::showTransactionsOnDate() const {
    cin.ignore(numeric_limits<int>::max(),'\n');
    string date;
    cout << "Insert the date intended: ";
    getline(cin, date);
    Date d1 = Date(date);

    cout << "Transactions made on " << d1 << ":" << endl;
    for(int mainindex = 0; mainindex < transactionsVector.size(); mainindex++){
        if(transactionsVector.at(mainindex).getDateOfTransaction() == d1){
            cout << "ID Nr." << transactionsVector.at(mainindex).getClientId() << " bought ";
            for (int secondaryindex = 0; secondaryindex < transactionsVector.at(mainindex).getProductsBought().size(); secondaryindex++) {
                cout << transactionsVector.at(mainindex).getProductsBought().at(secondaryindex);
                /*Logical test: If there are more than 2 products left to show, after the first one is shown a comma is inserted.
                If there are 2 products left, an 'and' is inserted. However, this is only done if there is more than one product.
                If there is only one product, nothing is added after such product*/
				if(transactionsVector.at(mainindex).getProductsBought().size() > 1) {
                    if (secondaryindex < transactionsVector.at(mainindex).getProductsBought().size() - 2)
                        cout << ", ";
                    else if (secondaryindex == transactionsVector.at(mainindex).getProductsBought().size() - 2)
                        cout << " and ";
                    }
            }
            cout << endl;
        }
    }
}

void VendeMaisMais::showAllTransactions() const {
    cout << "All transactions made in supermarket " << storeName << ":" << endl;
    for(int index = 0; index < transactionsVector.size(); index++)
        cout << transactionsVector.at(index) << endl;
}

void VendeMaisMais::showClientTransactions(string name) const {
    map<string,int>::const_iterator name_it = clientIdx.find(name); //returns iterator pointing to client's index in clients vector
    unsigned int cliUniqueId = clientsVector.at(name_it->second).getId(); //returns client's unique ID
    showClientTransactions(cliUniqueId);
}

void VendeMaisMais::showClientTransactions(unsigned int cliUniqueId) const {
    vector<Transaction> clientTransactionsTemp;
    multimap<int,int>::const_iterator id_it = transactionIdx.begin();
    for(id_it; id_it != transactionIdx.end(); id_it++){
        if(id_it->first == cliUniqueId)
            clientTransactionsTemp.push_back(transactionsVector.at(id_it->second)); //If ID matches client ID, push transaction with index pointed by id_it
    }

    //Sorting vector according to comparison function defined in utils header
    sort(clientTransactionsTemp.begin(), clientTransactionsTemp.end(), compareTrans);

    for(int index = 0; index < clientTransactionsTemp.size(); index++)
        cout << clientTransactionsTemp.at(index) << endl;
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

//Print supermarket
ostream& operator<<(ostream &out, const VendeMaisMais &supermarket){
	out << "supermarket " << supermarket.getStoreName() << endl << "Conta atualmente com:" << endl << supermarket.clientsVector.size() << " clientes" << endl << supermarket.productsVector.size() << " produtos no stock" << endl << supermarket.transactionsVector.size() << "transacoes realizadas, num valor total de " << totalAmountSpent(supermarket) << endl;

    return out;
}

string readClientName(const VendeMaisMais &supermarket) {
    string clientName;
    bool nameExists = false;
    int numberOfClients = supermarket.clientsVector.size();
    do{
        getline(cin, clientName);
        for(int index = 0; index < numberOfClients; index++){
            if(supermarket.clientsVector.at(index).getName() == clientName){
                nameExists = true;
                break;
            }
        }
    if(!nameExists)
        cout << "ERROR: Client not found, please insert a valid name: ";
    }while(!nameExists);

    return clientName;
}

unsigned int readClientId(const VendeMaisMais &supermarket) {
    unsigned int customerId;
    multimap<int,int>::const_iterator id_it;
    cout << "Insert the client's ID: ";
    do{
        cin >> customerId;
        id_it = supermarket.transactionIdx.find(customerId);
        if(id_it == supermarket.transactionIdx.end()) //Means that ID was not found
            cout << "ERROR: Invalid client ID, please insert a valid value: ";
    }while(id_it == supermarket.transactionIdx.end());

    return customerId;
}

float totalAmountSpent(const VendeMaisMais &supermarket) {
    float sum = 0;
    /*for(int mainindex = 0; mainindex < supermarket.transactionsVector.size(); mainindex++){
        for(int secondaryindex = 0; secondaryindex < supermarket.transactionsVector.at(mainindex).getProductsBought().size(); secondaryindex++){
            int currentProductIndex = (supermarket.productIdx.find(supermarket.transactionsVector.at(mainindex).getProductsBought().at(secondaryindex)))->second;
            float currentProductCost = supermarket.productsVector.at(currentProductIndex).getCost();
            sum = sum + currentProductCost;
        }
    }*/

    return sum;
}

void VendeMaisMais::showBottom10() const {
    //Needs implementation
}
