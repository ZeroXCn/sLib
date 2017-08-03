/**
* SSubject��
* �۲���ģʽģʽ-������
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
	//���,ɾ���۲���
	void AddObserver(SObserver *pObserver);
	void DeleteObserver(SObserver *pObserver);

	//���������Ƿ����ı�
	bool HasChanged();

	//֪ͨ�۲��߸�������
	void NotifyObserver(void *data);
	void NotifyObservers();
protected:
	//��������仯��־
	void SetChanged(bool bChange=true);

	//�������仯�仯��־
	void ClearChanged();
};
#endif