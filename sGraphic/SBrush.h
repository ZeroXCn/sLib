/**
* SBrush��
* GDI����-��ˢ��
* @author ZeroX
* @version v1.0 25/07/2017
*/
#include "SGdiObject.h"
#ifndef _SBRUSH_H_
#define _SBRUSH_H_
class SBrush :public SGdiObject
{
public:
	SBrush();
	SBrush(SGdiObject Obj);
	SBrush(HBRUSH hBrush);
	virtual ~SBrush();

public:
	void SetBrush(HBRUSH hBrush);

	HBRUSH GetBrush();

	LOGBRUSH GetBrushStruct();
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