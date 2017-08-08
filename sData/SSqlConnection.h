/**
* SSqlConnection接口类
* 封装SQL一些通用操作-数据库驱动类
* @author ZeroX
* @version v1.0 08/08/2017
*/

#include "SSqlStatement.h"
#ifndef _SSQLCONNECTION_H_
#define _SSQLCONNECTION_H_

class SSqlConnection
{
public:
	//析构
	virtual ~SSqlConnection(){ Close(); }

	virtual SSqlStatement CreateStatement() = 0 ;



	//关闭链接
	virtual void Close() = 0;
};

#endif