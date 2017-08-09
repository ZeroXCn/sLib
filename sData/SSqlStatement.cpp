#include "SSqlStatement.h"
using namespace std;

SSqlStatement::SSqlStatement(SSqlStatementImpl *pSqlStatemenImpl) :m_Ptr(pSqlStatemenImpl)
{

}

SSqlResultSetImpl *SSqlStatement::ExcuteQuery(const char* lpSql)
{
	return m_Ptr->ExcuteQuery(lpSql);
}
int SSqlStatement::Excute(const char* lpSql)
{
	return m_Ptr->Excute(lpSql);
}

