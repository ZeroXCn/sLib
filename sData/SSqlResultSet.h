/**
* SSqlResultSet类
* 封装SQL一些通用操作-返回结果集
* @author ZeroX
* @version v1.0 08/08/2017
*/

#include "SSqlResultSetImpl.h"

#ifndef _SSQLRESULTSET_H_
#define _SSQLRESULTSET_H_

#include <string>
#include <memory>


class SSqlResultSet
{
private:
	std::shared_ptr<SSqlResultSetImpl> m_Ptr;
public:
	SSqlResultSet();
	SSqlResultSet(SSqlResultSetImpl *pResultSetImpl);
public:
	// 总的列数   
	int GetColumnCount();

	// 总的行数
	int GetRowCount();

	//取得值
	std::string GetValue(int nColumn);

	//取得字段名称
	virtual std::string GetColumnName(int nColumn);
public:

	//关闭记录集
	void Close();

public:

	//游标往下移动
	bool Next();

	//游标向上移动
	bool Previous();

	//重载后置++
	SSqlResultSet &operator ++(int);

	//重载后置--
	SSqlResultSet &operator --(int);

public:
	SSqlResultSet &operator = (SSqlResultSetImpl *pSqlStatement);
};

#endif