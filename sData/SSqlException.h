/**
* SSqlException�ӿ���
* ��װSQLһЩͨ�ò���-�쳣��
* @author ZeroX
* @version v1.0 08/08/2017
*/

#ifndef _SSQLEXCEPTION_H_
#define _SSQLEXCEPTION_H_
#include <string>

class SSqlException
{
protected:
	std::string m_szDesc;
public:
	SSqlException(std::string szDesc = "") :m_szDesc(szDesc){}
	std::string GetDesc(){ return m_szDesc; }
};

#endif