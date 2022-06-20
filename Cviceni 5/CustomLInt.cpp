#pragma once
#include "CustomLInt.h"
#include <iostream>
#include "CustomStr.h"

//CONSTRUCTORS
#pragma region Constructors
CustomLInt::CustomLInt(const char x)
{
	this->sign = true;
	this->value = new char[strlen(&x) + 1];
	this->value[0] = x;
	this->value[1] = '\0';
}

CustomLInt::CustomLInt(char* x)
{
	if (x[0] == '-')
	{
		this->sign = '-';
		this->value = new char[strlen(x)];

		strcpy_s(this->value, strlen(x), &x[1]);
	}
	else
	{
		this->sign = '+';
		this->value = new char[strlen(x) + 1];
		strcpy_s(this->value, strlen(x) + 1, x);
	}
}

CustomLInt::CustomLInt(const CustomLInt& x)
{
	this->sign = x.sign;
	this->value = new char[strlen(x.value) + 1];

	for (int i = 0; i < strlen(x.value); i++)
		this->value[i] = x.value[i];

	this->value[strlen(x.value)] = '\0';
}

CustomLInt::CustomLInt(int n)
{
	if (n < 0)
	{
		this->sign = '-';
		n = -n;
	}
	else
		this->sign = '+';

	int length = 1;
	int tmpNum = n;

	if (tmpNum != 0)
	{
		for (length = 0; tmpNum != 0; length++)
			tmpNum /= 10;
	}
	this->value = new char[length + 1];
	for (int i = length - 1; i >= 0; i--)
	{
		this->value[i] = (n % 10) + '0';
		n = n / 10;
	}
	this->value[length] = '\0';		
}
#pragma endregion

#pragma region Operators
//OPERATOR OVERLOAD
CustomLInt& CustomLInt::operator=(const CustomLInt& s)
{
	delete[] this->value;
	this->value = new char[strlen(s.value) + 1];

	for (int i = 0; i < strlen(s.value); i++)
		this->value[i] = s.value[i];

	this->value[strlen(s.value)] = '\0';
	this->sign = s.sign;

	return *this;
}

CustomLInt& CustomLInt::operator=(const char* s)
{
	delete[] this->value;
	this->value = new char[strlen(s) + 1];

	for (int i = 0; i < strlen(s); i++)
		this->value[i] = s[i];

	this->value[strlen(s)] = '\0';

	return *this;
}

CustomLInt& CustomLInt::operator=(int n)
{
	int length = log10(n) + 2;

	if(this->value != nullptr)
		delete[] this->value;

	this->value = new char[length];

	sprintf_s(this->value, length, "%d", n);

	return *this;
}

CustomLInt CustomLInt::operator+(CustomLInt& lint)
{
	CustomLInt a = CustomLIntAdd(*this, lint);
	return a;
}

CustomLInt& CustomLInt::operator += (CustomLInt& n)
{
	*this = CustomLIntAdd(*this, n);
	return *this;
}

CustomLInt CustomLInt::operator-(CustomLInt& lint)
{
	CustomLInt a = CustomLIntSub(*this, lint);
	return a;
}

CustomLInt& CustomLInt::operator-=(CustomLInt& lint)
{
	*this = CustomLIntSub(*this, lint);
	return *this;
}

CustomLInt CustomLInt::operator * (CustomLInt& n)
{
	CustomLInt a = CustomLIntMultiply(*this, n);
	return a;
}

CustomLInt& CustomLInt::operator *= (CustomLInt& n)
{
	*this = CustomLIntMultiply(*this, n);
	return *this;
}

CustomLInt CustomLInt::operator / (CustomLInt& n)
{
	CustomLInt a = CustomIntDivide(*this, n);
	return a;
}

CustomLInt& CustomLInt::operator /= (CustomLInt& n)
{
	*this = CustomIntDivide(*this, n);
	return *this;
}

#pragma endregion

#pragma region Functions

//FUNCTIONS

void CustomLInt::Copy(int num)
{
	if (this->value != nullptr)
		delete[] this->value;

	int len = log10(num)+1;
	this->value = new char[len + 1];

	_itoa_s(num, this->value, len + 1, 10);
}

