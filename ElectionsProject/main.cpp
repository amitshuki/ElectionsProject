#include <iostream>
#include "myString.h"
using namespace std;
using namespace myStr;
int main()
{
	//string str1;
	myString str2;

	//cout << "str1: ";
	//cin >> str1;
	cout << endl << "str2: ";
	cin >> str2;
	//cout << "str1 = " << str1 << endl;
	cout << "str2 = " << str2 << endl;
	cout << "len = " << str2.getlength() << endl;
	cout << "capacity = " << str2.getCapacity() << endl << endl;
	
	str2.append(" adi sapir mushlemet");
	cout << "str2 = " << str2 << endl;
	cout << "len = " << str2.getlength() << endl;
	cout << "capacity = " << str2.getCapacity() << endl << endl;

	myString str1 = str2.subMyString(4,2000);
	cout << "str1 = " << str1 << endl;
	cout << "len = " << str1.getlength() << endl;
	cout << "capacity = " << str1.getCapacity() << endl << endl;

	str1.erase(5, 3);
	cout << "str1 = " << str1 << endl;
	cout << "len = " << str1.getlength() << endl;
	cout << "capacity = " << str1.getCapacity() << endl << endl;

	str1.setIdx(-1, 'H');
	cout << "str1 = " << str1 << endl;
	cout << "len = " << str1.getlength() << endl;
	cout << "capacity = " << str1.getCapacity() << endl << endl;

	cout << "str1[2] = " << str1[2] << endl << endl;

	if (str1 == str2)
		cout << "They are the same" << endl << endl;
	else
		cout << "They are not the same" << endl << endl;

	str2 = str1;
	cout << "str2 = " << str2 << endl;
	cout << "len = " << str2.getlength() << endl;
	cout << "capacity = " << str2.getCapacity() << endl << endl;

	if (str1 == str2)
		cout << "Now they are the same" << endl << endl;
	else
		cout << "They are still not the same" << endl << endl;
}