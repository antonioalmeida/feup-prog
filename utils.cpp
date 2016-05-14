#include "utils.h"


void clearScreen(){
  for(int counter = 0; counter < ALTURA_ECRA; counter++)
    cout << endl;
}
/*
void pressToContinue(){
    cout << "Press any key, followed by ENTER to continue" << endl;
    //getchar();
    cin.ignore(numeric_limits<int>::max(), '\n');
    clearScreen();
}
*/

void DeleteWhitespace(string &s){
  //Delete whitespace characters in the beginning
    while(s.at(0) == ' ')
        s.erase(0,1);
    //Delete whitespace characters in the end
    int lastindex = s.size()-1;
    while(s.at(lastindex) == ' ')
     {
        s.erase(lastindex,1);
        lastindex--;
     }
}


unsigned short int readUnsignedShortInt(unsigned short int minValue, unsigned short int  maxValue){

  unsigned short int number;
  do{
      cin >> number;
      if(number < minValue || number > maxValue)
        cout << "ERROR: Out of range value, please insert a value between " << minValue << "-" << maxValue << endl;
  }while(number < minValue || number > maxValue);

  return number;
}


int readInteger(int minValue, int maxValue){

  int number;
  do{
      cin >> number;
      if(number < minValue || number > maxValue)
        cout << "ERROR: Out of range value, please insert a value between " << minValue << "-" << maxValue << ":";
  }while(number < minValue || number > maxValue);

  return number;
}

string readYesNo() {

    string answer;
    bool goodChoice = false;

    do{
        getline(cin, answer);

        if(answer == "yes" || answer == "no")
            goodChoice = true;

        if(!goodChoice)
            cout << "ERROR: That was not a valid answer, please insert valid option (yes or no) :" << endl;

    } while(!goodChoice);

    return answer;
}

bool compareTrans(const Transaction &tran1, const Transaction &tran2) {
    return tran1.getDateOfTransaction() <= tran2.getDateOfTransaction();
}


//Check if leap year
bool isLeapYear(int year) {
    bool leap = ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);

    return leap;
}

//Returns the number of days on a given month
unsigned int numDays(unsigned int year,unsigned int month) {

    unsigned int days;

    if(month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12) days = 31;
    else if(month == 2) {
        if(isLeapYear(year)) days = 29;
        else days = 28;
    }
    else days = 30;

    return days;
}
