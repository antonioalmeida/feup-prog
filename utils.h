#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <climits>

#include "defs.h"
#include "Date.h"

using namespace std;


void clearScreen();
void pressToContinue();
void DeleteWhitespace(string &s);
unsigned short int readUnsignedShortInt(unsigned short int minValue, unsigned short int maxValue);
int readInteger(int minValue, int maxValue);

//Verify and return yes or no input to string
string readYesNo ();
                     
//Checks if leap year
bool isLeapYear(int year);

//Returns the number of days on a given month
unsigned int numDays(unsigned int year,unsigned int month);

//Checks if given number(ID) is already in the vector
bool isMember(const vector<int> &idVector, int id);

