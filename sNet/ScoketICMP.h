#include <WINSOCK2.H>
#pragma comment(lib,"ws2_32.lib")
class SocketICMP
{
private:
	SOCKET m_sockRaw;
    WSAEVENT m_event;
    USHORT m_usCurrentProcID;

	sockaddr_in sockaddrDest; 
	int nSockaddrDestSize;
//	int dwTimeout;
public:
	SocketICMP():
		m_szICMPData(NULL), 
		m_bIsInitSucc(FALSE)
	{}
	~SocketICMP()
	{
		Close();
	}
	void Creat(char *IP):
		m_szICMPData(NULL), 
		m_bIsInitSucc(FALSE)
	{
		WSADATA WSAData;
		WSAStartup(MAKEWORD(1, 1), &WSAData);

		m_event = WSACreateEvent();
		m_usCurrentProcID = (USHORT)GetCurrentProcessId();

		if ((m_sockRaw = WSASocket(AF_INET, SOCK_RAW, IPPROTO_ICMP, NULL, 0, 0)) != SOCKET_ERROR)
		{
			WSAEventSelect(m_sockRaw, m_event, FD_READ);
			m_bIsInitSucc = TRUE;

			sockaddrDest.sin_family = AF_INET; 
			sockaddrDest.sin_addr.s_addr = IP;
			nSockaddrDestSize = sizeof(sockaddrDest);
		}
	}

	int Send(char *SendBuff,int len)
	{
		return sendto(m_sockRaw, SendBuff, len, 0, (struct sockaddr*)&sockaddrDest, nSockaddrDestSize)
	
	}
	int Recerve(char *RecerveBuff,int len)
	{
		return	recvfrom(m_sockRaw, RecerveBuf, len, 0, (struct sockaddr*)&sockaddrDest, &nSockaddrDestSize);
	}
	int Close()
	{
		WSACleanup();
		closesocket(m_sockRaw);//¹Ø±Õ
	}
};