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

#include "SWidget.h"

class SApplication :public SObject
{
protected:
	static SApplication *g_pApp;			//����ģʽ
	static HINSTANCE	g_hInstance;				//��ǰ����ʵ�����
	static HINSTANCE	g_hPrevInstance;			//������ʵ�����
	static PSTR g_lpCmdline;						//�����ĸ�������
	static int g_nCmdShow;							//����ģʽ

	std::set<SWidget *>	m_winset;				//���ڼ���
public:
	static void SetParam(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdline, int nCmdShow);

	//ȡ�ô���ʵ��
	static HINSTANCE GetInstance();

	//ȡ�ø�����ʵ��
	static HINSTANCE GetPrevInstance();

	//ȡ������������
	static PSTR GetCmdline();

	//ȡ����ʾģʽ������
	static int GetCmdShow();
public:
	SApplication(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdline, int nCmdShow);
	~SApplication();
public:

	//ȡ�ô��ڼ���
	std::set<SWidget *> *GetWidgetSet();

public:
	//ע�ᴰ��
	BOOL RegisterWidget(SWidget *pWidget);

	//��ע�ᴰ��
	BOOL UnRegisterWidget(SWidget *pWidget);

	//�˳�����
	void QuitWidget(SWidget *pWidget);

	//ע������
	void DestroyWidget(SWidget *pWidget);
public:
	//ȡ�õ���
	static SApplication *GetApp();

public:
	int Exec();
};

#endif