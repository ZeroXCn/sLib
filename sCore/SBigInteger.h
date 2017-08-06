/**
* SBigInteger
* ��������
* @author ???
* @version 0.1 beta
*/
#include "SObject.h"
#include "SException.h"
#ifndef _SBIGINTEGER_H_
#define _SBIGINTEGER_H_

#pragma warning (disable:4290)

#include <deque>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class DividedByZeroException :public SException{};

class SBigInteger :public SObject
{
private:
	vector<char> digits;
	bool sign;          //  true for positive, false for negitive
	void trim();        //  remove zeros in tail, but if the value is 0, keep only one:)
public:
	SBigInteger(int);    // construct with a int integer
	SBigInteger(string);
	SBigInteger();
	SBigInteger(const SBigInteger&);
	SBigInteger operator=(const SBigInteger& op2);
	SBigInteger operator=(string num);

	SBigInteger    abs() const;
	SBigInteger    pow(int a);

	string toString() const;

	//binary operators

	friend SBigInteger operator+=(SBigInteger&, const SBigInteger&);
	friend SBigInteger operator-=(SBigInteger&, const SBigInteger&);
	friend SBigInteger operator*=(SBigInteger&, const SBigInteger&);
	friend SBigInteger operator/=(SBigInteger&, const SBigInteger&) throw(DividedByZeroException);
	friend SBigInteger operator%=(SBigInteger&, const SBigInteger&) throw(DividedByZeroException);

	friend SBigInteger operator+(const SBigInteger&, const SBigInteger&);
	friend SBigInteger operator-(const SBigInteger&, const SBigInteger&);
	friend SBigInteger operator*(const SBigInteger&, const SBigInteger&);
	friend SBigInteger operator/(const SBigInteger&, const SBigInteger&) throw(DividedByZeroException);
	friend SBigInteger operator%(const SBigInteger&, const SBigInteger&) throw(DividedByZeroException);


	//uniary operators
	friend SBigInteger operator-(const SBigInteger&);   //negative

	friend SBigInteger operator++(SBigInteger&);        //++v
	friend SBigInteger operator++(SBigInteger&, int);    //v++
	friend SBigInteger operator--(SBigInteger&);        //--v
	friend SBigInteger operator--(SBigInteger&, int);    //v--

	friend bool operator>(const SBigInteger&, const SBigInteger&);
	friend bool operator<(const SBigInteger&, const SBigInteger&);
	friend bool operator==(const SBigInteger&, const SBigInteger&);
	friend bool operator!=(const SBigInteger&, const SBigInteger&);
	friend bool operator>=(const SBigInteger&, const SBigInteger&);
	friend bool operator<=(const SBigInteger&, const SBigInteger&);

	friend ostream& operator<<(ostream&, const SBigInteger&);    //print the SBigInteger
	friend istream& operator>>(istream&, SBigInteger&);         // input the SBigInteger

public:
	static const SBigInteger ZERO;
	static const SBigInteger ONE;
	static const SBigInteger TEN;
};

#endif