/**
* SGraphic��
* ͼ����Ⱦ��
* @author ZeroX
* @version v1.0 21/07/2017
*/

#include "../sCore/SObject.h"
#include "../sCore/SString.h"
#ifndef _SGRAPHIC_H_
#define _SGRAPHIC_H_
#include <Windows.h>

#define RED_COLOR RGB(255,0,0)
#define GREEN_COLOR RGB(255,0,0)
#define BLUE_COLOR RGB(255,0,0)
#define WHITE_COLOR RGB(255,255,255)
#define BLACK_COLOR RGB(0,0,0)

class SGraphics:public SObject
{
protected:
	HWND m_hWnd;		//������
	HDC m_hDC;			//��ͼ�豸
public:
	SGraphics();
	SGraphics(HDC hDC);

	virtual ~SGraphics();
public:
	//��ʼ����
	HDC BeginPaint(LPPAINTSTRUCT lpPaint);

	//��������
	BOOL EndPaint(PAINTSTRUCT *lpPaint);

	//������ˢ
	HBRUSH CreateHatchBrush(
		_In_  int fnStyle,        // Ӱ����ʽ
		_In_  COLORREF clrref     // ��ˢ��ɫ
		);
	/*	CreateSolidBrush ����һ��ʵ����ɫ��Solid color����ˢ
		CreateHatchBrush ����һ��Ӱ��ģʽ��Hatch pattern���Ļ�ˢ
		CreatePatternBrush ����һ��λͼģʽ��Bitmap pattern���Ļ�ˢ
		CreateBrushIndirect ����ָ������ʽ����ɫ��ģʽ��pattern��������һ����ˢ
		CreateDIBPatternBrushPt ���� DIB ģʽ��pattern from DIB������һ����ˢ*/

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
	BOOL GradientFill(CONST PTRIVERTEX pVertex, DWORD dwNumVertex, CONST PVOID pMesh, DWORD dwNumMesh, DWORD dwMode);

	BOOL DrawImage();

	BOOL(DrawText)(LPTSTR lpchText, int cchText, RECT rt, UINT format);

	BOOL DrawString(SString str, RECT rt, UINT format);
};
#endif