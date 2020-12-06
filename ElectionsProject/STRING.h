#pragma once
class STRING
{
private:
	char* str;
	int physicalSize,logicalSize;
	void resize();
public:
	STRING();
	STRING(const char* str);
	~STRING();
	char& operator[](int index)const { return str[index]; }
	const int& getPhysicalSize()const { return physicalSize; }
	const int& getlogicalSize()const { return logicalSize; }
	int getLength();
	static int length(const char* other_str);
	/*void append(const STRING& str);
	void erase(int begining, int end);
	void erase(int index);*/
	STRING& operator=(const STRING& str);
	STRING& operator=(const char* str);

};

