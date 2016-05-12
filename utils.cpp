#include "utils.h"


void clearScreen(){
  for(int counter = 0; counter < ALTURA_ECRA; counter++)
    cout << endl;
}
/*
void pressToContinue(){
    cout << "Press any key, followed by ENTER to continue" << endl;
    //getchar();
    cin.ignore(INT_MAX, '\n');
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
        cout << "ERROR: Out of range value, please insert a value between " << minValue << "-" << maxValue << endl;
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
