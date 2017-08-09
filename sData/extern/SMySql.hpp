/**
* SMysql��
* ��װMysql�ӿ�
* @author ZeroX
* @version v0.6 beta 09/08/2017
*/
/* �ӿ���δ����,�����ʹ�� */


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
	// �ܵ�����   
	int GetColumnCount()
	{
		//mysql_field_count();	//�鲻�����ؿ�-
		//mysql_num_fields()	//���쳣
		return mysql_num_fields(m_result);//����ʵ������
	}

	// �ܵ�����
	int GetRowCount()
	{
		// TODO��������ܴ������
		return (int)mysql_num_rows(m_result);
	
	}

	//ȡ��ֵ
	std::string GetValue(int nColumn)
	{
		return m_sql_row[nColumn];
	}


	//ȡ���ֶ�����
	std::string GetColumnName(int nColumn)
	{
		//ȡ�ֶμ�
		MYSQL_FIELD *fd; int i = 0;
		for (int i=0;fd = mysql_fetch_field(m_result);i++)
		{
			if (i == nColumn)
				return fd->name;

		}
		
		return "";
	}


public:

	//�رռ�¼��
	void Close()
	{
		mysql_free_result(m_result);
	}

public:

	//�α������ƶ�
	bool Next()
	{
		m_sql_row = mysql_fetch_row(m_result);
		return m_sql_row ? true:false;
	}

	//�α������ƶ�
	bool Previous()
	{
		//TODO:û�����ֲ���
		return false;
	}

};



class SMysqlStatement :public SSqlStatementImpl
{
private:
	MYSQL *m_myCont;
	//MYSQL_STMT *m_pStmt;	//���ô�����
public:
	SMysqlStatement(MYSQL *pCont):m_myCont(pCont){}
	SSqlResultSetImpl *ExcuteQuery(const char* lpSql)
	{
		int res;
		res = mysql_query(m_myCont, lpSql);//��ѯ
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
		return mysql_query(m_myCont, lpSql);//��ѯ
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
		//�ɹ������ñ����ʽ
		if (ret) {
			mysql_query(&m_myCont, "SET NAMES GBK"); return true;
		}
		else return false;

	}

	//�ر�����
	void DisConnect()
	{
		mysql_close(&m_myCont);
	}
};
typedef SMysqlConnection SMysql;


#endif

#endif