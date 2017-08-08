/**
* SSqlResultSet接口类
* 封装SQL一些通用操作-返回结果集
* @author ZeroX
* @version v1.0 08/08/2017
*/
/* ResultSetMap的结合体 */
#ifndef _SSQLRESULTSET_H_
#define _SSQLRESULTSET_H_
#include "SSqlStatement.h"

#include <string>
using namespace std;

class SSqlResultSet
{
protected:
	SSqlStatement *m_pSqlStatement;
public:
	// 总的列数   
	virtual int GetColumnCount() = 0;

	// 总的行数
	virtual int GetRowCount() = 0;

	//取得值
	virtual string GetValue(const char *field) = 0;
	virtual string GetValue(int nColumn){ return GetValue(GetField(nColumn).c_str()); }

	//取得字段名称
	virtual string GetColumnName(int nColumn) = 0;

	SSqlStatement *GetStatement(){ return m_pSqlStatement; }
public:
	SSqlResultSet(SSqlStatement *pStatement=NULL) :m_pSqlStatement(pStatement){}
	//析构
	virtual ~SSqlResultSet(){ Close(); }

	//关闭记录集
	virtual void Close() = 0;

	//记录集是否已经关闭
	virtual bool isClosed() = 0;
public:

	//游标往下移动
	virtual bool Next() = 0;

	//游标向上移动
	virtual bool Previous() = 0;

	//重载后置++
	virtual SSqlResultSet &operator ++(int){ Next(); }

	//重载后置--
	virtual SSqlResultSet &operator --(int){ Previous(); }

};

#endif