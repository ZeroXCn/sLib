/**
* SObserver�ӿ���
* �۲���ģʽģʽ-�۲�����
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
	//�۲��߸�������
	void Update(SSubject *pSubject, void *date);
};

#endif