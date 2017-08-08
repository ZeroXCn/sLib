/**
*	SMedia类
*	基于WinAPI 多媒体组件(MCI)开发的音效
*	多余实时响应不是很好,慎用
*	@author ZeroX
*	@version v1.0 22/07/2017(03/12/2016)
*/
#include "../sCore/SObject.h"

#ifndef _SMEDIA_H_
#define _SMEDIA_H_ 

#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>		//包含文件

#pragma comment(lib,"winmm.lib")

class SMedia :public SObject
{
protected:
	int		m_ID;				//编号
	static int g_nNewID;		//下一个可用编号

	UINT	m_nVolume;			//音量(0~1000)
	
public:
	static MCIERROR Execute(LPTSTR szCommand, LPTSTR szReturnString = NULL, UINT cchReturnSize = 0, HWND hwndCallback = 0);	//命令执行

public:
	SMedia();					//构造函数

	SMedia(LPTSTR szMusicPath);	//带路径参数的构造函数

	~SMedia();				//析构函数

public:
	BOOL IsPlay();			//音乐是否播放状态

	BOOL IsOpen();			//音乐文件是否打开状态

	BOOL IsStop();			//音乐是否停止状态

	//BOOL IsPause();			//音乐是否暂停状态

	LPTSTR GetMusicState(LPTSTR szStatus, UINT nBufferSize);		//获取音乐状态

	UINT GetVolume();			//获取音量大小

	void SetVolume(UINT nVolume);	//设置音量

	void VolumeDown();			//减小音量

	void VolumeUp();			//增大音量
	
	BOOL Open(LPTSTR szMusicPath);	//打开音乐文件

	BOOL Close();				//关闭音乐文件
public:
	UINT GetLength();			//取得媒体总长度

public:
	BOOL Pause();				//暂停播放

	BOOL Resume();				//继续播放

	BOOL Stop();				//停止播放

	BOOL Play(UINT nVolume, BOOL bRepeat, BOOL bReStart); //播放音乐，可设置是否循环播放、重新开始

	BOOL Play(UINT nVolume, UINT nStartTime, UINT nEndTime, BOOL bRepeat, BOOL bReStart);//从X到Y播放音乐,是否重复

	BOOL LoopPlay(); //循环播放

	BOOL Play(); //播放音乐

	BOOL RePlay(); //重新播放
public:
	BOOL Seek(UINT nTime);		//设置进度
	BOOL SeekToStart();			//设置到开头
	BOOL SeekToEnd();			//设置到结尾


	UINT Tell();				//取得当前进度

	BOOL Step(UINT nTime);		//快进或快退
};

#endif

