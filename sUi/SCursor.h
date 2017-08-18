/**
* SCurson��
* �����
* @author ZeroX
* @version v1.0 29/07/2017
*/
#include "SHandle.h"
#ifndef _SCURSOR_H_
#define _SCURSOR_H_

class SCursor :public SHandle<HCURSOR>
{
public:
	SCursor(HCURSOR hCursor=NULL);
	virtual ~SCursor();
public:
	//����һ��ָ����С��λģʽ���ȵ�Ĺ��
	BOOL Create(HINSTANCE htnst, int xHotSpot, int yHotSpot, int nWidth, int nHeight, CONST VOID *pvANDPlane, CONST VOID *pvXORPlane);

	//����Դ�м���λͼ
	BOOL Load(UINT uRcid, HINSTANCE hInstance = NULL);

	//���ļ��м���λͼ
	BOOL Load(LPTSTR lpFileName, HINSTANCE hInstance = NULL);

	//����һ����겢�ͷ���ռ�õ��κ��ڴ�,��Ҫʹ�øú���ȥ����һ��������
	BOOL Destroy();


};

#endif