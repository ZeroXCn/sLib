/**
* SBrush��
* GDI����-��ˢ��
* @author ZeroX
* @version v1.0 25/07/2017
*/
#include "SGdiHandle.h"
#ifndef _SBRUSH_H_
#define _SBRUSH_H_
class SBrush :public SGdiHandle<HBRUSH, LOGBRUSH>
{
public:
	SBrush(SGdiObj Obj);
	SBrush(HBRUSH hBrush=NULL);
	virtual ~SBrush();

public:
	//��������ָ�������ɫ��ģʽ���߼�ˢ��
	BOOL CreateIndirect(LOGBRUSH lBrush);

	//ָ����Ӱģʽ����ɫ���߼�ˢ��
	BOOL CreateHatch(int fnStyle, COLORREF clrref);

	//��һ�����豸�޹ص�λͼ����һ��ˢ�ӣ��Ա�ָ��ˢ����ʽ��ͼ����
	BOOL CreateDIBPattern(HGLOBAL hglbDIBPacked,UINT fuColorSpec);

	//��������ָ��λͼģʽ���߼�ˢ��
	BOOL CreatePattern(HBITMAP hbmp);

	//����һ������ָ����ɫ���߼�ˢ�ӡ�
	BOOL CreateSolid(COLORREF clrref);

	//��ˢ�Ӷ�Ӧָ������ɫ����ֵ��
	BOOL CreateSysColor(int nIndex);

public:

};

#endif;