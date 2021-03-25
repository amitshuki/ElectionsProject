#pragma once
#include <iostream>
using namespace std;
class undefined_option :
	public exception
{
private:
	string msg;
public:
	undefined_option(const char* option_type) {
		this->msg += "Undefined ";
		this->msg.append(option_type);
		this->msg += ".";
	}
	~undefined_option() = default;
	virtual const char* what()  const throw() { return msg.data(); }
};


