/**
* SButton类
* 按钮控件
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
	function<void(void)> m_fClicked;		//点击回调
public:

	SButton(LPTSTR name = TEXT("button"), SWidget *parent = NULL);
	virtual ~SButton();
protected:
	//注册一个类-用来标记控件类型
	virtual BOOL OnPreCreate();

	//消息处理
	virtual LRESULT CALLBACK OnProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	//回调
	void OnClicked(function<void(void)> callback);
};

#endif