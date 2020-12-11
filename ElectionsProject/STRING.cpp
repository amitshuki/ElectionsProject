#include "STRING.h"
STRING::STRING() {
	str = new char[1]{ 0 };
	logicallength = 0;
	physicallength = 1;
}
STRING::STRING(const char* other_str) {
	this->operator=(other_str);
}
STRING::~STRING() {
	delete[] str;
}
STRING& STRING::operator=(const STRING& other_str){
	return this->operator=(other_str.str);
}
STRING& STRING::operator=(const char* other_str) {
	int i,other_length = length(other_str);
	while (other_length > this->getLength())
		relength();
	for (i = 0; i < other_length; i++)
		this->str[i] = other_str[i];
	this->logicallength = i;
	return *this;
}

void STRING::relength(){
	physicallength *= 2;
	char* new_str = new char[physicallength] {0};
	for (int i = 0; i < logicallength; i++)
		new_str[i] = str[i];
	delete[] str;
	str = new_str;
}

int STRING::getLength() {
	int i = 0;
	while (str[i++] != '\0');
	return i-1;
}

int STRING::length(const char* other_str){
	int i = 0;
	while (other_str[i++] != '\0');
	return i - 1;
}

