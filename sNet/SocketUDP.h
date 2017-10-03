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
		int err=WSAStartup(sockVersion,&wsaData);//Э���İ汾��Ϣ
		if(err!=0)return err;

		MySocket=socket(AF_INET,SOCK_DGRAM, IPPROTO_UDP);
		if(MySocket == INVALID_SOCKET) return -1;

		MySock_in.sin_family=AF_INET;
		MySock_in.sin_port=htons(port); 

		//����˵Ļ����а�
		if(add==NULL){
			identity=0;
			MySock_in.sin_addr.S_un.S_addr=htonl(INADDR_ANY);//�����
			bind(MySocket,(SOCKADDR*)&MySock_in,sizeof(MySock_in));//�����
			remoteAddr=&serSockin;
		}else//�ͻ��˵Ļ�
		{
			identity=1;
			MySock_in.sin_addr.S_un.S_addr=inet_addr(smtpIp(add));//ip��ַ(�ͻ���)
			remoteAddr=&MySock_in;
		}
		nAddrLen = sizeof(*remoteAddr);
		return err; //!err�򿪳ɹ�
	}
	
	string Receive(int *state=NULL)
	{
		//�˴������ַ������ճ���δ֪�����ܸ�1024,����һ�λ���1024���ֽ�
		const int MAXLENGTH=255;//���û�������С
		char receiveBuf[MAXLENGTH];
		string result="";
		int _rev=0;
		do{
			memset(receiveBuf, 0, MAXLENGTH);//��ǰMAXLENGTH���ַ���Ϊ0
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
		closesocket(MySocket);//�ر�
		WSACleanup();//�ͷ���Դ�Ĳ���
	}

}; 