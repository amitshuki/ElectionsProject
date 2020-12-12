#pragma once
#include "myString.h"
#include <iostream>

using namespace std;
using namespace myStr;

myString::myString(const int& elength) :arr(nullptr), length(0), capacity(0) {
	if (elength >= 0) {
		arr = new char[elength + 1]{ '\0' };
		this->length = elength;
		this->capacity = elength + 1;
	}
	else
		cout << "Cannot allocate negatives." << endl;
}
myString::myString(const myString& other) :arr(nullptr), length(0), capacity(0) {
	length = other.length;
	capacity = other.capacity;
	arr = new char[capacity];
	for (int i = 0; i < capacity; i++)
		arr[i] = other.arr[i];

}
myString::myString(const char* str) :arr(nullptr), length(0), capacity(0){
	int i = 0, countSpaces = 0;
	//while (str[countSpaces++] == ' ');
	length = myStrLen(str + countSpaces);
	capacity = length + 1;
	arr = new char[capacity] {'\0'};
	for (int j = 0; j < length; j++)
		arr[j] = str[j + countSpaces];
}
myString::~myString() {
	if (capacity > 0)
		delete[] arr;
}

void myString::resizeCapacity(const int& newCapacity) { 
	/*This function resizeCapacitys myString according to given newCapacity*/
	if (newCapacity == 0) {
		cout << "New capacity is invalid." << endl;
	}
	else {
		if (newCapacity > 0 && newCapacity != capacity) {
			if (newCapacity - 1 > length) {//=============== Enlarge myString
				if (newCapacity <= capacity)//========= case 1.1: length < newCapacity < capacity
					resizeCapacityCase_1_1(newCapacity);
				else {//=========================== case 1.2: length < capacity < newCapacity
					if (newCapacity >= capacity * enlargeMultiplier)//= case 1.2.1: length < capacity*2 < newCapacity
						resizeCapacityCase_1_2(newCapacity);
					else//========================================= case 1.1: length < newCapacity < capacity*2
						resizeCapacityCase_1_3(newCapacity);
				}
			}
			else {////============================ shrink myString
				if (newCapacity < capacity / shrinkDevider)// case 2.1: newCapacity < capacity / shirnkDevider
					resizeCapacityCase_2(newCapacity);
				else// =================================  case 2.1: newCapacity < capacity && newCapacity > capacity / shirnkDevider
					length = newCapacity - 1;
			}
		}
	}
}
void myString::resizeCapacityCase_1_1(const int& newCapacity) {
	for (int i = length; i < newCapacity; i++)
		arr[i] = '\0';
}
void myString::resizeCapacityCase_1_2(const int& newCapacity) {
	int i;
	char* newArr = new char[newCapacity];
	for (i = 0; i < newCapacity; i++)
		if (i < length)
			newArr[i] = arr[i];
		else
			newArr[i] = '\0';

	delete[] arr;
	arr = newArr;
	capacity = newCapacity;
}
void myString::resizeCapacityCase_1_3(const int& newCapacity) {
	int i;
	char* newArr = new char[capacity * 2];
	for (i = 0; i < capacity * 2; i++)
		if (i < length)
			newArr[i] = arr[i];
		else
			newArr[i] = '\0';
	newArr[i] = '\0';
	delete[] arr;
	arr = newArr;
	capacity = capacity * 2;
}
void myString::resizeCapacityCase_2(const int& newCapacity) {
	int i;
	char* newArr = new char[newCapacity];
	for (i = 0; i < newCapacity - 1; i++)
		newArr[i] = arr[i];
	arr[newCapacity - 1] = '\0';
	delete[] arr;
	arr = newArr;
	length = newCapacity - 1;
	capacity = newCapacity;
}

myString& myString::append(const myString& other) {
	if (other.length > 0) {
		int i, originallength = length;
		this->resizeCapacity(length + other.length + 1);
		length += other.length;
		for (i = 0; i < other.length; i++)
			arr[i + originallength] = other.arr[i];
	}
	return *this;
}
myString myString::subMyString(const int& start, const int& requestedLength)const {
	int i, actualLength, actualStart;
	if (start > this->length - 1 || length <= 0)
		return myString();

	actualStart = (start < 0) ? 0 : start;
	actualLength =
		(actualStart + requestedLength > this->length - 1) ?
		this->length - actualStart : requestedLength; // if length exceeds length-1 return length-1

	myString newmyString(actualLength);
	for (i = 0; i < actualLength; i++)
		newmyString.arr[i] = this->arr[i + actualStart];
	return newmyString;
}
void myString::erase(const int& start, const int& requestedLength) {// erases length characters from given begining
	if (start > length - 1 || requestedLength <= 0)
		return;
	int i, j;
	int actualStart = (start < 0) ? 0 : start;
	int newLen =
		((actualStart + requestedLength) > (this->length - 1)) ? this->length - actualStart : requestedLength;

		myString newArr(length - newLen);
	for (i = j = 0; i < length && j < newArr.length; i++, j++) {
		if (i == start)
			i += newLen;
		newArr.arr[j] = this->arr[i];
	}
	*this = newArr;
}
bool myString::setIdx(const int& index, const char& val) {
	if (index<0 || index>length - 1) {
		cout << ("Index not in range.\n");
		return false;
	}
	arr[index] = val;
	return true;
}

char myString::operator[](const int& index)const {
	if (length == 0) {
		out_of_range e("Out of range.\n");
		throw e;
	}
	else if (index<0 || index>length - 1) {
		out_of_range e("Out of range.\n");
		throw e;
	}
	return arr[index];
}
myString& myString::operator=(const myString& other) {
	if (&other != this) {
		resizeCapacity(other.capacity);
		for (int i = 0; i < other.length; i++)
			arr[i] = other.arr[i];
		length = other.length;
	}
	return *this;
}
bool myString::operator==(const myString& other)const {
	int i;
	if (length != other.length)
		return false;

	for (i = 0; i < length; i++)
		if (arr[i] != other.arr[i])
			return false;

	return true;
}

bool myString::checkNumericInput(const char* str) {
	int i, length = myStrLen(str);
	for (i = 0; i < length; i++)
		if (str[i] > '9' || str[i] < '0')
			return false;
	return true;
}
int myString::myStrLen(const char* str) {
	int i = 0;
	while (str[i++]);
	return i - 1;
}