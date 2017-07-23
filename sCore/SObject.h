/**
*
*	SObject类,所有S类的基类
*	
*	@author ZeroX
*	@version v1.0 22/07/2017(22/07/2017)
*
*/


#include "SString.h"

#ifndef _SOBJECT_H_
#define _SOBJECT_H_
//提前声明一下,因为SObject要比SString提前加载,此时SString未声明,之后才会去
class SString;
class SObject
{

public:
	virtual SString ToString();
};

#endif