void CustomLInt::Copy(const CustomLInt& num)
{
	if (this->value != nullptr)
		delete[] this->value;

	int len = strlen(num.value);
	this->value = new char[len + 1];

	for (int i = 0; i < len; i++)
		this->value[i] = num.value[i];

	this->value[len] = '\0';
}

int CustomLInt::CompareAbs(CustomLInt& a, CustomLInt& b)
{
	int lenA = strlen(a.GetValue());
	int lenB = strlen(b.GetValue());

	if (lenA > lenB)
		return 1;
	else if (lenA < lenB)
		return -1;
	else
	{
		for (int i = 0; i < lenA; i++)
		{
			if (a.GetValue()[i] - '0' == b.GetValue()[i] - '0')
				continue;
			if (a.GetValue()[i] - '0' < b.GetValue()[i] - '0')
				return -1;
			if (a.GetValue()[i] - '0' > b.GetValue()[i] - '0')
				return 1;
		}
	}
	return 0;
}

int CustomLInt::Compare(CustomLInt& a, CustomLInt& b)
{
	if (a.GetSign() == '+' && b.GetSign() == '-')
		return 1;
	if (a.GetSign() == '-' && b.GetSign() == '+')
		return -1;
	if (a.GetSign() == '+' && b.GetSign() == '+')
		return CompareAbs(a, b);
	if (a.GetSign() == '-' && b.GetSign() == '-')
		return CompareAbs(a, b);
}

void CustomLInt::CustomLIntTrim(CustomLInt& a)
{
	int i = 0;
	while (a.value[i] == '0')
		i++;

	if (i != 0)
	{
		int newLen = strlen(a.value) - i;
		char* tmp = new char[newLen + 1];
		strcpy_s(tmp, newLen + 1, &a.value[i]);
		delete[] a.value;
		a.value = tmp;
	}
	if (strcmp(a.value, "") == 0)
	{
		delete[] a.value;
		a.value = new char[2];
		a.value[0] = '0';
		a.value[1] = '\0';
	}
}

void CustomLInt::CustomLIntSwap(CustomLInt& a)
{
	for (int i = 0, j = strlen(a.value) - 1; i < j; i++, j--)
		swap(a.value[i], a.value[j]);
}

CustomLInt CustomLInt::CustomLIntAdd(CustomLInt& a, CustomLInt& b)
{
	CustomLInt tmpA(a);
	int lenA = strlen(tmpA.value);
	CustomLIntSwap(tmpA);

	CustomLInt tmpB(b);
	int lenB = strlen(b.value);
	CustomLIntSwap(tmpB);

	bool aBigger = false;
	CustomLInt resultInt(0);
	int i = 0;
	int reminder = 0;

	if (lenA > lenB) 
	{
		delete[] resultInt.value;
		resultInt.value = new char[lenA + 1];
		resultInt.value[lenA] = '\0';
		aBigger = true;
	}
	else if (lenB > lenA)
	{
		delete[] resultInt.value;
		resultInt.value = new char[lenB + 1];
		resultInt.value[lenB] = '\0';
		aBigger = false;
	}		
	else
	{
		delete[] resultInt.value;
		resultInt.value = new char[lenA + 1];
		resultInt.value[lenA] = '\0';
	}		

	if (tmpA.GetSign() == tmpB.GetSign())
	{
		for (i = 0; aBigger ? i < lenB : i < lenA; i++)
		{
			reminder += (tmpA.value[i]-'0') + (tmpB.value[i]-'0');
			resultInt.value[i] = reminder % 10 + '0';
			reminder /= 10;
		}
		for (i; aBigger?i < lenA:i<lenB; i++)
		{
			reminder += aBigger? (tmpA.value[i] - '0'):(tmpB.value[i]-'0');
			resultInt.value[i] = reminder % 10 + '0';
			reminder /= 10;
		}
		resultInt.sign = tmpA.sign;

		if (reminder > 0)
		{
			char* tmp = new char[strlen(resultInt.value) + 2];

			for (int i = 0; i < strlen(resultInt.value); i++)
				tmp[i] = resultInt.value[i];

			tmp[strlen(resultInt.value)] = reminder+'0';
			tmp[strlen(resultInt.value) + 1] = '\0';

			delete[] resultInt.value;
			resultInt.value = tmp;
		}

		for (int i = 0, j = strlen(resultInt.value) - 1; i < j; i++, j--)
			swap(resultInt.value[i], resultInt.value[j]);

		CustomLIntTrim(resultInt);
		return resultInt;
	}
	else
	{
		if (tmpA.sign == '-')
		{
			CustomLInt tmpLInt = tmpA;
			tmpA = tmpB;
			tmpB = tmpLInt;
		}

		CustomLIntSwap(tmpA);
		CustomLIntSwap(tmpB);
		int absCmp = CompareAbs(tmpA, tmpB);
		CustomLIntSwap(tmpA);
		CustomLIntSwap(tmpB);

		if (absCmp == 0)
		{
			delete[] resultInt.value;

			resultInt.value = new char[2];
			resultInt.value[0] = '0';
			resultInt.value[1] = '\0';

			return resultInt;
		}
		else if (absCmp > 0)
		{
			tmpB.sign = '+';

			CustomLIntSwap(tmpA);
			CustomLIntSwap(tmpB);

			resultInt = CustomLIntSub(tmpA, tmpB);
			return resultInt;
		}
		else
		{
			tmpB.sign = '+';

			CustomLIntSwap(tmpA);
			CustomLIntSwap(tmpB);

			resultInt = CustomLIntSub(tmpB, tmpA);
			resultInt.sign = '-';
			return resultInt;
		}
	}
}

