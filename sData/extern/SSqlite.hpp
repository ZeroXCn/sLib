/**
* SSqlite��
* ��װSSqlite�ӿ�
* @author ZeroX
* @version v0.7 beta 09/08/2017
*/
/* �ӿ���δ����,�����ʹ�� */

#ifdef _SQLITE3_H_

#include "../SSqlConnectionImpl.h"
#include "../SSqlStatementImpl.h"
#include "../SSqlResultSetImpl.h"

#ifndef _SSQLITE_H_
#define _SSQLITE_H_

class SSqliteResultSet;
class SSqliteStatement;
class SSqliteConnection;

class SSqliteResultSet :public SSqlResultSetImpl
{
private:
	sqlite3_stmt* m_pStmt;
public:
	SSqliteResultSet(sqlite3_stmt *pStmt) :m_pStmt(pStmt){}
public:
	// �ܵ�����   
	int GetColumnCount()
	{
		return sqlite3_column_count(m_pStmt);
	}

	// �ܵ�����
	int GetRowCount()
	{
		int lnRows = 0;
		//����������ִ��sqlite3_step(m_pStmt),���ǻ�������һ����¼��
		sqlite3_reset(m_pStmt);
		sqlite3_step(m_pStmt);
		lnRows = sqlite3_data_count(m_pStmt);
		sqlite3_reset(m_pStmt);
		return lnRows;
	}

	//ȡ��ֵ
	std::string GetValue(const char *field)
	{
		//TODO:û�����ֲ���
		return "";
	}

	std::string GetValue(int nColumn)
	{
		return (const char *)sqlite3_column_text(m_pStmt, nColumn);
	}


	//ȡ���ֶ�����
	std::string GetColumnName(int nColumn)
	{
		return sqlite3_column_name(m_pStmt, nColumn);
	}


public:

	//�رռ�¼��
	void Close()
	{
		if (m_pStmt)
		{
			sqlite3_finalize(m_pStmt);
			m_pStmt = nullptr;
		}
	}

public:

	//�α������ƶ�
	bool Next()
	{
		if (m_pStmt == nullptr)
		{
			return false;
		}
		if (sqlite3_step(m_pStmt) != SQLITE_ROW)
		{
			return false;
		}
		return true;
	}

	//�α������ƶ�
	bool Previous()
	{
		//TODO:û���ⲽ����
		return false;
	}

};



class SSqliteStatement :public SSqlStatementImpl
{
private:
	sqlite3 *m_db;
public:
	SSqliteStatement(sqlite3 *db) :m_db(db){}

public:
	SSqlResultSetImpl *ExcuteQuery(const char* lpSql)
	{
		if (lpSql == nullptr)
		{
			return nullptr;
		}
		sqlite3_stmt* stmt;
		if (sqlite3_prepare_v2(m_db, lpSql, -1, &stmt, nullptr) != SQLITE_OK)
		{
			return nullptr;
		}
		return new SSqliteResultSet(stmt);
	}
	int Excute(const char* lpSql)
	{
		if (lpSql == nullptr)
		{
			return false;
		}
		sqlite3_stmt* stmt;

		if (sqlite3_prepare_v2(m_db, lpSql, -1, &stmt, NULL) != SQLITE_OK)
		{
			return false;
		}
		sqlite3_step(stmt);

		return (sqlite3_finalize(stmt) == SQLITE_OK) ? true : false;
	}
};

class SSqliteConnection :public SSqlConnectionImpl
{
protected:
	sqlite3 *m_db;
public:
	SSqlStatementImpl *CreateStatement()
	{
		if (m_db){
			return  new SSqliteStatement(m_db);
		}
		else return nullptr;
	}

	bool Connect(const char *host, const char *user, const char *pswd, const char *database, int port)
	{
		if (database == nullptr)
		{
			return false;
		}
		if (sqlite3_open(database, &m_db) != SQLITE_OK)
		{
			return false;
		}
		return true;
	}

	//�ر�����
	void DisConnect()
	{
		if (m_db)
		{
			sqlite3_close(m_db);
			m_db = nullptr;
		}
	}
};
typedef SSqliteConnection SSqlite;


#endif

#endif