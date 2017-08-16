/**
* SButton类
* 按钮控件
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
	std::function<void(void)> m_fClicked;		//点击回调
public:

	SButton(SWidget *parent = NULL, LPTSTR name = TEXT("button"));
	virtual ~SButton();
protected:
	//消息处理
	virtual LRESULT CALLBACK OnProc(MessageParam param);

public:
	//设置取得按钮文本
	void SetText(SString str);
	SString GetText();

protected:
	//点击
	virtual void OnClicked();
public:
	//点击
	void OnClicked(std::function<void(void)> callback);
};

#endif