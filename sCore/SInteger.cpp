#include "SInteger.h"
#include "SNumber.cpp"

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

SString SInteger::ToHexString()
{
	SString strHex;
	int &num = m_data;
	int len = sizeof(num)* 8;		//��λ��
	int iCount = len / 4;			//��ѭ������
	for (int i = iCount - 1; i >= 0; i--){
		unsigned char cTemp = (num >>  (4 * i));
		unsigned char cCur = (cTemp & 0x0f);
		if (cCur < 10){
			cCur += _T('0');
		}
		else{
			cCur += ((false ? _T('A') : _T('a')) - 10);
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