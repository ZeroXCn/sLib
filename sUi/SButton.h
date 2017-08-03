/**
* SButton类
* 按钮控件
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
	function<void(void)> m_fClicked;		//点击回调
public:

	SButton(SWidget *parent = NULL, LPTSTR name = TEXT("button"));
	virtual ~SButton();
protected:
	//注册一个类-用来标记控件类型
	virtual BOOL OnPreCreate();

	//消息处理
	virtual LRESULT CALLBACK OnProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	//设置取得按钮文本
	void SetText(SString str);
	SString GetText();
public:
	//回调
	virtual void OnClicked();
	void OnClicked(function<void(void)> callback);
};

#endif