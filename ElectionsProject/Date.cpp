#include <iostream>;
#include "Date.h"


Date::Date(int day, int month, int year)
{
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
	if (month > 0 || month < 12) {
		this->month = month;
		return true;

	}
	else
		return false;

}
bool Date::setYear(int year)
{
	if (year > 999 || year < 9999) {
		this->year = year;
		return true;
	}
	else
		return false;
	

	
}

void printDate(Date d)
{
	if (d.getDay() > 9 && d.getMonth() > 9)
	{
		cout << d.getDay() << '/' << d.getMonth() << '/' << d.getYear() << endl;
	}
	if (d.getDay() < 9 && d.getMonth() > 9)
	{
		cout <<0<< d.getDay() << '/' << d.getMonth() << '/' << d.getYear() << endl;

	}
	if (d.getDay() < 9 && d.getMonth() < 9)
	{
		cout << 0 << d.getDay() << '/' << d.getMonth() << 0 << '/' << d.getYear() << endl;

	}
}

int Date::getDay(void) const
{
	return day;
}
int Date::getMonth(void) const
{
	return month;
}
int Date::getYear(void) const
{
	return year;
}

