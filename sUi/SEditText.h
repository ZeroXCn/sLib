/**
* SEditText类
* 编辑框控件
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
	std::function<void(void)> m_fTextChanged;		//发生改变
public:
	SEditText(SWidget *parent = NULL, LPTSTR content = TEXT(""));
	virtual ~SEditText();
protected:
	//消息处理
	virtual LRESULT CALLBACK OnProc(MessageParam param);
public:
	//设置取得按钮文本
	void SetCurrentText(SString str);
	SString GetCurrentText();

	//设置只读
	BOOL IsReadOnly();
	void SetReadOnly(BOOL bReadOnly);

protected:
	//文本发生改变
	virtual void OnTextChanged();
public:
	//文本发生改变
	void OnTextChanged(std::function<void(void)> callback);

};
#endif