#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>


#include "defs.h"
#include "utils.h"
#include "Vende++.h"

//using namespace std;


bool initialInformation(string &store, string &clientsFileName, string &productsFileName, string &transactionsFileName);
void mainOption(VendeMaisMais &supermarket);
void clientManagementOption(VendeMaisMais &supermarket);
void transactionsManagementOption(VendeMaisMais &supermarket);
void recommendationOption(VendeMaisMais &supermarket);
