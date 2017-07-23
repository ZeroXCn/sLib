/**
* SApplication��
* ��ΪWin32��Ӧ�ó�����ںͳ���,���Ҵ���һЩȫ���¼�
* @author ZeroX
* @version v1.0 21/07/2017
*/
#include "../sCore/SObject.h"
#ifndef _SAPPLICATION_H_
#define _SAPPLICATION_H_

#include <Windows.h>
#include <set>

#include "SWindow.h"
using namespace std;


class SApplication :public SObject
{
	
protected:
	static SApplication *g_pApp;			//����ģʽ
protected:
	HINSTANCE	m_hInstance;				//��ǰ����ʵ�����
	HINSTANCE	m_hPrevInstance;			//������ʵ�����
	PSTR m_lpCmdline;						//�����ĸ�������
	int m_nCmdShow;							//����ģʽ

	set<SWindow *>	m_winset;				//���ڼ���
public:

public:
	SApplication(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdline, int nCmdShow);
	~SApplication();
public:
	//ȡ�ô���ʵ��
	HINSTANCE GetInstance();

	//ȡ�ø�����ʵ��
	HINSTANCE GetPrevInstance();

	//ȡ������������
	PSTR GetCmdline();

	//ȡ����ʾģʽ������
	int GetCmdShow();

	//ȡ�ô��ڼ���
	set<SWindow *> *GetWindowSet();

public:
	//ע�ᴰ��
	BOOL RegisterWindow(SWindow *pWindow);

	//��ע�ᴰ��
	BOOL UnRegisterWindow(SWindow *pWindow);

	//�˳�����
	void QuitWindow(SWindow *pWindow);

	//ע������
	void DestroyWindow(SWindow *pWindow);
public:
	//ȡ�õ���
	static SApplication *GetApp();

public:
	int Exec();
};

#endif