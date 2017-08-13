/**
* SLabel类
* 标签部件
* @author ZeroX
* @version v1.0 21/07/2017
*/
#include "../sCore/SString.h"
#include "../sGraphic/SFont.h"
#include "SControl.h"
#ifndef _SLABEL_H_
#define _SLABEL_H_

class SLabel :public SControl
{
public:
	SLabel(SWidget *parent = NULL, LPTSTR name = TEXT("This is a Label"));
	virtual ~SLabel();
protected:
	//注册一个类-用来标记控件类型
	virtual BOOL OnPreCreate();

public:
	//设置取得按钮文本
	void SetText(SString str);
	SString GetText();

	//调整到文本大小
	void AdjustText();

};
#endif