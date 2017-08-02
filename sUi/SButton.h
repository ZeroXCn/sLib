/**
* SButton��
* ��ť�ؼ�
* @author ZeroX
* @version v1.0 30/07/2017
*/
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

	SButton(LPTSTR name = TEXT("button"), SWidget *parent = NULL);
	virtual ~SButton();
protected:
	//ע��һ����-������ǿؼ�����
	virtual BOOL OnPreCreate();

	//��Ϣ����
	virtual LRESULT CALLBACK OnProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	//�ص�
	void OnClicked(function<void(void)> callback);
};

#endif