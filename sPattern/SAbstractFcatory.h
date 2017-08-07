/**
* SAbstractFcatory抽象类
* 工厂模式-抽象工厂类
* @author ZeroX
* @version v1.0 07/08/2017
*/

#ifndef _SABSTRACTFCATORY_H_
#define _SABSTRACTFCATORY_H_
#include "SProduct.h"

class SAbstractFcatory
{
protected:
	SAbstractFcatory();
public:
	virtual SProduct *Create(int nType)=0;
};

#endif