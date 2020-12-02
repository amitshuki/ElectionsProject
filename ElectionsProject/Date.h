#pragma once
#include <iostream>
class Date {
	private:
		int day, month, year;
	public:
		Date(int day, int month, int year);

		bool setDay(int day);
		bool setMonth(int month);
		bool setYear(int year);

		void printDate(Date d);

		

		int getDay(void) const;
		int getMonth(void) const;
		int getYear(void) const;


	};