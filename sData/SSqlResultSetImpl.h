/**
* SSqlResultSet接口类
* 封装SQL一些通用操作-返回结果集
* @author ZeroX
* @version v1.0 08/08/2017
*/

#ifndef _SSQLRESULTSETIMPL_H_
#define _SSQLRESULTSETIMPL_H_
#include <string>

class SSqlResultSetImpl
{
public:
	// 总的列数   
	virtual int GetColumnCount() = 0;

	// 总的行数
	virtual int GetRowCount() = 0;

	//取得值
	virtual std::string GetValue(int nColumn) = 0;

	//取得字段名称
	virtual std::string GetColumnName(int nColumn) = 0;
public:
	//关闭记录集
	virtual void Close() = 0;

public:

	//游标往下移动
	virtual bool Next() = 0;

	//游标向上移动
	virtual bool Previous() = 0;

};

#endif