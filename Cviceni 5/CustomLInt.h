#pragma once
#include <string.h>
#include <iostream>
using namespace std;
class CustomLInt
{
private:
	char* value = nullptr;
	char sign = '+';

	CustomLInt CustomLIntAdd(CustomLInt& a, CustomLInt& b);
	CustomLInt CustomLIntSub(CustomLInt& a, CustomLInt& b);
	void CustomLIntTrim(CustomLInt& a);
	void CustomLIntSwap(CustomLInt& a);
	int CompareAbs(CustomLInt& a, CustomLInt& b);
	int Compare(CustomLInt& a, CustomLInt& b);
	CustomLInt CustomLIntMultiply(CustomLInt& a, CustomLInt& b);
	CustomLInt CustomIntDivide(CustomLInt& a, CustomLInt& b);

public:
	//CONSTRUCTORS
	CustomLInt(const char x);
	CustomLInt(char* x);
	CustomLInt(const CustomLInt& x);
	CustomLInt(int n);

	//GETTERS AND SETTERS (FOR TEST ONLY)
	char* GetValue() { return this->value; }
	char GetSign() { return this->sign; }
	void SetValue(const char p[]) { delete[] this->value; this->value = new char[strlen(p) + 1]; strcpy_s(this->value, strlen(p) + 1, p); }

	//OPERATORS OVERLOAD
	CustomLInt& operator = (const CustomLInt& s);
	CustomLInt& operator = (const char* s);
	CustomLInt& operator = (int n);
	CustomLInt operator + (CustomLInt& n);
	CustomLInt& operator += (CustomLInt& n);
	CustomLInt operator - (CustomLInt& n);
	CustomLInt& operator -= (CustomLInt& n);
	CustomLInt operator * (CustomLInt& n);
	CustomLInt& operator *= (CustomLInt& n);
	CustomLInt operator / (CustomLInt& n);
	CustomLInt& operator /= (CustomLInt& n);

	//FUNCTIONS
	void Clear() { if (this->value != nullptr) delete[] this->value; this->value = nullptr; }
	void Copy(int num);
	void Copy(const CustomLInt& num);	

	~CustomLInt() { delete[] this->value; }
};

