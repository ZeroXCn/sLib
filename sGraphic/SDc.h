/**
* SDc��
* HDC��װ��
* @author ZeroX
* @version v1.0 25/07/2017
*/

#include "../sCore/SObject.h"
#include "../sCore/SString.h"
#include "SGdiObject.h"
#ifndef _SDC_H_
#define _SDC_H_
#include <Windows.h>
#include <wingdi.h>
#pragma comment(lib,"gdi32.lib")		//���ÿ�

#define RED_COLOR RGB(255,0,0)
#define GREEN_COLOR RGB(255,0,0)
#define BLUE_COLOR RGB(255,0,0)
#define WHITE_COLOR RGB(255,255,255)
#define BLACK_COLOR RGB(0,0,0)

class SDc:public SObject
{
protected:
	HDC m_hDC;			//�豸������
public:
	SDc();
	SDc(HDC hDC);

	virtual ~SDc();
public:
	//���û�ͼ������
	void SetDc(HDC hDC);

	//ȡ�õ�ǰ��ͼ������
	HDC GetDc();
public:
	//ѡ��һ����ָ�����豸�����Ļ�����
	HGDIOBJ SelectObject(HGDIOBJ hgdiobj);
	SGdiObject SelectObject(SGdiObject pObj);

	//ɾ�����ͷ�ϵͳ��Դ
	BOOL DeleteObject(HGDIOBJ hObject);
	BOOL DeleteObject(SGdiObject pObj);

public:
	//�����ı���ɫ
	COLORREF SetTextColor(COLORREF crColor);

	//���ñ���ɫ
	COLORREF SetBkColor(COLORREF color);

public:
	//����
	BOOL DrawPoint(int x, int y, COLORREF color = RGB(0, 0, 0));

	//����
	void DrawLine(int x1, int y1, int x2, int y2);

	//��������
	void DrawTringle(POINT a, POINT b, POINT c);

	//������-�������ͻ��߿�
	BOOL DrawRect(int left, int top, int right, int bottom);

	//�����α߿�
	BOOL FrameRect(int left, int top, int right, int bottom, HBRUSH hbr = NULL);

	//������
	BOOL FillRect(int left, int top, int right, int bottom, HBRUSH hbr = NULL);

	//����Բ�Ǿ���
	BOOL RoundRect(int left, int top, int right, int bottom, int width, int height);

	//���������ݷ�ɫ
	BOOL InvertRect(int left, int top, int right, int bottom);

	//��Բ
	BOOL DrawRadius(int x, int y, int radius);

	//����Բ
	BOOL DrawEllipse(int left, int top, int right, int bottom);

	//��Բ������
	BOOL DrawPie(int left, int top, int right, int bottom, int xr1, int yr1, int xr2, int yr2);

	//�����и���Բ
	BOOL DrawChord(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);

	//�����Բ
	//void FillEllipse(int left, int top, int right, int bottom);

	//���ƶ����
	BOOL DrawPolygon(POINT *apt, int cpt);

	//����ͬʱ���ƶ����յĶ���Ρ�
	BOOL DrawPolyPolygon(POINT *apt, int *asz, int csz);

	//�������
	//BOOL GradientFill(CONST PTRIVERTEX pVertex, DWORD dwNumVertex, CONST PVOID pMesh, DWORD dwNumMesh, DWORD dwMode);

	//�������
	BOOL DrawString(SString str, RECT rt, UINT format = DT_CALCRECT);

	//���λͼ
	BOOL DrawImage(HBITMAP hbm, int x, int y, int nWidth, int nHeight, int xSrc = 0, int ySrc = 0, DWORD dwRop = SRCCOPY);


};

#endif