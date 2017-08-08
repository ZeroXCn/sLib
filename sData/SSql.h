/**
* SSql接口类
* 封装SQL一些通用操作-具体由对应数据库实现
* @author ZeroX
* @version v1.0 08/08/2017
*/
/* 所有操作必须有具体数据库继承重写实现 */

#ifndef _SSQL_H_
#define _SSQL_H_
#include <vector>
#include <map>
using namespace std;
class SSql
{
public:
	//连接数据库地址,用户名,密码,数据库,端口
	virtual bool Connect(const char *host, const char *user, const char *pswd, const char *database, int port) = 0;
	virtual bool Open(const char *path, const char *user = nullptr, const char *pswd = nullptr){ return Connect(nullptr, user, pswd, path, -1); }//针对本地数据库

	//关闭链接
	virtual void Close() = 0;

public:
	//查询,返回结果集
	virtual map<string,vector<string> > ExcuteQuery(const char* lpSq) = 0;
	virtual int ExcuteNonQuery(const char* lpSq) = 0;
};

#endif