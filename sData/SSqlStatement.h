/**
* SSqlStatement接口类
* 封装SQL一些通用操作-返回数据库状态
* @author ZeroX
* @version v1.0 08/08/2017
*/
#include "SSqlResultSet.h"
#ifndef _SSQLSTATEMENT_H_
#define _SSQLSTATEMENT_H_
class SSqlStatement
{
public:
	//查询,返回结果集
	virtual SSqlResultSet ExcuteQuery(const char* lpSq) = 0;
	virtual int Excute(const char* lpSq) = 0;
};
#endif