#include "SSqlConnection.h"
#include "SSqlDriverManager.h"
using namespace std;

SSqlConnection::SSqlConnection(SSqlConnectionImpl *pConnectionImpl) :m_Ptr(pConnectionImpl)
{

}

//析构
SSqlConnection::~SSqlConnection(){
	Close();
}


void SSqlConnection::Close()
{
	m_Ptr->DisConnect();							//执行断开连接的操作
	SSqlDriverManager::DisConnection(m_Ptr.get());
}
SSqlStatementImpl *SSqlConnection::CreateStatement()
{
	return m_Ptr->CreateStatement();
}