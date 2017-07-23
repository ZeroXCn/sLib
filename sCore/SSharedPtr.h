/**
*
*	SRunnable类
*	智能指针的一种
*	@author ZeroX
*	@version v1.0 23/07/2017(23/07/2017)
*
*/
#include "SObject.h"
#ifndef _SSHAREDPTR_H_
#define _SSHAREDPTR_H_
#include <memory>

template<class T>
class SSharedPtr :
	public SObject,
	public shared_ptr<T>
{

};

#endif