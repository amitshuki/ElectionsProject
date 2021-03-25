#pragma once
#include <iostream>
using namespace std;
class outfile_error :
	public exception
{
private:
	string msg;
public:
	outfile_error() {
		msg += "Error writing to file.";
	}
	outfile_error(const char* entity) {
		this->msg.append("Error writing to file in class ");
		this->msg.append(entity);
		this->msg += ".";
	}
	~outfile_error() = default;
	virtual const char* what()  const throw() { return msg.data(); }
};

