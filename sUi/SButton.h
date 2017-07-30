/**
* SButtonÀà
* °´Å¥¿Ø¼þ
* @author ZeroX
* @version v1.0 30/07/2017
*/
#include "SWidget.h"
#ifndef _SBUTTON_H_
#define _SBUTTON_H_

class SButton :public SWidget
{
public:
	SButton(SWidget *parent = NULL);
	virtual ~SButton();
public:
	virtual BOOL Create();
};

#endif