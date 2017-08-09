/**
* SSqlResultSet�ӿ���
* ��װSQLһЩͨ�ò���-���ؽ����
* @author ZeroX
* @version v1.0 08/08/2017
*/

#ifndef _SSQLRESULTSETIMPL_H_
#define _SSQLRESULTSETIMPL_H_
#include <string>

class SSqlResultSetImpl
{
public:
	// �ܵ�����   
	virtual int GetColumnCount() = 0;

	// �ܵ�����
	virtual int GetRowCount() = 0;

	//ȡ��ֵ
	virtual std::string GetValue(int nColumn) = 0;

	//ȡ���ֶ�����
	virtual std::string GetColumnName(int nColumn) = 0;
public:
	//�رռ�¼��
	virtual void Close() = 0;

public:

	//�α������ƶ�
	virtual bool Next() = 0;

	//�α������ƶ�
	virtual bool Previous() = 0;

};

#endif