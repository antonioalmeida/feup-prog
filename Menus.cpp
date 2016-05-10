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
  cout << TAB_BIG << "Menu Gestao Clientes" << endl;
  cout << endl;
  cout << TAB << "1 - Listar clientes" << endl;
  cout << TAB << "2 - Ver informacao cliente" << endl;
  cout << TAB << "3 - Editar cliente" << endl;
  cout << TAB << "4 - Remover cliente" << endl;
  cout << TAB << "0 - Voltar ao menu inicial" << endl << endl;
  cout << TAB << "Qual a sua opcao: ";
  option = readUnsignedShortInt(0, 4);

  return option;
}


void clientManagementOption(VendeMaisMais &supermarket){
  unsigned int option;
  string name;

  while((option = clientManagementMenu())) //When option = 0, it is interpreted logically as false and exits loop
    switch (option){
    case 1:
    supermarket.listClientsAlphabetically();
    break;
    case 2:
    cout << "Qual o nome do cliente: ";
    getline(cin, name);
    supermarket.showSpecificClient(name);
    break;
    case 3:
    break;
    case 4:
    break;
    }
}

/* *****************************
   TRANSACTION MENU FUNCTION SET
   ***************************** */

unsigned short int transactionsManagementMenu(){
    
    unsigned int option;
    string name;
    
    clearScreen();
    cout << TAB_BIG << "-------------------" << endl;
    cout << TAB_BIG << "-Transactions Menu-" << endl;
    cout << TAB_BIG << "-------------------" << endl;
    cout << endl;
    cout << TAB << "1 - Show transactions between two dates" << endl;
    cout << TAB << "2 - Show a client's transactions (alphabetically)" << endl;
    cout << TAB << "3 - Add a transaction (make a purchase)" << endl;
    cout << TAB << "4 - Show transactions made on a specific date" << endl;
    cout << TAB << "0 - Leave for main menu" << endl << endl;
    cout << TAB << "Qual a sua opcao: ";
    option = readUnsignedShortInt(0, 4);
    return 0;
}

void transactionsManagementOption(VendeMaisMais &supermarket){
  unsigned int option;

  while((option = transactionsManagementMenu()))
    switch (option){
    case 1:
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
    }
}

/* ********************************
   RECOMMENDATION MENU FUNCTION SET
   ******************************** */

unsigned short int recommendationMenu(){
    
    //Needs implementation
    return 0;
}

void recommendationOption(VendeMaisMais & supermarket){
  unsigned int option;

  while((option = recommendationMenu()))
    switch (option){
    case 1:
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
    }

}


//Main menu
unsigned short int mainMenu(){
    
  unsigned short int option;

  clearScreen();
    
  cout << TAB_BIG << "--------------" << endl;
  cout << TAB_BIG << "-Menu Inicial-" << endl;
  cout << TAB_BIG << "--------------" << endl;
  cout << endl;
  cout << TAB << "1 - Clients Management" << endl;
  cout << TAB << "2 - Show availible products" << endl;
  cout << TAB << "3 - Transactions Menu" << endl;
  cout << TAB << "4 - Recommendation System" << endl;
  cout << TAB << "0 - Exit Program" << endl << endl;
  cout << TAB << "Qual a sua opcao: ";
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
