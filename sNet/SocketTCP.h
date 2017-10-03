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
	SOCKET serConn;  //���ڷ���˷���
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
	//	versionRequired=MAKEWORD(2,2); //�е�����Ϊ1��1
	//	WSAStartup(versionRequired,&wsaData);//Э���İ汾��Ϣ
	}
	int Creat(char *add,int port,int maxconnum=5)
	{
		versionRequired=MAKEWORD(2,2);
		int err=WSAStartup(versionRequired,&wsaData);//Э���İ汾��Ϣ
		if(err!=0)return err;
		MySocket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

		MySock_in.sin_family=AF_INET;
		MySock_in.sin_port=htons(port);

		//����˵Ļ����а�
		if(add==NULL){
			identity=0;
			MySock_in.sin_addr.S_un.S_addr=htonl(INADDR_ANY);//�����
			bind(MySocket,(SOCKADDR*)&MySock_in,sizeof(SOCKADDR));//�����
			listen(MySocket,maxconnum);//���еڶ������������ܹ����յ�����������
			RecSenSocket=&serConn;
		}else//�ͻ��˵Ļ�
		{
			identity=1;
			MySock_in.sin_addr.S_un.S_addr=inet_addr(smtpIp(add));//ip��ַ(�ͻ���)
			RecSenSocket=&MySocket;
		}
		return err; //!err�򿪳ɹ�
	}
	int Connect()
	{
		return connect(MySocket,(SOCKADDR*)&MySock_in,sizeof(SOCKADDR));//��ʼ����
	}
	int Connect(char *add,int port,int maxconnum=5)
	{
		if(Creat(add,port,maxconnum))return 0;
		return connect(MySocket,(SOCKADDR*)&MySock_in,sizeof(SOCKADDR));//��ʼ����

	}
	void Listen()
	{
		static SOCKADDR_IN clientsocket;
		static int len;
		len=sizeof(SOCKADDR);
		serConn=accept(MySocket,(SOCKADDR*)&clientsocket,&len);//������ﲻ��accept����conection�Ļ������ͻ᲻�ϵļ���
	}
	string Receive(int *state=NULL,int count=99)
	{
		//�˴������ַ������ճ���δ֪�����ܸ�1024,����һ�λ���1024���ֽ�
		const int MAXLENGTH=1024;//���û�������С
		char receiveBuf[MAXLENGTH];
		string result="";
		int _rev=0;
		do{
			memset(receiveBuf, 0, MAXLENGTH);//��ǰ1024���ַ���Ϊ0
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
		closesocket(MySocket);//�ر�
		WSACleanup();//�ͷ���Դ�Ĳ���
	}

}; 