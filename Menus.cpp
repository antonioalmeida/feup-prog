#include "Menus.h"


bool initialInformation(string &store, string &clientsFileName, string &productsFileName, string &transactionsFileName) {

  clearScreen();
  cout << "Insert the store's name: " << endl;
  getline(cin, store);

  cout << "Insert the clients' filename: " << endl;
  getline(cin, clientsFileName);
  ifstream clientTestFile;
  clientTestFile.open(clientsFileName);
  if(!clientTestFile.is_open()) //If opening fails, then filename is not valid
    return false;

  cout << "Insert the products' filename: " << endl;
  getline(cin, productsFileName);
  ifstream productTestFile;
  productTestFile.open(productsFileName);
  if(!productTestFile.is_open())
    return false;

  cout << "Insert the transactions' filename: " << endl;
  getline(cin, transactionsFileName);
  ifstream transactionTestFile;
  transactionTestFile.open(transactionsFileName);
  if(!transactionTestFile.is_open())
    return false;


  //No failure in opening = good to go. Close temporary files to avoid unwanted trouble
  clientTestFile.close();
  productTestFile.close();
  transactionTestFile.close();
  return true;
}

/* ************************
   CLIENT MENU FUNCTION SET
   ************************ */

unsigned short int clientManagementMenu(){
  unsigned short int option;

  clearScreen();
  cout << TAB_BIG << "----------------------" << endl;
  cout << TAB_BIG << "-----Client menu------" << endl;
  cout << TAB_BIG << "----------------------" << endl;
  cout << endl;
  cout << TAB << "1 - Show clients alphabetically" << endl;
  cout << TAB << "2 - Show a client's properties" << endl;
  cout << TAB << "3 - Edit a client's properties" << endl;
  cout << TAB << "4 - Add a new client" << endl;
  cout << TAB << "5 - Remove a client" << endl;
  cout << TAB << "6 - Show 'Bottom10' clients" << endl;
  cout << TAB << "0 - Go back to main menu" << endl << endl;
  cout << TAB << "Choose an option: ";
  option = readUnsignedShortInt(0, 6);

  return option;
}


void clientManagementOption(VendeMaisMais &supermarket){
  unsigned int option;

  while((option = clientManagementMenu())) //When option = 0, it is interpreted logically as false and exits loop
    switch (option){
        case 1:
            supermarket.listClientsAlphabetically();
            break;
        case 2:{
            cout << "What is the client's name? : ";
            cin.ignore(numeric_limits<int>::max(),'\n');
            string clientName = readClientName(supermarket);
            cout << endl;
            supermarket.showSpecificClient(clientName);
            break;
        }
        case 3:{
            cout << "What is the client's name? : ";
            cin.ignore(numeric_limits<int>::max(),'\n');
            string clientName = readClientName(supermarket);
            cout << endl;
            supermarket.editSpecificClient(clientName);
            break;
        }
        case 4:{
            cout << "What is the new client's name? : ";
            cin.ignore(numeric_limits<int>::max(),'\n');
            string clientName;
            getline(cin, clientName, '\n');
            DeleteWhitespace(clientName);
            cout << endl;
            cout << "What is the client's new join date? (DD/MM/YYYY) : ";
            string clientDate;
            getline(cin, clientDate);
            DeleteWhitespace(clientDate);
            //Create temporary date
            Date newDateClass(clientDate);
            Client tempClient(clientName, newDateClass);
            supermarket.addClient(tempClient);
            break;
        }
        case 5:{
            cout << "What is the client's name? : ";
            cin.ignore(numeric_limits<int>::max(),'\n');
            string clientName = readClientName(supermarket);
            cout << endl;
            supermarket.removeSpecificClient(clientName);
            break;
        }
        case 6:{
            //supermarket.showBottom10();
        }
    }
}

/* *****************************
   TRANSACTION MENU FUNCTION SET
   ***************************** */

