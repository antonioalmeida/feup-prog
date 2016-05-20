#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>

using namespace std;


class Date {
private:
  unsigned int day;
  unsigned int month;
  unsigned int year;

public:
  Date(){};
  Date(string date); //Date given according to the format: DD/MM/AAAA
  unsigned int getDay() const;
  unsigned int getMonth() const;
  unsigned int getYear() const;
  void setDay(unsigned int day);
  void setMonth(unsigned int month);
  void setYear(unsigned int year);
  void save(ofstream &out) const;
  bool verifyDate() const;

  friend ostream& operator<<(ostream& out, const Date &date);
  friend bool operator<=(const Date &date1, const Date &date2); //Compares date1 with date2; returns true if date1 does not come after date2 in the Gregorian calendar
  friend bool operator>=(const Date &date1, const Date &date2); //Compares date1 with date2; returns true if date1 does not come before date2 in the Gregorian calendar
  friend bool operator==(const Date &date1, const Date &date2); //Compares date1 with date2; returns true if date1 is the same as date2 in the Gregorian calendar
};
