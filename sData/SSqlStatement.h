/**
* SSqlStatement�ӿ���
* ��װSQLһЩͨ�ò���-�������ݿ�״̬
* @author ZeroX
* @version v1.0 08/08/2017
*/
#include "SSqlResultSet.h"
#ifndef _SSQLSTATEMENT_H_
#define _SSQLSTATEMENT_H_
class SSqlStatement
{
public:
	//��ѯ,���ؽ����
	virtual SSqlResultSet ExcuteQuery(const char* lpSq) = 0;
	virtual int Excute(const char* lpSq) = 0;
};
#endif