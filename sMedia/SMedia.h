/**
*	SMedia��
*	����WinAPI ��ý�����(MCI)��������Ч
*	����ʵʱ��Ӧ���Ǻܺ�,����
*	@author ZeroX
*	@version v1.0 22/07/2017(03/12/2016)
*/
#include "../sCore/SObject.h"

#ifndef _SMEDIA_H_
#define _SMEDIA_H_ 

#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>		//�����ļ�

#pragma comment(lib,"winmm.lib")

class SMedia :public SObject
{
protected:
	int		m_ID;				//���
	static int g_nNewID;		//��һ�����ñ��

	UINT	m_nVolume;			//����(0~1000)
	
public:
	static MCIERROR Execute(LPTSTR szCommand, LPTSTR szReturnString = NULL, UINT cchReturnSize = 0, HWND hwndCallback = 0);	//����ִ��

public:
	SMedia();					//���캯��

	SMedia(LPTSTR szMusicPath);	//��·�������Ĺ��캯��

	~SMedia();				//��������

public:
	BOOL IsPlay();			//�����Ƿ񲥷�״̬

	BOOL IsOpen();			//�����ļ��Ƿ��״̬

	BOOL IsStop();			//�����Ƿ�ֹͣ״̬

	//BOOL IsPause();			//�����Ƿ���ͣ״̬

	LPTSTR GetMusicState(LPTSTR szStatus, UINT nBufferSize);		//��ȡ����״̬

	UINT GetVolume();			//��ȡ������С

	void SetVolume(UINT nVolume);	//��������

	void VolumeDown();			//��С����

	void VolumeUp();			//��������
	
	BOOL Open(LPTSTR szMusicPath);	//�������ļ�

	BOOL Close();				//�ر������ļ�
public:
	UINT GetLength();			//ȡ��ý���ܳ���

public:
	BOOL Pause();				//��ͣ����

	BOOL Resume();				//��������

	BOOL Stop();				//ֹͣ����

	BOOL Play(UINT nVolume, BOOL bRepeat, BOOL bReStart); //�������֣��������Ƿ�ѭ�����š����¿�ʼ

	BOOL Play(UINT nVolume, UINT nStartTime, UINT nEndTime, BOOL bRepeat, BOOL bReStart);//��X��Y��������,�Ƿ��ظ�

	BOOL LoopPlay(); //ѭ������

	BOOL Play(); //��������

	BOOL RePlay(); //���²���
public:
	BOOL Seek(UINT nTime);		//���ý���
	BOOL SeekToStart();			//���õ���ͷ
	BOOL SeekToEnd();			//���õ���β


	UINT Tell();				//ȡ�õ�ǰ����

	BOOL Step(UINT nTime);		//��������
};

#endif

