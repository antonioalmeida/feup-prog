#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <climits>

#include "defs.h"

using namespace std;


void clearScreen();
// void pressToContinue();
void DeleteWhitespace(string &s);
unsigned short int readUnsignedShortInt(unsigned short int minValue, unsigned short int maxValue);
int readInteger(int minValue, int maxValue);

//Verify and return yes or no input to string
string readYesNo ();