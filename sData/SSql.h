/**
* SSql�ӿ���
* ��װSQLһЩͨ�ò���-�����ɶ�Ӧ���ݿ�ʵ��
* @author ZeroX
* @version v1.0 08/08/2017
*/
/* ���в��������о������ݿ�̳���дʵ�� */

#ifndef _SSQL_H_
#define _SSQL_H_
#include <vector>
#include <map>
using namespace std;
class SSql
{
public:
	//�������ݿ��ַ,�û���,����,���ݿ�,�˿�
	virtual bool Connect(const char *host, const char *user, const char *pswd, const char *database, int port) = 0;
	virtual bool Open(const char *path, const char *user = nullptr, const char *pswd = nullptr){ return Connect(nullptr, user, pswd, path, -1); }//��Ա������ݿ�

	//�ر�����
	virtual void Close() = 0;

public:
	//��ѯ,���ؽ����
	virtual map<string,vector<string> > ExcuteQuery(const char* lpSq) = 0;
	virtual int ExcuteNonQuery(const char* lpSq) = 0;
};

#endif