/**
* SSqlConnection�ӿ���
* ��װSQLһЩͨ�ò���-���ݿ�������
* @author ZeroX
* @version v1.0 08/08/2017
*/

#include "SSqlStatement.h"
#ifndef _SSQLCONNECTION_H_
#define _SSQLCONNECTION_H_

class SSqlConnection
{
public:
	//����
	virtual ~SSqlConnection(){ Close(); }

	virtual SSqlStatement CreateStatement() = 0 ;



	//�ر�����
	virtual void Close() = 0;
};

#endif