CustomLInt CustomLInt::CustomLIntSub(CustomLInt& a, CustomLInt& b)
{
	CustomLInt tmpA(a);
	int lenA = strlen(tmpA.value);
	CustomLIntSwap(tmpA);

	CustomLInt tmpB(b);
	int lenB = strlen(b.value);
	CustomLIntSwap(tmpB);

	bool aBigger = false;
	int i = 0;
	int reminder = 0;
	CustomLInt resultInt(0);

	if (tmpB.sign == '-')               //if tmpA - -tmpB = tmpA+tmpB
	{
		tmpB.sign = '+';
		CustomLIntSwap(tmpA);
		CustomLIntSwap(tmpB);
		resultInt = CustomLIntAdd(tmpA, tmpB);
		return resultInt;
	}

	if (tmpA.sign == '-')				//if -tmpA - tmpB = - tmpA+tmpB
	{
		tmpA.sign = '+';
		CustomLIntSwap(tmpA);
		CustomLIntSwap(tmpB);
		resultInt = CustomLIntAdd(tmpA, tmpB);
		resultInt.sign = '-';
		return resultInt;
	}

	CustomLIntSwap(tmpA);
	CustomLIntSwap(tmpB);
	int absCmp = CompareAbs(tmpA, tmpB);
	CustomLIntSwap(tmpA);
	CustomLIntSwap(tmpB);

	if (absCmp == 0)
	{
		delete[] resultInt.value;
		resultInt.value = new char[2];
		resultInt.value[0] = '0';
		resultInt.value[1] = '\0';
		return resultInt;
	}
	if (absCmp < 0)
	{
		CustomLInt tmp = tmpA;
		tmpA = tmpB;
		tmpB = tmp;
		CustomLIntSwap(tmpA);
		CustomLIntSwap(tmpB);
		resultInt = (tmpA, tmpB);
		if (resultInt.sign == '+')
			resultInt.sign = '-';
		else
			resultInt.sign = '+';
		return resultInt;
	}

	if (lenA > lenB)
	{
		delete[] resultInt.value;
		resultInt.value = new char[lenA + 1];
		resultInt.value[lenA] = '\0';
		aBigger = true;
	}
	else if (lenB > lenA)
	{
		delete[] resultInt.value;
		resultInt.value = new char[lenB + 1];
		resultInt.value[lenB] = '\0';
		aBigger = false;
	}
	else
	{
		delete[] resultInt.value;
		resultInt.value = new char[lenA + 1];
		resultInt.value[lenA] = '\0';
		aBigger = true;
	}

	for (i = 0; aBigger ? i < lenB : i < lenA; i++)
	{
		reminder = (tmpA.value[i] - '0') - (tmpB.value[i] - '0') - reminder;
		resultInt.value[i] = ((reminder + 10) % 10) + '0';
		if (reminder < 0)
			reminder = 1;
		else
			reminder = 0;
	}
	for (i; aBigger ? i < lenA : i < lenB; i++)
	{
		reminder = aBigger ? (tmpA.value[i] - '0')-reminder : (tmpB.value[i] - '0') - reminder;
		resultInt.value[i] = ((reminder + 10) % 10) + '0';
		if (reminder < 0)
			reminder = 1;
		else
			reminder = 0;
	}
	resultInt.sign = tmpA.sign;
	CustomLIntSwap(resultInt);
	CustomLIntTrim(resultInt);
	return resultInt;
}

