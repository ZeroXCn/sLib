/**
* SSqlDriverManager类
* 驱动管理类-所有连接必须经过注册
* @author ZeroX
* @version v1.0 08/08/2017
*/


#include "SSqlConnectionImpl.h"

#ifndef _SSQLDRIVERMANAGER_H_
#define _SSQLDRIVERMANAGER_H_

#include <vector>

class SSqlDriverManager
{
private:
	static std::vector<SSqlConnectionImpl *> g_connectlist;
public:
	//注册连接
	template<class T>
	static T *GetConnection(const char *host, const char *user, const char *pswd, const char *database, int port);

	template<class T>
	static T *GetConnection(const char *path, const char *user = nullptr, const char *pswd = nullptr);

	//断开连接
	static bool DisConnection(SSqlConnectionImpl *);

};

#endif