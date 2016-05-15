
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
  for(int counter = 0; counter < numberOfTransactions; counter++){
    transactionIdx.insert(pair<int,int>(transactionsVector.at(counter).getClientId(),counter));
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

    cin.ignore(numeric_limits<int>::max(),'\n');
    pressToContinue();
}

void VendeMaisMais::showSpecificClient(string name) const {

    map<string,int>::const_iterator p = clientIdx.find(name);

    cout << clientsVector.at(p->second);

    cout << endl;

    pressToContinue();
}

void VendeMaisMais::listProductsAlphabetically() const {

    vector<Product> productsVectorTemp = productsVector;

    sort(productsVectorTemp.begin(), productsVectorTemp.end());

    int numberOfProducts = productsVectorTemp.size();

    cout << endl;

    cout << "Current available products:" << endl;

    for(int index = 0; index < numberOfProducts; index++)
        cout << "- " << productsVectorTemp.at(index).getName() << ", at a cost of " << productsVectorTemp.at(index).getCost() << endl;

    cin.ignore(numeric_limits<int>::max(),'\n');
    cout << endl;
    pressToContinue();
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

    cout << endl;
    cout << "Client successfully altered!" << endl;
    cout << endl;

    pressToContinue();

}

void VendeMaisMais::addClient(Client newClient) {

    //Set client's Id
    newClient.changeClientId(maxClientID+1);
    maxClientID++;

    //Add client to clientsVector
    clientsVector.push_back(newClient);

    //Add client to map
    clientIdx.insert(pair<string, int>(newClient.getName(), clientsVector.size()-1));

    cout << endl;
    cout << "Client successfully added!" << endl;
    cout << endl;
    pressToContinue();
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

    cout << "Client successfully removed!" << endl;
    cout << endl;
    pressToContinue();
}

void VendeMaisMais::showBottom10() const {
    //Needs implementation
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

    cout << endl;
    cout << "Transaction successfully added!" << endl;
    cout << endl;
    pressToContinue();
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

    cout << endl;
    pressToContinue();
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
    cout << endl;
    pressToContinue();
}

void VendeMaisMais::showAllTransactions() const {
    cout << "All transactions made in supermarket " << storeName << ":" << endl;
    for(int index = 0; index < transactionsVector.size(); index++)
        cout << transactionsVector.at(index) << endl;

    cin.ignore(numeric_limits<int>::max(),'\n');
    cout << endl;
    pressToContinue();
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

    if(clientTransactionsTemp.size() == 0) { //No transactions made
        cout << endl;
        cout << "ID Nr." << cliUniqueId << " has not made any transactions!" << endl;
    }

    else {
        cout << endl;
        for(int index = 0; index < clientTransactionsTemp.size(); index++)
            cout << clientTransactionsTemp.at(index) << endl;
    }

    cout << endl;
    pressToContinue();
}

