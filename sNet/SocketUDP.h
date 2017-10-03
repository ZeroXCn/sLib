#include <iostream>
#include <string>
#include <WINSOCK2.H>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
#define DEFAULT_PAGE_BUF_SIZE 1048576
class SocketUDP
{
private:
	int identity;
	WSADATA wsaData;
	SOCKET MySocket;
	SOCKADDR_IN MySock_in;
	SOCKADDR_IN serSockin;

	SOCKADDR_IN *remoteAddr;
	int nAddrLen;

	char *smtpIp(char *url)
	{
		struct hostent *hp;
		hp = gethostbyname(url);
		struct in_addr inAddr;
		LPSTR lpAddr;
		lpAddr = hp->h_addr;
		memmove(&inAddr,lpAddr,4);
		return inet_ntoa(inAddr);
	}
	
public:
	SocketUDP()
	{
		identity=-1;
	}
	int Creat(char *add,int port)
	{
		WORD sockVersion=MAKEWORD(2,2);
		int err=WSAStartup(sockVersion,&wsaData);//协议库的版本信息
		if(err!=0)return err;

		MySocket=socket(AF_INET,SOCK_DGRAM, IPPROTO_UDP);
		if(MySocket == INVALID_SOCKET) return -1;

		MySock_in.sin_family=AF_INET;
		MySock_in.sin_port=htons(port); 

		//服务端的话进行绑定
		if(add==NULL){
			identity=0;
			MySock_in.sin_addr.S_un.S_addr=htonl(INADDR_ANY);//服务端
			bind(MySocket,(SOCKADDR*)&MySock_in,sizeof(MySock_in));//绑定完成
			remoteAddr=&serSockin;
		}else//客户端的话
		{
			identity=1;
			MySock_in.sin_addr.S_un.S_addr=inet_addr(smtpIp(add));//ip地址(客户端)
			remoteAddr=&MySock_in;
		}
		nAddrLen = sizeof(*remoteAddr);
		return err; //!err打开成功
	}
	
	string Receive(int *state=NULL)
	{
		//此处接收字符串接收长度未知，不能给1024,现在一次缓冲1024个字节
		const int MAXLENGTH=255;//设置缓存区大小
		char receiveBuf[MAXLENGTH];
		string result="";
		int _rev=0;
		do{
			memset(receiveBuf, 0, MAXLENGTH);//将前MAXLENGTH个字符置为0
			_rev=recvfrom(MySocket, receiveBuf, MAXLENGTH, 0,  (SOCKADDR *)remoteAddr, &nAddrLen);
			result+=receiveBuf;
		}while(_rev>0);
		if(state)*(state)=_rev;
		return result;
	}
	int Send(string sendBuf)
	{
		return sendto(MySocket, (char *)sendBuf.c_str(), sendBuf.length()+1, 0, (SOCKADDR *)remoteAddr, nAddrLen); 
	}
	void Close()
	{
		closesocket(MySocket);//关闭
		WSACleanup();//释放资源的操作
	}

}; 