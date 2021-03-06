#pragma once
#include <iostream>
using namespace std;
namespace myStr {
	class myString
	{
	private:
		char* arr;
		int length, capacity;
		static const int shrinkDevider = 3;
		static const int enlargeMultiplier = 2;
	public:
		myString() :arr(nullptr), length(0), capacity(0) {}
		myString(const int& elength);
		myString(const myString& other);
		myString(const char* str);
		myString(istream& in) :arr(nullptr), length(0), capacity(0) { load(in); }

		~myString();

		const int& getlength()const { return length; }
		const int& getCapacity()const { return capacity; }

		bool resizeCapacity(const int& newlength);
	private:
		void resizeCapacityCase_1_1(const int& newlength);
		void resizeCapacityCase_1_2(const int& newlength);
		void resizeCapacityCase_1_3(const int& newlength);
		void resizeCapacityCase_2(const int& newlength);
	public:
		myString& append(const myString& other);
		myString& append(const char* str) { return this->append(myString(str)); }
		
		myString subMyString(const int& start, const int& length)const;
		void erase(const int& begining, const int& length);
		bool setIdx(const int& index, const char& val);

		char operator[](const int& index)const;
		myString& operator=(const myString& other);
		myString& operator=(const char* str) { return this->operator=(myString(str)); }

		bool operator==(const myString& other)const;
		bool operator!=(const myString& other)const { return !(*this == other); }
		bool operator!=(const char* str)const { return !(*this == myString(str)); }


		friend ostream& operator<<(ostream& output, const myString& myStr);
		friend istream& operator>>(istream& input, myString& str);

		bool save(ostream& out) const;
		bool load(istream& in);

		static bool checkNumericInput(const char* str);
		static int myStrLen(const char* str);
	};
}