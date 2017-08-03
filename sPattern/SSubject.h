/**
* SSubject类
* 观察者模式模式-主题类
* @author ZeroX
* @version v1.0 03/08/2017(03/06/2017)
*/
#ifndef _SSUBJECT_H_
#define _SSUBJECT_H_
#include "SObserver.h"

#include <vector>
using namespace std;

class SSubject
{
private:
	vector<SObserver *> m_Obs;
	bool m_bChanged;
public:
	//添加,删除观察者
	void AddObserver(SObserver *pObserver);
	void DeleteObserver(SObserver *pObserver);

	//主题数据是否发生改变
	bool HasChanged();

	//通知观察者更新数据
	void NotifyObserver(void *data);
	void NotifyObservers();
protected:
	//设置主题变化标志
	void SetChanged(bool bChange=true);

	//清除主题变化变化标志
	void ClearChanged();
};
#endif