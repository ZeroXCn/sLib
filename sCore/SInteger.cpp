#include "SInteger.h"

const int SInteger::MAX_VALUE = INT_MAX;
const int SInteger::MIN_VALUE = INT_MIN;
const int SInteger::SIZE = sizeof(int);
//
SInteger SInteger::ValueOf(int i)
{
	return SInteger(i);
}
SInteger SInteger::ValueOf(SString s)
{
	return SInteger(s.toInt());
}

SString SInteger::ToHexString(int num, bool bIsUpper)
{
	SString strHex;
	int len = sizeof(num)* 8;		//总位数
	int iCount = len / 4;			//总循环次数
	for (int i = iCount - 1; i >= 0; i--){
		unsigned char cTemp = (num >>  (4 * i));
		unsigned char cCur = (cTemp & 0x0f);
		if (cCur < 10){
			cCur += _T('0');
		}
		else{
			cCur += ((bIsUpper ? _T('A') : _T('a')) - 10);
		}

		strHex += cCur;
	}
	
	return strHex;
}

int SInteger::ParseInt(SString s)
{
	return s.toInt();
}


//
SInteger::SInteger(int data) :SNumber(data)
{

}