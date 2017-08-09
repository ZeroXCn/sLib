#include "SSqlResultSet.h"
using namespace std;

SSqlResultSet::SSqlResultSet()
{

}

SSqlResultSet::SSqlResultSet(SSqlResultSetImpl *pResultSetImpl) :m_Ptr(pResultSetImpl)
{

}


// 总的列数   
int SSqlResultSet::GetColumnCount()
{
	return m_Ptr->GetColumnCount();
}

// 总的行数
int SSqlResultSet::GetRowCount()
{
	return m_Ptr->GetRowCount();
}

//取得值
string SSqlResultSet::GetValue(int nColumn)
{
	return m_Ptr->GetValue(nColumn);
}

//取得字段名称
string SSqlResultSet::GetColumnName(int nColumn)
{
	return m_Ptr->GetColumnName(nColumn);
}


//关闭记录集
void SSqlResultSet::Close()
{
	return m_Ptr->Close();
}


//游标往下移动
bool SSqlResultSet::Next()
{
	return m_Ptr->Next();
}

//游标向上移动
bool SSqlResultSet::Previous()
{
	return m_Ptr->Previous();
}

//重载后置++
SSqlResultSet &SSqlResultSet::operator ++(int){
	Next();
	return *this;
}


//重载后置--
SSqlResultSet &SSqlResultSet::operator --(int){ 
	Previous();
	return *this;
}

SSqlResultSet &SSqlResultSet::operator = (SSqlResultSetImpl *pResultSetImpl)
{
	m_Ptr.reset(pResultSetImpl);
	return *this;
}