/**
* SSqlStatementImpl接口类
* 封装SQL一些通用操作-返回数据库状态
* @author ZeroX
* @version v1.0 08/08/2017
*/
#include "SSqlResultSetImpl.h"

#ifndef _SSQLSTATEMENTIMPL_H_
#define _SSQLSTATEMENTIMPL_H_

class SSqlStatementImpl
{
public:
	//因为抽象类无法返回对象,只能通过指针形式返回

	//查询,返回结果集
	virtual SSqlResultSetImpl *ExcuteQuery(const char* lpSql) = 0;

	//查询,不返回结果
	virtual int Excute(const char* lpSql) = 0;
};
#endif