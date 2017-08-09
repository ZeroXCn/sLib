/**
* SMysql类
* 封装Mysql接口
* @author ZeroX
* @version v0.6 beta 09/08/2017
*/
/* 接口善未完善,请谨慎使用 */


#ifdef _mysql_h

#include "../SSqlConnectionImpl.h"
#include "../SSqlStatementImpl.h"
#include "../SSqlResultSetImpl.h"

#ifndef _SMYSQL_H_
#define _SMYSQL_H_

class SMysqlResultSet;
class SMysqlStatement;
class SMysqlConnection;

class SMysqlResultSet :public SSqlResultSetImpl
{
private:
	MYSQL_RES *m_result;
	MYSQL_ROW m_sql_row;
public:
	SMysqlResultSet(MYSQL_RES *res) :m_result(m_result){}
	// 总的列数   
	int GetColumnCount()
	{
		//mysql_field_count();	//查不到返回空-
		//mysql_num_fields()	//会异常
		return mysql_num_fields(m_result);//返回实际列数
	}

	// 总的行数
	int GetRowCount()
	{
		// TODO：结果可能存在误差
		return (int)mysql_num_rows(m_result);
	
	}

	//取得值
	std::string GetValue(int nColumn)
	{
		return m_sql_row[nColumn];
	}


	//取得字段名称
	std::string GetColumnName(int nColumn)
	{
		//取字段集
		MYSQL_FIELD *fd; int i = 0;
		for (int i=0;fd = mysql_fetch_field(m_result);i++)
		{
			if (i == nColumn)
				return fd->name;

		}
		
		return "";
	}


public:

	//关闭记录集
	void Close()
	{
		mysql_free_result(m_result);
	}

public:

	//游标往下移动
	bool Next()
	{
		m_sql_row = mysql_fetch_row(m_result);
		return m_sql_row ? true:false;
	}

	//游标向上移动
	bool Previous()
	{
		//TODO:没有这种操作
		return false;
	}

};



class SMysqlStatement :public SSqlStatementImpl
{
private:
	MYSQL *m_myCont;
	//MYSQL_STMT *m_pStmt;	//作用待补充
public:
	SMysqlStatement(MYSQL *pCont):m_myCont(pCont){}
	SSqlResultSetImpl *ExcuteQuery(const char* lpSql)
	{
		int res;
		res = mysql_query(m_myCont, lpSql);//查询
		if (!res)
		{
			MYSQL_RES *result;
			result = mysql_store_result(m_myCont);
			if (result)
			{
				return new SMysqlResultSet(result);
			}
			else return nullptr;
		}
		else return nullptr;

	}
	int Excute(const char* lpSql)
	{
		return mysql_query(m_myCont, lpSql);//查询
	}
};

class SMysqlConnection :public SSqlConnectionImpl
{
private:
	MYSQL m_myCont;
public:
	SMysqlConnection(){ mysql_init(&m_myCont); }
	SSqlStatementImpl *CreateStatement()
	{
		return new SMysqlStatement(&m_myCont);
	}

	bool Connect(const char *host, const char *user, const char *pswd, const char *database, int port)
	{

		bool ret= mysql_real_connect(&m_myCont, host, user, pswd, database, port, NULL, 0)?true:false;
		//成功则设置编码格式
		if (ret) {
			mysql_query(&m_myCont, "SET NAMES GBK"); return true;
		}
		else return false;

	}

	//关闭链接
	void DisConnect()
	{
		mysql_close(&m_myCont);
	}
};
typedef SMysqlConnection SMysql;


#endif

#endif