#include "SSqlConnection.h"
#include "SSqlDriverManager.h"
using namespace std;

SSqlConnection::SSqlConnection(SSqlConnectionImpl *pConnectionImpl) :m_Ptr(pConnectionImpl)
{

}

//����
SSqlConnection::~SSqlConnection(){
	Close();
}


void SSqlConnection::Close()
{
	m_Ptr->DisConnect();							//ִ�жϿ����ӵĲ���
	SSqlDriverManager::DisConnection(m_Ptr.get());
}
SSqlStatementImpl *SSqlConnection::CreateStatement()
{
	return m_Ptr->CreateStatement();
}