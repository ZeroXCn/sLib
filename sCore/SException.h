/**
*
*	SException��
*	�쳣�������
*	@author ZeroX
*	@version v1.0 22/07/2017(03/02/2017)
*
*/
#include "SObject.h"
#include "SString.h"

#ifndef SEXCEPTION_H
#define SEXCEPTION_H

using namespace std;
class SException:public SObject
{
private:
	int m_nTime;			//�쳣ʱ��
	SString m_strOri;		//�쳣��Դ
	SString m_strDesc;		//��¼�쳣��������
protected:

public:
	SException();
	SException(SString m_strDesc);
	SException(SString strOri, const TCHAR* pszFormat, ...);
public:
	int GetTime();
	SString GetDesc();
	SString GetOri();

	virtual void Print();
	virtual void PrintException();

};

#endif