void VendeMaisMais::recommendProductSingleClient() const {
    map<int,int> clientIdtoIndex; //int to int map that translates each client's ID to his position in the matrix used
    /*vector that contains every ID that made at least one transaction and respective initialization
    Note that simply getting the IDs from current clients is not good practice,
    since it is relatively likely that there are clients with no transactions or transactions from clients who have been removed*/

    vector<int> idsThatMadeTransactions;
    for(int index = 0; index < transactionsVector.size(); index++){
        if(!isMember(idsThatMadeTransactions, transactionsVector.at(index).getClientId()))
            idsThatMadeTransactions.push_back(transactionsVector.at(index).getClientId());
    }
    //Sorting makes it easier
    sort(idsThatMadeTransactions.begin(), idsThatMadeTransactions.end());

    //Initializing int to int client ID to matrix position map
    for(int counter = 0; counter < idsThatMadeTransactions.size(); counter++)
        clientIdtoIndex.insert(pair<int,int>(idsThatMadeTransactions.at(counter), counter));

    /*PRINTING TEST (DELETE)
    for(map<int,int>::const_iterator p = clientIdtoIndex.begin(); p != clientIdtoIndex.end(); p++)
        cout << p->first << " - " << p->second << endl;*/

    //Matrix initialization with the conditions required
    vector<vector<bool>> marketingmatrix(clientIdtoIndex.size(), vector<bool>(productsVector.size(),false));

    /*
    //Changing every bought product on each client boolean to #t (OLD WAY; DELETE LATER)
    for(int clientindex = 0; clientindex < marketingmatrix.size(); clientindex++){
        for(int transactionindex = 0; transactionindex < transactionsVector.size(); transactionindex++){
            if(clientIdtoIndex[transactionsVector.at(transactionindex).getClientId()] == clientindex) { //If ID of the client from current transaction is the one from the current loop in the marketing matrix
                    vector<string> products = transactionsVector.at(transactionindex).getProductsBought();
                    for(int productindex = 0; productindex < products.size(); productindex++){
                        int productIndexInMatrix = (productIdx.find(products.at(productindex)))->second;
                        marketingmatrix.at(clientindex).at(productIndexInMatrix) = true;
                    }
            }
        }
    }
    */

    //Changing every bought product on each client boolean to #t (NEW WAY: USING transactionIdx multimap (practically not used in the whole program)
    for(map<int,int>::const_iterator id_it = transactionIdx.begin(); id_it != transactionIdx.end(); id_it++){
            int clientIndex = (clientIdtoIndex.find(id_it->first))->second;
            vector<string> products = transactionsVector.at(id_it->second).getProductsBought(); //Products bought on current transaction
            for(int productindex = 0; productindex < products.size(); productindex++){
                int productIndexInMatrix = (productIdx.find(products.at(productindex)))->second;
                marketingmatrix.at(clientIndex).at(productIndexInMatrix) = true;
            }
    }


    /*
    //PRINTING TEST (DELETE)
    for(int i = 0; i < marketingmatrix.size(); i++){
        cout << "Index " << i << " - ";
        for(int j = 0; j < productsVector.size(); j++)
            cout << marketingmatrix.at(i).at(j) << " ";
        cout << endl;
    }
    */

    //Reading target client ID
    unsigned int targetId;
    bool clientHasTransactions;
    bool clientFound;
    cout << "Insert the target client's ID: ";
    do{
        cin >> targetId;
        for(int index = 0; index < clientsVector.size(); index++){
            if(clientsVector.at(index).getId() == targetId){
                clientFound = true;
                break;
            }
        }
        if(!clientFound)
            cout << "ERROR: Invalid client ID, please insert a valid ID: ";
    }while(!clientFound);

    map<int,int>::const_iterator id_it = clientIdtoIndex.find(targetId);
    if(id_it == clientIdtoIndex.end()) { //Client has not made any transactions -> use alternative marketing method

        //Extract every product bought on every transaction (since target client has no transactions, all clients who made are considered "most common", no need to verify it
        vector<int> indexesOfPossibleProducts;
        for(int index = 0; index < marketingmatrix.size(); index++){
            for(int productindex = 0; productindex < productsVector.size(); productindex++){
                if(marketingmatrix.at(index).at(productindex)) //If product is set as #t (by other words, was bought by a client)
                    indexesOfPossibleProducts.push_back(productindex);
            }
        }

        //Determine the suggested product's index
        int currentMax = 0;
        int suggestedProductIndex = indexesOfPossibleProducts.at(0);
        for(int index = 0; index < indexesOfPossibleProducts.size(); index++) {
                int temp = (int)count(indexesOfPossibleProducts.begin(), indexesOfPossibleProducts.end(), indexesOfPossibleProducts.at(index)); //Count occurrences of current product
                if(temp > currentMax) {
                    currentMax = temp;
                    suggestedProductIndex = indexesOfPossibleProducts.at(index);
                }
        }

        //Suggesting
        cout << "ID Nr." << targetId << ", it seems that you have not made any transactions yet!" << endl;
        cout << "The most bought product currently is " << productsVector.at(suggestedProductIndex).getName() << ", so why not start there? It only costs " << productsVector.at(suggestedProductIndex).getCost() << "!" << endl;
        return; //Exit function
    }

    //ORIGINAL METHOD: Used when target client has at least one transaction
    //Vector that counts number of common products between each client and the target client (target client if left with 0 so it is ignored later)
    vector<int> numberOfCommonProducts(marketingmatrix.size(), 0);
    int targetIndex = clientIdtoIndex[targetId];
    for(int index = 0; index < marketingmatrix.size(); index++){
        if(index != targetIndex) { //If it's not the target client
            for(int productindex = 0; productindex < productsVector.size(); productindex++){
                if(marketingmatrix.at(index).at(productindex) && marketingmatrix.at(targetIndex).at(productindex)) //If both products are set as #t
                    numberOfCommonProducts.at(index)++;
            }
        }
    }

    /*PRINTING TEST (DELETE)
    for(int k = 0; k < numberOfCommonProducts.size(); k++)
        cout << "index " << k << " - " << numberOfCommonProducts.at(k) << endl;*/

    //Holds the maximum number of common products (used for next loop)
    int maxCommon = *(max_element(numberOfCommonProducts.begin(),numberOfCommonProducts.end()));

    //Vector that holds all indexes of products that most common clients have bought and target client has not (with repetitions, so the maximum can be calculated and presented soon after)
    vector<int> indexesOfPossibleProducts;
    for(int index = 0; index < marketingmatrix.size(); index++){
        if(numberOfCommonProducts.at(index) == maxCommon) { //If current client is (one of) the most common
            for(int productindex = 0; productindex < productsVector.size(); productindex++){
                if(marketingmatrix.at(index).at(productindex) && !marketingmatrix.at(targetIndex).at(productindex)) //If common client has bought the product and target client has not
                    indexesOfPossibleProducts.push_back(productindex);
            }
        }
    }

    //Determine the suggested product's index
    int currentMax = 0;
    int suggestedProductIndex = indexesOfPossibleProducts.at(0);
    for(int index = 0; index < indexesOfPossibleProducts.size(); index++)
    {
        int temp = (int)count(indexesOfPossibleProducts.begin(), indexesOfPossibleProducts.end(), indexesOfPossibleProducts.at(index)); //Count occurrences of current product
        if(temp > currentMax)
        {       currentMax = temp;
                suggestedProductIndex = indexesOfPossibleProducts.at(index);
        }
    }

    //Suggesting
    cout << endl;
    cout << "ID Nr." << targetId << ", you should buy " << productsVector.at(suggestedProductIndex).getName() << ", it only costs " << productsVector.at(suggestedProductIndex).getCost() << "!" << endl;
    cout << endl;

    cin.ignore(numeric_limits<int>::max(),'\n');
    pressToContinue();
}

void VendeMaisMais::recommendProductBottom10() const {
    //Needs implementation
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
	out << endl << "supermarket " << supermarket.getStoreName() << endl << "Conta atualmente com:" << endl << supermarket.clientsVector.size() << " clientes" << endl << supermarket.productsVector.size() << " produtos no stock" << endl << supermarket.transactionsVector.size() << "transacoes realizadas, num valor total de " << totalAmountSpent(supermarket) << endl;

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
    bool cliFound;
    do{
        cliFound = false;
        cin >> customerId;
        for(int index = 0; index < supermarket.clientsVector.size(); index++){
            if(supermarket.clientsVector.at(index).getId() == customerId){
                cliFound = true;
                break;
            }
        }
        if(!cliFound)
            cout << "ERROR: Invalid client ID, please insert a valid value: ";
    }while(!cliFound);

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
