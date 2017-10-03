/**
* SGraphics��
* ͼ�������
* @author ZeroX
* @version v1.0 25/07/2017
*/
#include "SDc.h"
#ifndef _SGRAPHICS_H_
#define _SGRAPHICS_H_

class SGraphics:public SObject
{
protected:
	HWND m_hWnd;
	HDC m_hDC;
	int m_nWidth, m_nHeight;
public:
	SGraphics();
	SGraphics(HWND hWnd,HDC hDC=NULL);
	virtual ~SGraphics();

	//���ھ��
	HWND GetWnd();
	void SetWnd(HWND hWnd);

	//��ȡ����DC�豸
	HDC GetDC();
	void SetDC(HDC hDC);

	//���ÿ��
	void SetWidth(int nWidth);
	void SetHeight(int nHeight);
	//���ÿ��
	int GetWidth();
	int GetHeight();
public:
	//ѡ������
	SFont SetFont(SFont ofont);
	SFont GetFont();
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
	BOOL FillRect(int left, int top, int right, int bottom, HBRUSH hbr);
	BOOL FillRect(int left, int top, int right, int bottom, COLORREF crColor = BLACK_COLOR);

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

	//�������
	BOOL DrawString(SString str, int x, int y, SFont sFont, COLORREF crColor = BLACK_COLOR, BOOL bTrans = TRUE, UINT format = DT_LEFT);
	BOOL DrawString(SString str, int x, int y, COLORREF crColor = BLACK_COLOR, BOOL bTrans = TRUE, UINT format = DT_LEFT);
	int DrawString(SString str, RECT rt, UINT format = DT_CALCRECT);
	//������߿�����
	int DrawStringEx(SString str, LPRECT lprc, UINT dwDTFormat = DT_LEFT, LPDRAWTEXTPARAMS lpDTParams = NULL);

	//���λͼ
	BOOL DrawImage(SBitmap sbm, int x, int y, DWORD dwRop = SRCCOPY);
	BOOL DrawImage(SBitmap sbm, int x, int y, UINT crTransparent);	//���߲�������,������Ҫǿ��ת��
	BOOL DrawImage(SBitmap sbm, int x, int y, int nWidth, int nHeight, int xSrc = 0, int ySrc = 0, DWORD dwRop = SRCCOPY);
	BOOL DrawImage(SBitmap sbm, int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, int xSrcWidth, int ySrcHeight, DWORD dwRop = SRCCOPY);
	BOOL DrawImage(SBitmap sbm, int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, UINT crTransparent = RGB(255, 255, 255));
	BOOL DrawImage(SBitmap sbm, int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, int xSrcWidth, int ySrcHeight, UINT crTransparent);
	BOOL DrawImage(SBitmap sbm, int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, SBitmap sMarkBitmap, int xMark, int yMark, DWORD dwRop = MAKEROP4(SRCPAINT, SRCCOPY));
	BOOL DrawImage(SBitmap sbm, int x, int y, SBitmap sMarkBitmap, int xSrc = 0, int ySrc = 0, DWORD dwRop = MAKEROP4(SRCPAINT, SRCCOPY));
	//�������
	BOOL DrawDC(SDc sdcSrc, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, DWORD dwRop = SRCCOPY);
	BOOL DrawDC(SDc sdcSrc, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, int nXOriginSrc = 0, int nYOriginSrc = 0, DWORD dwRop = SRCCOPY);

};

#endif