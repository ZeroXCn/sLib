/**
* SSqlStatementImpl�ӿ���
* ��װSQLһЩͨ�ò���-�������ݿ�״̬
* @author ZeroX
* @version v1.0 08/08/2017
*/
#include "SSqlResultSetImpl.h"

#ifndef _SSQLSTATEMENTIMPL_H_
#define _SSQLSTATEMENTIMPL_H_

class SSqlStatementImpl
{
public:
	//��Ϊ�������޷����ض���,ֻ��ͨ��ָ����ʽ����

	//��ѯ,���ؽ����
	virtual SSqlResultSetImpl *ExcuteQuery(const char* lpSql) = 0;

	//��ѯ,�����ؽ��
	virtual int Excute(const char* lpSql) = 0;
};
#endif