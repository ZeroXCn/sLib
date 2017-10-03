#include <iostream>
#include <string>
#include <WINSOCK2.H>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
#define DEFAULT_PAGE_BUF_SIZE 1048576
class SocketTCP
{
private:
	int identity;
	WORD versionRequired;
	WSADATA wsaData;
	SOCKET MySocket;
	SOCKET serConn;  //用于服务端发送
	SOCKET *RecSenSocket;
	SOCKADDR_IN MySock_in;
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
	SocketTCP()
	{
		identity=-1;
	//	versionRequired=MAKEWORD(2,2); //有的设置为1，1
	//	WSAStartup(versionRequired,&wsaData);//协议库的版本信息
	}
	int Creat(char *add,int port,int maxconnum=5)
	{
		versionRequired=MAKEWORD(2,2);
		int err=WSAStartup(versionRequired,&wsaData);//协议库的版本信息
		if(err!=0)return err;
		MySocket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

		MySock_in.sin_family=AF_INET;
		MySock_in.sin_port=htons(port);

		//服务端的话进行绑定
		if(add==NULL){
			identity=0;
			MySock_in.sin_addr.S_un.S_addr=htonl(INADDR_ANY);//服务端
			bind(MySocket,(SOCKADDR*)&MySock_in,sizeof(SOCKADDR));//绑定完成
			listen(MySocket,maxconnum);//其中第二个参数代表能够接收的最多的连接数
			RecSenSocket=&serConn;
		}else//客户端的话
		{
			identity=1;
			MySock_in.sin_addr.S_un.S_addr=inet_addr(smtpIp(add));//ip地址(客户端)
			RecSenSocket=&MySocket;
		}
		return err; //!err打开成功
	}
	int Connect()
	{
		return connect(MySocket,(SOCKADDR*)&MySock_in,sizeof(SOCKADDR));//开始连接
	}
	int Connect(char *add,int port,int maxconnum=5)
	{
		if(Creat(add,port,maxconnum))return 0;
		return connect(MySocket,(SOCKADDR*)&MySock_in,sizeof(SOCKADDR));//开始连接

	}
	void Listen()
	{
		static SOCKADDR_IN clientsocket;
		static int len;
		len=sizeof(SOCKADDR);
		serConn=accept(MySocket,(SOCKADDR*)&clientsocket,&len);//如果这里不是accept而是conection的话。。就会不断的监听
	}
	string Receive(int *state=NULL,int count=99)
	{
		//此处接收字符串接收长度未知，不能给1024,现在一次缓冲1024个字节
		const int MAXLENGTH=1024;//设置缓存区大小
		char receiveBuf[MAXLENGTH];
		string result="";
		int _rev=0;
		do{
			memset(receiveBuf, 0, MAXLENGTH);//将前1024个字符置为0
			_rev=recv(*RecSenSocket,receiveBuf,MAXLENGTH,0);
			result+=receiveBuf;
			count--;
		}while(_rev>0 && count>0);
		if(state)*(state)=_rev;
		return result;
	}
	int Send(string sendBuf)
	{
		return send(*RecSenSocket,(char *)sendBuf.c_str(),sendBuf.length()+1,0);
	}
	void Close()
	{
		closesocket(MySocket);//关闭
		WSACleanup();//释放资源的操作
	}

}; 