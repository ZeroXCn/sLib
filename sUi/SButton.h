/**
* SButton类
* 按钮控件
* @author ZeroX
* @version v1.0 30/07/2017
*/
#include "SWidget.h"
#ifndef _SBUTTON_H_
#define _SBUTTON_H_

class SButton :public SWidget
{
public:

	SButton(LPTSTR name = TEXT("button"), SWidget *parent = NULL);
	virtual ~SButton();
protected:
	//注册一个类-用来标记控件类型
	virtual BOOL OnPreCreate();

};

#endif