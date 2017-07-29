/*********************************
	��Ϸ���ֳ����ļ�GameMusic.cpp
*********************************/

#include "SMedia.h"


int SMedia::g_nNewID=1;		//��ʼ����һ�����ñ��

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SMedia::SMedia()					//���캯��
{
	m_ID=g_nNewID;
	g_nNewID++;	
	m_nVolume=100;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SMedia::SMedia(LPTSTR szMusicPath)	//��·�������Ĺ��캯��
{

	m_ID=g_nNewID;
	g_nNewID++;	
	m_nVolume=100;
	if (_tcslen(szMusicPath)>0)	//�ж�·����Ϊ��
	{
		Open(szMusicPath);	//�������ļ�
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SMedia::~SMedia()//��������
{
	Close();
}		

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MCIERROR SMedia::Execute(LPTSTR szCommand, LPTSTR szReturnString, UINT cchReturnSize, HWND hwndCallback)
{
	return ::mciSendString(szCommand, szReturnString, cchReturnSize, hwndCallback);	//��ȡ״̬
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL SMedia::IsPlay()		//��ȡ���ֲ���״̬
{	
	TCHAR szStatus[20]={'\0'};
	TCHAR szCommand[256];
	
	_stprintf_s(szCommand,TEXT("status MUSIC%d mode"), m_ID);	//����MCI�����ַ���
	::mciSendString(szCommand,szStatus,20,0);	//��ȡ״̬
	return(0 == wcscmp(szStatus, TEXT("playing")));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL SMedia::IsOpen()		//��ȡ�����ļ���״̬
{
	TCHAR szStatus[20]={'\0'};
	TCHAR szCommand[256];
	
	_stprintf_s(szCommand, TEXT("status MUSIC%d mode"), m_ID);
	::mciSendString(szCommand,szStatus,20,0);	

	return(0 == wcscmp(szStatus, TEXT("stopped")) || 0 == wcscmp(szStatus, TEXT("playing")));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL SMedia::IsStop()
{
	TCHAR szStatus[20]={'\0'};
	TCHAR szCommand[256];
	
	_stprintf_s(szCommand, TEXT("status MUSIC%d mode"), m_ID);
	::mciSendString(szCommand,szStatus,20,0);
	return(0 == wcscmp(szStatus, TEXT("stopped")));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LPTSTR SMedia::GetMusicState(LPTSTR szStatus, UINT nBufferSize)		//��ȡ����״̬
{
	TCHAR szCommand[256];

	_stprintf_s(szCommand, TEXT("status MUSIC%d mode"), m_ID);
	::mciSendString(szCommand, szStatus, nBufferSize, 0);

	return szStatus;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

UINT SMedia::GetVolume()			//��ȡ������С
{
	return m_nVolume;	
}

void SMedia::SetVolume(UINT nVolume)	//��������
{
	if(nVolume<0)
		nVolume=0;
	if(nVolume>1000)
		nVolume=1000;

	TCHAR szCommand[256];
	_stprintf_s(szCommand, TEXT("Setaudio MUSIC%d volume to %d"), m_ID, nVolume);	//����MCI�����ַ���
	::mciSendString(szCommand,NULL,0,0);	//��������
	
	m_nVolume=nVolume;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void SMedia::VolumeDown()		//��С����
{
	SetVolume(m_nVolume-10);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SMedia::VolumeUp()			//��������
{
	SetVolume(m_nVolume+10);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL SMedia::Open(LPTSTR szMusicPath)	//�������ļ�
{

	if(wcslen(szMusicPath)==0)
		return FALSE;
	
	if(IsPlay()||IsStop())	//������������ļ����򿪣����ȹر�
		Close();

	TCHAR szCommand[256];
	_stprintf_s(szCommand, TEXT("OPEN %s ALIAS MUSIC%d"), szMusicPath, m_ID);
	if(!::mciSendString(szCommand,NULL,0,0))	//�������ļ�
	{
		return TRUE;
	}
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL SMedia::Close()		//�ر������ļ�
{
	TCHAR szCommand[256];

	if(IsOpen())
	{
		_stprintf_s(szCommand, TEXT("CLOSE MUSIC%d"), m_ID);
		if(!::mciSendString(szCommand,NULL,0,0))
		{
			return TRUE;				
		}
	}
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UINT SMedia::GetLength()			//ȡ��ý���ܳ���
{
	TCHAR szStatus[20] = { '\0' };
	TCHAR szCommand[256];

	_stprintf_s(szCommand, TEXT("status MUSIC%d length"), m_ID);
	::mciSendString(szCommand, szStatus, 20, 0);

	//�ַ���ת����
	return _tstoi(szStatus);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL SMedia::Play(UINT nVolume, BOOL bRepeat, BOOL bReStart) //�������֣��������Ƿ�ѭ�����š����²���
{
	TCHAR szCommand[256];	
	
	if(IsStop()||bReStart)	//�ж�������ֹͣ״̬��Ҫ�����²���ʱ�Ų���
	{	

		if(bRepeat)
			_stprintf_s(szCommand, TEXT("PLAY MUSIC%d FROM 0  repeat"), m_ID);
		else
			_stprintf_s(szCommand, TEXT("PLAY MUSIC%d FROM 0"), m_ID);

		if(!::mciSendString(szCommand,NULL,0,0))
		{
			SetVolume(nVolume);				
			return TRUE;
		}
	}

	return FALSE;
}

BOOL SMedia::Play(UINT nVolume, UINT nStartTime, UINT nEndTime, BOOL bRepeat, BOOL bReStart)//��X��Y��������,�������Ƿ�ѭ�����š����²���
{
	TCHAR szCommand[256];

	if (IsStop() || bReStart)	//�ж�������ֹͣ״̬��Ҫ�����²���ʱ�Ų���
	{

		if (bRepeat)
			_stprintf_s(szCommand, TEXT("PLAY MUSIC%d FROM %d to %d repeat"), m_ID, nStartTime, nEndTime);
		else
			_stprintf_s(szCommand, TEXT("PLAY MUSIC%d FROM %d to %d"), m_ID, nStartTime, nEndTime);

		if (!::mciSendString(szCommand, NULL, 0, 0))
		{
			SetVolume(nVolume);
			return TRUE;
		}
	}

	return FALSE;
}

BOOL SMedia::Play(){
	TCHAR szCommand[256];
	_stprintf_s(szCommand, TEXT("PLAY MUSIC%d"), m_ID);
	if (!::mciSendString(szCommand, NULL, 0, 0))
	{
		return TRUE;
	}
	else return FALSE;
}
BOOL SMedia::LoopPlay(){
	return Play(GetVolume(), true, false);
}
BOOL  SMedia::RePlay(){
	Stop();
	return Play(GetVolume(), false, true);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL SMedia::Stop()		//ֹͣ����
{
	TCHAR szCommand[256];
	if(IsPlay())
	{	
		_stprintf_s(szCommand, TEXT("STOP MUSIC%d"), m_ID);
		if(!::mciSendString(szCommand,NULL,0,0))
		{
			return TRUE;
		}
	}		
	return FALSE;
}	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL SMedia::Pause()	//��ͣ����
{
	TCHAR szCommand[256];
	_stprintf_s(szCommand, TEXT("PAUSE MUSIC%d"), m_ID);
	if (!::mciSendString(szCommand, NULL, 0, 0))
	{
		return TRUE;
	}else return FALSE;

}

BOOL SMedia::Resume()				//��������
{
	TCHAR szCommand[256];
	_stprintf_s(szCommand, TEXT("RESUME MUSIC%d"), m_ID);
	if (!::mciSendString(szCommand, NULL, 0, 0))
	{
		return TRUE;
	}
	else return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL SMedia::Seek(UINT nTime)		//���ý���
{
	TCHAR szCommand[256];
	_stprintf_s(szCommand, TEXT("SEEK MUSIC%d to %d"), m_ID, nTime);
	
	if (!::mciSendString(szCommand, NULL, 0, 0))
	{
		//_stprintf_s(szCommand, TEXT("PLAY MUSIC%d"), m_ID);
		return TRUE;
	}
	else return FALSE;
}

BOOL SMedia::SeekToStart()			//���õ���ͷ
{
	TCHAR szCommand[256];
	_stprintf_s(szCommand, TEXT("SEEK MUSIC%d to start"), m_ID);

	if (!::mciSendString(szCommand, NULL, 0, 0))
	{
		//_stprintf_s(szCommand, TEXT("PLAY MUSIC%d"), m_ID);
		return TRUE;
	}
	else return FALSE;
}
BOOL SMedia::SeekToEnd()			//���õ���β
{
	TCHAR szCommand[256];
	_stprintf_s(szCommand, TEXT("SEEK MUSIC%d to end"), m_ID);

	if (!::mciSendString(szCommand, NULL, 0, 0))
	{
		//_stprintf_s(szCommand, TEXT("PLAY MUSIC%d"), m_ID);
		return TRUE;
	}
	else return FALSE;
}

UINT SMedia::Tell()				//ȡ�õ�ǰ����
{
	TCHAR szStatus[20] = { '\0' };
	TCHAR szCommand[256];

	_stprintf_s(szCommand, TEXT("status MUSIC%d position"), m_ID);
	::mciSendString(szCommand, szStatus, 20, 0);

	//�ַ���ת����
	return _tstoi(szStatus);
}

BOOL SMedia::Step(UINT nTime)				//��������
{
	TCHAR szCommand[256];
	_stprintf_s(szCommand, TEXT("STEP MUSIC%d by %d"), m_ID, nTime);

	if (!::mciSendString(szCommand, NULL, 0, 0))
	{
		//_stprintf_s(szCommand, TEXT("PLAY MUSIC%d"), m_ID);
		return TRUE;
	}
	else return FALSE;
}