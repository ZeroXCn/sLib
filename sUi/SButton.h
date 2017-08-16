/**
* SButton��
* ��ť�ؼ�
* @author ZeroX
* @version v1.0 30/07/2017
*/

#include "SControl.h"
#ifndef _SBUTTON_H_
#define _SBUTTON_H_
#include <functional>

class SButton :public SControl
{
protected:
	std::function<void(void)> m_fClicked;		//����ص�
public:

	SButton(SWidget *parent = NULL, LPTSTR name = TEXT("button"));
	virtual ~SButton();
protected:
	//��Ϣ����
	virtual LRESULT CALLBACK OnProc(MessageParam param);

public:
	//����ȡ�ð�ť�ı�
	void SetText(SString str);
	SString GetText();

protected:
	//���
	virtual void OnClicked();
public:
	//���
	void OnClicked(std::function<void(void)> callback);
};

#endif