CustomLInt CustomLInt::CustomLIntMultiply(CustomLInt& a, CustomLInt& b)
{
	int i  = 0;
	int j = 0;
	CustomLInt tmpA(a);
	int lenA = strlen(tmpA.value);

	CustomLInt tmpB(b);
	int lenB = strlen(tmpB.value);

	CustomLInt resultInt(0);
	int reminder = 0;

	if (tmpA.sign != tmpB.sign)
		resultInt.sign = '-';
	else
		resultInt.sign = '+';

	delete[] resultInt.value;
	resultInt.value = new char[lenA + lenB + 2];
	resultInt.value[lenA + lenB + 1] = '\0';
	for (int i = 0; i < lenA + lenB+1; i++)
		resultInt.value[i] = 0 + '0';

	for (i = lenA - 1; i >= 0; i--)
	{
		for (j = lenB - 1; j >= 0; j--)
		{
			char debugA = tmpA.value[i];
			char debugB = tmpB.value[j];

			reminder = (tmpA.value[i] -'0') * (tmpB.value[j] -'0') + reminder;

			int midRes = (resultInt.value[i + j + 2] - '0') + (reminder % 10);
			reminder += midRes / 10*10;
			midRes %= 10;
			char debugRes = resultInt.value[i + j + 2];
			resultInt.value[i + j + 2] = midRes +'0';
			reminder /= 10;
		}
		resultInt.value[i+j+2] = reminder + '0';
		reminder /= 10;
		j = 0;
	}
	resultInt.value[0] = reminder + '0';
	CustomLIntTrim(resultInt);
	return resultInt;
}

CustomLInt CustomLInt::CustomIntDivide(CustomLInt& a, CustomLInt& b)
{

	int counter = 0;
	CustomLInt resultInt(1);
	CustomLInt tmpA(a);
	CustomLInt tmpB(b);
	CustomStr res('0');
	CustomLInt startB(b);
	bool enough = false;

	if (strcmp(tmpB.GetValue(),"0") == 0)
		throw overflow_error("Divide by zero not allowed)");

	res = tmpB.value;

	while (strlen(res.GetValue()) < strlen(tmpA.value))
		res += '0';
	cout <<"tmpA len = "<<strlen(tmpA.value)<< "    res len = "<< strlen(res.GetValue()) << endl;
	tmpB = res.GetValue();
	res = '0';

	if (a.sign == b.sign)
		resultInt.sign = b.sign;
	else
	{
		resultInt.sign = '-';
		tmpA.sign = '+';
		tmpB.sign = '+';
	}		

	while (!enough)
	{
		while (CompareAbs(tmpA, tmpB) > 0)
		{
			tmpA=CustomLIntSub(tmpA, tmpB);
			counter++;
		}
		res += counter + '0';
		counter = 0;

		while(strlen(tmpB.value) >= strlen(tmpA.value))
		{
			if (strcmp(tmpB.value, startB.value)==0)
				enough = true;
			cout << "tmpB len before: " << strlen(tmpB.value);
			char* pTmp = new char[strlen(tmpB.value)];
			pTmp[strlen(tmpB.value)-1] = '\0';
			for (int i = 0; i < strlen(pTmp); i++)
				pTmp[i] = tmpB.value[i];
			delete[] tmpB.value;
			tmpB.value = pTmp;
			cout << "                             After: " << strlen(tmpB.value) << endl;
		}
		
	}
	resultInt = res.GetValue();
	CustomLIntTrim(resultInt);
	return resultInt;
}
#pragma endregion