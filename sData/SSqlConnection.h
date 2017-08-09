/**
* SSqlConnection类
* 封装连接指针,自动释放
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
	//生成状态集
	SSqlStatementImpl *CreateStatement();

	void Close();
};

#endif