/**
* SSqlConnection��
* ��װ����ָ��,�Զ��ͷ�
* @author ZeroX
* @version v1.0 08/08/2017
*/

#include "SSqlConnectionImpl.h"
#ifndef _SSQLCONNECTION_H_
#define _SSQLCONNECTION_H_

#include <memory>

class SSqlConnection
{
private:
	std::shared_ptr<SSqlConnectionImpl> m_Ptr;
public:
	SSqlConnection(SSqlConnectionImpl *pConnectionImpl);
	~SSqlConnection();
public:
	//����״̬��
	SSqlStatementImpl *CreateStatement();

	void Close();
};

#endif