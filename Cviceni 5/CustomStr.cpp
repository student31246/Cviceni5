#pragma once
#include "CustomStr.h"

//CONSTRUCTORS
#pragma region Constructors
CustomStr::CustomStr(const CustomStr& x)
{
	this->value = new char[strlen(x.value) + 1];

	for (int i = 0; i < strlen(x.value); i++)
		this->value[i] = x.value[i];

	this->value[strlen(x.value)] = '\0';
}

CustomStr::CustomStr(const char x[])
{
	this->value = new char[strlen(x) + 1];

	for (int i = 0; i < strlen(x); i++)
		this->value[i] = x[i];

	this->value[strlen(x)] = '\0';
}
#pragma endregion

//OPERATOR OVERLOAD
#pragma region Operator overloads

CustomStr& CustomStr::operator=(const CustomStr& s)
{
	if (this->value != nullptr)
		delete[] this->value;
	this->value = new char[strlen(s.value) + 1];

	for (int i = 0; i < strlen(s.value); i++)
		this->value[i] = s.value[i];

	this->value[strlen(s.value)] = '\0';

	return *this;
}

CustomStr& CustomStr::operator=(const char* s)
{
	if (this->value != nullptr)
		delete[] this->value;
	this->value = new char[strlen(s) + 1];

	for (int i = 0; i < strlen(s); i++)
		this->value[i] = s[i];

	this->value[strlen(s)] = '\0';

	return *this;
}

CustomStr CustomStr::operator+(const CustomStr& s)
{
	char* tmp;
	int len1 = strlen(this->value);
	int len2 = strlen(s.value);
	tmp = new char[len1 + len2 + 1];

	for (int i = 0; i < len1; i++)
		tmp[i] = this->value[i];

	for (int j = 0; j < len2; j++)
		tmp[j + len1] = s.value[j];

	tmp[len1 + len2] = '\0';
	CustomStr tmpStr(tmp);

	return tmpStr;
}

CustomStr& CustomStr::operator+=(const CustomStr& s)
{
	char* tmp;
	int len1 = strlen(this->value);
	int len2 = strlen(s.value);
	tmp = new char[len1 + len2 + 1];

	for (int i = 0; i < len1; i++)
		tmp[i] = this->value[i];

	for (int j = 0; j < len2; j++)
		tmp[j + len1] = s.value[j];

	tmp[len1 + len2] = '\0';

	delete[] this->value;
	this->value = tmp;

	return *this;
}

CustomStr CustomStr::operator+(char c)
{
	char* tmp;
	int len1 = strlen(this->value);
	tmp = new char[len1 + 2];

	for (int i = 0; i < len1; i++)
		tmp[i] = this->value[i];

	tmp[len1] = c;

	tmp[len1 + 1] = '\0';
	CustomStr tmpStr(tmp);

	return tmpStr;
}

CustomStr& CustomStr::operator+=(char c)
{
	char* tmp;
	int len1 = strlen(this->value);
	tmp = new char[len1 + 2];

	for (int i = 0; i < len1; i++)
		tmp[i] = this->value[i];

	tmp[len1] = c;

	tmp[len1 + 1] = '\0';

	delete[] this->value;
	this->value = tmp;

	return *this;
}

#pragma endregion

//FUNCTIONS
#pragma region Functions
void CustomStr::Copy(const char* pch, int len)
{
	if (this->value != nullptr)
		delete[] this->value;
	this->value = new char[len + 1];

	for (int i = 0; i < len; i++)
		this->value[i] = pch[i];

	this->value[len] = '\0';
}

void CustomStr::Copy(const char* pch, int len, int pos)
{
	if (this->value != nullptr)
		delete[] this->value;

	int newLen = len - pos + 1;
	this->value = new char[newLen + 1];

	for (int i = 0; i < newLen; i++)
		this->value[i] = pch[len - newLen + i];

	this->value[newLen] = '\0';
}

void CustomStr::Copy(const CustomStr& str)
{
	if (this->value != nullptr)
		delete[] this->value;
	int len = strlen(str.value);

	this->value = new char[len + 1];
	for (int i = 0; i < len; i++)
		this->value[i] = str.value[i];

	this->value[len] = '\0';
}
#pragma endregion