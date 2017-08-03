/**
* SButton��
* ��ť�ؼ�
* @author ZeroX
* @version v1.0 30/07/2017
*/
#include "../sCore/SString.h"
#include "SWidget.h"
#ifndef _SBUTTON_H_
#define _SBUTTON_H_
#include <functional>
using namespace std;

class SButton :public SWidget
{
protected:
	function<void(void)> m_fClicked;		//����ص�
public:

	SButton(SWidget *parent = NULL, LPTSTR name = TEXT("button"));
	virtual ~SButton();
protected:
	//ע��һ����-������ǿؼ�����
	virtual BOOL OnPreCreate();

	//��Ϣ����
	virtual LRESULT CALLBACK OnProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	//����ȡ�ð�ť�ı�
	void SetText(SString str);
	SString GetText();
public:
	//�ص�
	virtual void OnClicked();
	void OnClicked(function<void(void)> callback);
};

#endif