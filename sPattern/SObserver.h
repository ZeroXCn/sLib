/**
* SObserver接口类
* 观察者模式模式-观察者类
* @author ZeroX
* @version v1.0 03/08/2017(03/06/2017)
*/
#include "SSubject.h"
#ifndef _SOBSERVER_H_
#define _SOBSERVER_H_
class SSubject;

class SObserver
{
public:
	//观察者更新数据
	void Update(SSubject *pSubject, void *date);
};

#endif