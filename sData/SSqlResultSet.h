/**
* SSqlResultSet�ӿ���
* ��װSQLһЩͨ�ò���-���ؽ����
* @author ZeroX
* @version v1.0 08/08/2017
*/
/* ResultSetMap�Ľ���� */
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
	// �ܵ�����   
	virtual int GetColumnCount() = 0;

	// �ܵ�����
	virtual int GetRowCount() = 0;

	//ȡ��ֵ
	virtual string GetValue(const char *field) = 0;
	virtual string GetValue(int nColumn){ return GetValue(GetField(nColumn).c_str()); }

	//ȡ���ֶ�����
	virtual string GetColumnName(int nColumn) = 0;

	SSqlStatement *GetStatement(){ return m_pSqlStatement; }
public:
	SSqlResultSet(SSqlStatement *pStatement=NULL) :m_pSqlStatement(pStatement){}
	//����
	virtual ~SSqlResultSet(){ Close(); }

	//�رռ�¼��
	virtual void Close() = 0;

	//��¼���Ƿ��Ѿ��ر�
	virtual bool isClosed() = 0;
public:

	//�α������ƶ�
	virtual bool Next() = 0;

	//�α������ƶ�
	virtual bool Previous() = 0;

	//���غ���++
	virtual SSqlResultSet &operator ++(int){ Next(); }

	//���غ���--
	virtual SSqlResultSet &operator --(int){ Previous(); }

};

#endif