unsigned short int transactionsManagementMenu(){

    unsigned int option;

    clearScreen();
    cout << TAB_BIG << "-------------------" << endl;
    cout << TAB_BIG << "-Transactions Menu-" << endl;
    cout << TAB_BIG << "-------------------" << endl;
    cout << endl;
    cout << TAB << "1 - Show transactions between two dates" << endl;
    cout << TAB << "2 - Show a client's transactions (by chronological order)" << endl;
    cout << TAB << "3 - Add a transaction (make a purchase)" << endl;
    cout << TAB << "4 - Show transactions made on a specific date" << endl;
    cout << TAB << "5 - Show all transactions made" << endl;
    cout << TAB << "0 - Leave for main menu" << endl << endl;
    cout << TAB << "Choose an option: ";
    option = readUnsignedShortInt(0, 5);
    return option;
}

void transactionsManagementOption(VendeMaisMais &supermarket){
  unsigned int option;

  while((option = transactionsManagementMenu()))
    switch (option){
    case 1:
        supermarket.showTransactionsBetweenDates();
        break;
    case 2: {
        cout << TAB << "Choose the way you want to identify the client:" << endl;
        cout << TAB << "1 - Specify client unique ID" << endl;
        cout << TAB << "2 - Specify client name" << endl;
        cout << TAB << "0 - Back to transaction menu" << endl;
        cout << TAB << "Your option: ";
        unsigned int option = readUnsignedShortInt(0,2);
        switch(option){
            case 0:
                break;
            case 1:{
                unsigned int cliUniqueId = readClientId(supermarket);
                supermarket.showClientTransactions(cliUniqueId);
                break;
            }
            case 2:{
                cin.ignore(numeric_limits<int>::max(), '\n');
                cout << "Insert the client's name: ";
                string cliName = readClientName(supermarket);
                supermarket.showClientTransactions(cliName);
                break;
            }
        }
        break;
    }
    case 3:
        supermarket.addTransaction();
        break;
    case 4:
        supermarket.showTransactionsOnDate();
        break;
    case 5:
        supermarket.showAllTransactions();
        break;
    }
}

/* ********************************
   RECOMMENDATION MENU FUNCTION SET
   ******************************** */

unsigned short int recommendationMenu(){

    unsigned int option;

    clearScreen();
    cout << TAB_BIG << "---------------------" << endl;
    cout << TAB_BIG << "-Recommendation Menu-" << endl;
    cout << TAB_BIG << "---------------------" << endl;
    cout << endl;
    cout << TAB << "1 - Recommend product for a single client" << endl;
    cout << TAB << "2 - Recommend product for 'Bottom10' clients" << endl;
    cout << TAB << "0 - Leave for main menu" << endl << endl;
    cout << TAB << "Choose an option: ";
    option = readUnsignedShortInt(0, 2);
    return option;
}

void recommendationOption(VendeMaisMais &supermarket){
  unsigned int option;

  while((option = recommendationMenu()))
    switch (option){
    case 1:
        supermarket.recommendProductSingleClient();
        break;
    case 2:
        supermarket.recommendProductBottom10();
        break;
    }

}


//Main menu
unsigned short int mainMenu(){

  unsigned short int option;

  clearScreen();

  cout << TAB_BIG << "--------------" << endl;
  cout << TAB_BIG << "---MainMenu---" << endl;
  cout << TAB_BIG << "--------------" << endl;
  cout << endl;
  cout << TAB << "1 - Clients Management" << endl;
  cout << TAB << "2 - Show available products" << endl;
  cout << TAB << "3 - Transactions Menu" << endl;
  cout << TAB << "4 - Recommendation System" << endl;
  cout << TAB << "0 - Exit Program" << endl << endl;
  cout << TAB << "Choose an option: ";
  option = readUnsignedShortInt(0, 4);

  return option;
}

void mainOption(VendeMaisMais &supermarket) {

  unsigned short int option;

  while(option = mainMenu()){
    switch (option){
    case 1:
    clientManagementOption(supermarket);
    break;
    case 2:
    supermarket.listProductsAlphabetically();
    break;
    case 3:
    transactionsManagementOption(supermarket);
    break;
    case 4:
    recommendationOption(supermarket);
    break;
    }
  }

  supermarket.saveChanges();
}
