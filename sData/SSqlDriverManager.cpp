#include "SSqlDriverManager.h"


std::vector<SSqlConnectionImpl *> SSqlDriverManager::g_connectlist;

///////////
template<class T>
T *SSqlDriverManager::GetConnection(const char *host, const char *user, const char *pswd, const char *database, int port)
{
	T *temp = new T();
	if (temp->Connect(host, user, pswd, database, port)){
		g_connectlist.push_back(temp);
		return temp;
	}
	else return nullptr;
}

template<class T>
T *SSqlDriverManager::GetConnection(const char *path, const char *user, const char *pswd)
{
	return SSqlDriverManager::GetConnection<T>(path, user, pswd, path, -1);
}

bool SSqlDriverManager::DisConnection(SSqlConnectionImpl *pConnection)
{
	for (std::vector<SSqlConnectionImpl *>::const_iterator it = g_connectlist.begin(); it != g_connectlist.end(); it++)
	{
		if (*it == pConnection){
			g_connectlist.erase(it);
			//delete *it;	//TODO:可能存在问题
			return true;
		}
	}
	return false;
}