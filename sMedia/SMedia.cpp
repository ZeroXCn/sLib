/*********************************
	游戏音乐程序文件GameMusic.cpp
*********************************/

#include "SMedia.h"


int SMedia::g_nNewID=1;		//初始化下一个可用编号

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SMedia::SMedia()					//构造函数
{
	m_ID=g_nNewID;
	g_nNewID++;	
	m_nVolume=100;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SMedia::SMedia(LPTSTR szMusicPath)	//带路径参数的构造函数
{

	m_ID=g_nNewID;
	g_nNewID++;	
	m_nVolume=100;
	if (_tcslen(szMusicPath)>0)	//判断路径不为空
	{
		Open(szMusicPath);	//打开音乐文件
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SMedia::~SMedia()//析构函数
{
	Close();
}		

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MCIERROR SMedia::Execute(LPTSTR szCommand, LPTSTR szReturnString, UINT cchReturnSize, HWND hwndCallback)
{
	return ::mciSendString(szCommand, szReturnString, cchReturnSize, hwndCallback);	//获取状态
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL SMedia::IsPlay()		//获取音乐播放状态
{	
	TCHAR szStatus[20]={'\0'};
	TCHAR szCommand[256];
	
	_stprintf_s(szCommand,TEXT("status MUSIC%d mode"), m_ID);	//创建MCI命令字符串
	::mciSendString(szCommand,szStatus,20,0);	//获取状态
	return(0 == wcscmp(szStatus, TEXT("playing")));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL SMedia::IsOpen()		//获取音乐文件打开状态
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

LPTSTR SMedia::GetMusicState(LPTSTR szStatus, UINT nBufferSize)		//获取音乐状态
{
	TCHAR szCommand[256];

	_stprintf_s(szCommand, TEXT("status MUSIC%d mode"), m_ID);
	::mciSendString(szCommand, szStatus, nBufferSize, 0);

	return szStatus;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

UINT SMedia::GetVolume()			//获取音量大小
{
	return m_nVolume;	
}

void SMedia::SetVolume(UINT nVolume)	//设置音量
{
	if(nVolume<0)
		nVolume=0;
	if(nVolume>1000)
		nVolume=1000;

	TCHAR szCommand[256];
	_stprintf_s(szCommand, TEXT("Setaudio MUSIC%d volume to %d"), m_ID, nVolume);	//创建MCI命令字符串
	::mciSendString(szCommand,NULL,0,0);	//设置音量
	
	m_nVolume=nVolume;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void SMedia::VolumeDown()		//减小音量
{
	SetVolume(m_nVolume-10);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SMedia::VolumeUp()			//增大音量
{
	SetVolume(m_nVolume+10);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL SMedia::Open(LPTSTR szMusicPath)	//打开音乐文件
{

	if(wcslen(szMusicPath)==0)
		return FALSE;
	
	if(IsPlay()||IsStop())	//如果已有音乐文件被打开，则先关闭
		Close();

	TCHAR szCommand[256];
	_stprintf_s(szCommand, TEXT("OPEN %s ALIAS MUSIC%d"), szMusicPath, m_ID);
	if(!::mciSendString(szCommand,NULL,0,0))	//打开音乐文件
	{
		return TRUE;
	}
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL SMedia::Close()		//关闭音乐文件
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
UINT SMedia::GetLength()			//取得媒体总长度
{
	TCHAR szStatus[20] = { '\0' };
	TCHAR szCommand[256];

	_stprintf_s(szCommand, TEXT("status MUSIC%d length"), m_ID);
	::mciSendString(szCommand, szStatus, 20, 0);

	//字符串转数字
	return _tstoi(szStatus);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL SMedia::Play(UINT nVolume, BOOL bRepeat, BOOL bReStart) //播放音乐，可设置是否循环播放、重新播放
{
	TCHAR szCommand[256];	
	
	if(IsStop()||bReStart)	//判断音乐在停止状态或要求重新播放时才播放
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

BOOL SMedia::Play(UINT nVolume, UINT nStartTime, UINT nEndTime, BOOL bRepeat, BOOL bReStart)//从X到Y播放音乐,可设置是否循环播放、重新播放
{
	TCHAR szCommand[256];

	if (IsStop() || bReStart)	//判断音乐在停止状态或要求重新播放时才播放
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

BOOL SMedia::Stop()		//停止播放
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
BOOL SMedia::Pause()	//暂停播放
{
	TCHAR szCommand[256];
	_stprintf_s(szCommand, TEXT("PAUSE MUSIC%d"), m_ID);
	if (!::mciSendString(szCommand, NULL, 0, 0))
	{
		return TRUE;
	}else return FALSE;

}

BOOL SMedia::Resume()				//继续播放
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

BOOL SMedia::Seek(UINT nTime)		//设置进度
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

BOOL SMedia::SeekToStart()			//设置到开头
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
BOOL SMedia::SeekToEnd()			//设置到结尾
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

UINT SMedia::Tell()				//取得当前进度
{
	TCHAR szStatus[20] = { '\0' };
	TCHAR szCommand[256];

	_stprintf_s(szCommand, TEXT("status MUSIC%d position"), m_ID);
	::mciSendString(szCommand, szStatus, 20, 0);

	//字符串转数字
	return _tstoi(szStatus);
}

BOOL SMedia::Step(UINT nTime)				//快进或快退
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