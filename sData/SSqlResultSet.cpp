#include "SSqlResultSet.h"
using namespace std;

SSqlResultSet::SSqlResultSet()
{

}

SSqlResultSet::SSqlResultSet(SSqlResultSetImpl *pResultSetImpl) :m_Ptr(pResultSetImpl)
{

}


// �ܵ�����   
int SSqlResultSet::GetColumnCount()
{
	return m_Ptr->GetColumnCount();
}

// �ܵ�����
int SSqlResultSet::GetRowCount()
{
	return m_Ptr->GetRowCount();
}

//ȡ��ֵ
string SSqlResultSet::GetValue(int nColumn)
{
	return m_Ptr->GetValue(nColumn);
}

//ȡ���ֶ�����
string SSqlResultSet::GetColumnName(int nColumn)
{
	return m_Ptr->GetColumnName(nColumn);
}


//�رռ�¼��
void SSqlResultSet::Close()
{
	return m_Ptr->Close();
}


//�α������ƶ�
bool SSqlResultSet::Next()
{
	return m_Ptr->Next();
}

//�α������ƶ�
bool SSqlResultSet::Previous()
{
	return m_Ptr->Previous();
}

//���غ���++
SSqlResultSet &SSqlResultSet::operator ++(int){
	Next();
	return *this;
}


//���غ���--
SSqlResultSet &SSqlResultSet::operator --(int){ 
	Previous();
	return *this;
}

SSqlResultSet &SSqlResultSet::operator = (SSqlResultSetImpl *pResultSetImpl)
{
	m_Ptr.reset(pResultSetImpl);
	return *this;
}