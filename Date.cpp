
#include "Date.h"
#include "utils.h"


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
  out << date.day << "-" << date.month << "-" << date.year; // - instead of / just to be different from the save method
    return out;
}

bool operator<=(const Date &date1, const Date &date2) {
    bool isBefore = (date1.year < date2.year) || (date1.year == date2.year && date1.month < date2.month) || (date1.year == date2.year && date1.month == date2.month && date1.day < date2.day);
    bool isEqual = (date1.year == date2.year) && (date1.month == date2.month) && (date1.day == date2.day);
    return isBefore || isEqual;
}

bool operator>=(const Date &date1, const Date &date2) {
    bool isAfter = (date1.year > date2.year) || (date1.year == date2.year && date1.month > date2.month) || (date1.year == date2.year && date1.month == date2.month && date1.day > date2.day);
    bool isEqual = (date1.year == date2.year) && (date1.month == date2.month) && (date1.day == date2.day);
    return isAfter || isEqual;
}

bool operator==(const Date &date1, const Date &date2) {
    return (date1.year == date2.year) && (date1.month == date2.month) && (date1.day == date2.day);
}


//Function to verify date
bool Date::verifyDate() const {

    bool result;

    if((numDays(year, month) >= day && day > 0) && (month > 0 && month < 13))
        result = true;
    else {
        cout << "The date you inserted was not valid, please try again." << endl;
        result = false;
    }
    return result;
}















