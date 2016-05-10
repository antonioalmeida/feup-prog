#include "Date.h"


Date::Date(string date) {
    istringstream dateTemp;
    dateTemp.str(date);
    dateTemp >> day;
    dateTemp.ignore(numeric_limits<int>::max(), '/');
    dateTemp >> month;
    dateTemp.ignore(numeric_limits<int>::max(), '/');
    dateTemp >> year;
}

unsigned int Date::getDay() const {
  return day;
}

unsigned int Date::getMonth() const {
  return month;
}

unsigned int Date::getYear() const {
  return year;
}

void Date::setDay(unsigned int day) {
  this->day = day;
}

void Date::setMonth(unsigned int month) {
  this->month = month;
}

void Date::setYear(unsigned int year) {
  this->year = year;
}

void Date::save(ofstream &out) const{
  out << day << "/" << month << "/" << year;
}

ostream& operator<<(ostream& out, const Date &date){
  out << date.day << "-" << date.month << "-" << date.year; // - instead of / just to be different from the save method...
}
