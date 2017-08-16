/**
* SEditText��
* �༭��ؼ�
* @author ZeroX
* @version v1.0 13/08/2017
*/

#include "SControl.h"
#ifndef _SEDITTEXT_H_
#define _SEDITTEXT_H_
#include <functional>

class SEditText :public SControl
{
protected:
	std::function<void(void)> m_fTextChanged;		//�����ı�
public:
	SEditText(SWidget *parent = NULL, LPTSTR content = TEXT(""));
	virtual ~SEditText();
protected:
	//��Ϣ����
	virtual LRESULT CALLBACK OnProc(MessageParam param);
public:
	//����ȡ�ð�ť�ı�
	void SetCurrentText(SString str);
	SString GetCurrentText();

	//����ֻ��
	BOOL IsReadOnly();
	void SetReadOnly(BOOL bReadOnly);

protected:
	//�ı������ı�
	virtual void OnTextChanged();
public:
	//�ı������ı�
	void OnTextChanged(std::function<void(void)> callback);

};
#endif