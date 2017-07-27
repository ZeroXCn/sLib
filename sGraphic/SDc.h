/**
* SDc��
* HDC��װ��
* @author ZeroX
* @version v1.0 25/07/2017
*/

#include "../sCore/SObject.h"
#include "../sCore/SString.h"

#include "SGdiObject.h"
#include "SBitmap.h"
#include "SFont.h"
#include "SBrush.h"
#include "SPen.h"
#include "SRgn.h"
#include "SPalette.h"

#ifndef _SDC_H_
#define _SDC_H_
#include <Windows.h>
#include <Mmsystem.h>
#include <wingdi.h>

#pragma	comment(lib,"winmm.lib" )
#pragma comment(lib,"gdi32.lib")

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
	//�����豸�����Ļ���
	SDc &CreateDc(LPTSTR lpszDriver, LPTSTR lpszDevice = NULL, LPTSTR lpszPort = NULL, const DEVMODE *pdm = NULL);

	// ����һ����ָ���豸���ݵ��ڴ��豸�����Ļ���
	SDc &CreateCompatibleDc(SDc dc);

	// ɾ��ָ�����豸�����Ļ�����Dc����
	BOOL DeleteDC();
public:
	/* ���º���Ϊ�������DC���ݵ�GDI���� */
	//�������ݸ�DC��λͼ����
	SBitmap CreateBitmap(int nWidth, int nHeight);


public:
	//ѡ��һ����ָ�����豸�����Ļ�����
	HGDIOBJ SelectObject(HGDIOBJ hgdiobj);
	SGdiObject SelectObject(SGdiObject pObj);

	//��ȡ��ǰDC����
	HGDIOBJ GetCurrentObject(UINT uObjectType);
	//��ȡ��������
	UINT GetObjectType(HGDIOBJ hObject);

	//ɾ�����ͷ�ϵͳ��Դ
	BOOL DeleteObject(HGDIOBJ hObject);
	BOOL DeleteObject(SGdiObject pObj);
	
	//ѡ������
	SFont SetFont(SFont ofont);
	SFont GetFont();
	//ѡ��λͼ
	SBitmap SetBitmap(SBitmap bitmap);
	SBitmap GetBitmap();
	//ѡ��ˢ
	SBrush SetBrush(SBrush brush);
	SBrush GetBrush();
	//ѡ�񻭱�
	SPen SetPen(SPen pen);
	SPen GetPen();
	//ѡ������
	SRgn SetRgn(SRgn rgn);

	//��ɫ��
	SPalette GetPalette();


public:
	//ָ���豸�����������ֶ����־
	UINT SetTextAlign(UINT fMode); // �ı�����ѡ��
	UINT GetTextAlign(); // �ı�����ѡ��

	//�����ı���ɫ
	COLORREF SetTextColor(COLORREF crColor);
	COLORREF GetTextColor();

	//���ñ���ɫ
	COLORREF SetBkColor(COLORREF color);
	COLORREF SetBkColor(BOOL bTrans);
	COLORREF GetBkColor();

	//���ñ���ģʽ-OPAQUE��͸����TRANSPARENT͸��
	int SetBkMode(int iBkMode);
	int GetBkMode();

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
	BOOL FillRect(int left, int top, int right, int bottom, COLORREF crColor=BLACK_COLOR);

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
	BOOL DrawString(SString str, int x, int y, COLORREF crColor = BLACK_COLOR, BOOL bTrans = TRUE, UINT format = DT_LEFT);
	int DrawString(SString str, RECT rt, UINT format = DT_CALCRECT);
	//������߿�����
	int DrawStringEx(SString str, LPRECT lprc, UINT dwDTFormat = DT_LEFT, LPDRAWTEXTPARAMS lpDTParams = NULL);

	//���λͼ
	BOOL DrawImage(HBITMAP hbm, int x, int y, DWORD dwRop = SRCCOPY);
	BOOL DrawImage(HBITMAP hbm, int x, int y, UINT crTransparent);
	BOOL DrawImage(HBITMAP hbm, int x, int y, int nWidth, int nHeight, int xSrc = 0, int ySrc = 0, DWORD dwRop = SRCCOPY);
	BOOL DrawImage(HBITMAP hbm, int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, int xSrcWidth, int ySrcHeight, DWORD dwRop = SRCCOPY);
	BOOL DrawImage(HBITMAP hbm, int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, UINT crTransparent = RGB(255, 255, 255));
	BOOL DrawImage(HBITMAP hbm, int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, int xSrcWidth, int ySrcHeight, UINT crTransparent );

};

#endif