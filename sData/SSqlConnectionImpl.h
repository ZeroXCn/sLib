/**
* SSqlConnectionImpl接口类
* 封装SQL一些通用操作-管理数据库连接
* @author ZeroX
* @version v1.0 08/08/2017
*/

#include "SSqlStatementImpl.h"

#ifndef _SSQLCONNECTIONIMPL_H_
#define _SSQLCONNECTIONIMPL_H_

class SSqlConnectionImpl
{
	//TODO:以下两个接口最好protected继承,实例交由SSqlDriverManager生成
public:
	//建立连接
	virtual bool Connect(const char *host, const char *user, const char *pswd, const char *database, int port) = 0;

	//连接断开
	virtual void DisConnect() = 0;

	//生成状态集
	virtual SSqlStatementImpl *CreateStatement() = 0;

};

#endif