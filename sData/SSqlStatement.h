/**
* SSqlStatement�ӿ���
* ��װSQLһЩͨ�ò���-�������ݿ�״̬
* @author ZeroX
* @version v1.0 08/08/2017
*/
#include "SSqlStatementImpl.h"

#ifndef _SSQLSTATEMENT_H_
#define _SSQLSTATEMENT_H_
#include <memory>

class SSqlStatement
{
private:
	std::shared_ptr<SSqlStatementImpl> m_Ptr;
public:
	SSqlStatement(SSqlStatementImpl *pSqlStatement);
public:
	SSqlResultSetImpl *ExcuteQuery(const char* lpSql);
	int Excute(const char* lpSql);


};
#endif