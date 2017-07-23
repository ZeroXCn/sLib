/**
*
*	SInteger¿‡
*	Int∑‚◊∞¿‡
*	@author ZeroX
*	@version v1.0 22/07/2017()
*
*/
#include "SObject.h"
#include "SString.h"
#ifndef SINTEGER_H
#define SINTEGER_H

class SInteger :public SObject
{
private:
	int m_data;
public:
	SInteger(int data);
	SInteger(SString data);
public:
	int Value();
public:
	int IntValue();

public:
	static SInteger ValueOf(int i);
	static SInteger ValueOf(SString s);
	static SInteger ValueOf(SString s, int radix);

	SString ToString();
	static SString ToString(int i);
	static SString ToString(int i, int radix);

public:
	static int ParseInt(SString s);
	static int ParseInt(SString s, int radix);

};

#endif