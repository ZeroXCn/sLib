/**
* SSqlResultSet��
* ��װSQLһЩͨ�ò���-���ؽ����
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
	// �ܵ�����   
	int GetColumnCount();

	// �ܵ�����
	int GetRowCount();

	//ȡ��ֵ
	std::string GetValue(int nColumn);

	//ȡ���ֶ�����
	virtual std::string GetColumnName(int nColumn);
public:

	//�رռ�¼��
	void Close();

public:

	//�α������ƶ�
	bool Next();

	//�α������ƶ�
	bool Previous();

	//���غ���++
	SSqlResultSet &operator ++(int);

	//���غ���--
	SSqlResultSet &operator --(int);

public:
	SSqlResultSet &operator = (SSqlResultSetImpl *pSqlStatement);
};

#endif