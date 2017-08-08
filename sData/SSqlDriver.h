/**
* SSqlDriver�ӿ���
* ��װSQLһЩͨ�ò���-���ݿ�������
* @author ZeroX
* @version v1.0 08/08/2017
*/

#ifndef _SSQLDRIVER_H_
#define _SSQLDRIVER_H_
class SSqlDriver
{
public:
	virtual bool Connect(const char *host, const char *user, const char *pswd, const char *database, int port) = 0;
	virtual bool Open(const char *path, const char *user = nullptr, const char *pswd = nullptr){ return Connect(nullptr, user, pswd, path, -1); }//��Ա������ݿ�


};

#endif