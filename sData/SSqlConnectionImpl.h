/**
* SSqlConnectionImpl�ӿ���
* ��װSQLһЩͨ�ò���-�������ݿ�����
* @author ZeroX
* @version v1.0 08/08/2017
*/

#include "SSqlStatementImpl.h"

#ifndef _SSQLCONNECTIONIMPL_H_
#define _SSQLCONNECTIONIMPL_H_

class SSqlConnectionImpl
{
	//TODO:���������ӿ����protected�̳�,ʵ������SSqlDriverManager����
public:
	//��������
	virtual bool Connect(const char *host, const char *user, const char *pswd, const char *database, int port) = 0;

	//���ӶϿ�
	virtual void DisConnect() = 0;

	//����״̬��
	virtual SSqlStatementImpl *CreateStatement() = 0;

};

#endif