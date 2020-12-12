#pragma once
#include <iostream>
using namespace std;

class Date {
	private:
		int day, month, year;
	public:
		Date();
		Date(int day, int month, int year);
		bool setDay(int day);
		bool setMonth(int month);
		bool setYear(int year);
		const int& getDay(void) const;
		const int& getMonth(void) const;
		const int& getYear(void) const;

		void printDate();
		
};
inline void checkInputValidity(const string& val, int& num, const int min, const int max) {//Asks for a correct input
	while (num<min || num>max) {
		cout << "The input you have given for " << val << " is not valid." << endl;
		cout << "Please enter a valid input between " << min << " and " << max << ": ";
		cin >> num;
		cout << endl;
	}
}