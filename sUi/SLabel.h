/**
* SLabel类
* 标签部件
* @author ZeroX
* @version v1.0 21/07/2017
*/

#include "SWidget.h"
#ifndef _SLABEL_H_
#define _SLABEL_H_

class SLabel :public SWidget
{
public:
	SLabel(LPTSTR name=TEXT("This is a Label"),SWidget *parent=NULL);
	virtual ~SLabel();
protected:
	//注册一个类-用来标记控件类型
	virtual BOOL OnPreCreate();

};
#endif