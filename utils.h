#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <climits>

#include "defs.h"
#include "Transaction.h"
#include "Date.h"

using namespace std;


void clearScreen();
// void pressToContinue();
void DeleteWhitespace(string &s);
unsigned short int readUnsignedShortInt(unsigned short int minValue, unsigned short int maxValue);
int readInteger(int minValue, int maxValue);

//Verify and return yes or no input to string
string readYesNo ();

bool compareTrans(const Transaction &tran1, const Transaction &tran2); //Compares two transactions; returns true if tran1 was made before tran2 in the Gregorian calendar

//Checks if leap year
bool isLeapYear(int year);

//Returns the number of days on a given month
unsigned int numDays(unsigned int year,unsigned int month);