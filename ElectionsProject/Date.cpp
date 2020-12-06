#include "Date.h"
#include <iostream>
using namespace std;


Date::Date(){
	day = month = year = 0;
}
Date::Date(int day, int month, int year)
{
	checkInputValidity("day", day, 1, 30);
	checkInputValidity("month", month, 1, 12);
	checkInputValidity("year", year, 1900, 2020);
	this->day = day;
	this->month = month;
	this->year = year;
}

bool Date::setDay(int day)
{
	if (day > 0 || day < 31) {
		this->day = day;
		return true;
	}
	else
		return false;
}
bool Date::setMonth(int month) 
{
	if (month > 0 || month <= 12) {
		this->month = month;
		return true;
	}
	else
		return false;
}
bool Date::setYear(int year)
{
	if (year > 1900 || year < 2020) {
		this->year = year;
		return true;
	}
	else
		return false;
}

void Date::printDate(){
	cout << this->day << '\\' << this->month << '\\' << this->year << endl;
}
const int& Date::getDay(void) const
{
	return day;
}
const int& Date::getMonth(void) const
{
	return month;
}
const int& Date::getYear(void) const
{
	return year;
}

