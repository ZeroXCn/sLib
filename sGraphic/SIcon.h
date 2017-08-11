/**
* SIcon��
* ͼ����
* @author ZeroX
* @version v1.0 29/07/2017
*/
#include "../sCore/SObject.h"
#ifndef _SICON_H_
#define _SICON_H_
#include <Windows.h>
class SIcon :public SObject
{
protected:
	HICON m_hIcon;			//ͼ��
public:
	SIcon();
	SIcon(HICON hIcon);
	virtual ~SIcon();
public:
	void SetHandle(HICON hIcon);
	HICON GetHandle();

public:
	/*
	hInstance------Long��׼��ӵ��ͼ���Ӧ�ó����ʵ���ľ��������GetWindowWord�������ӵ��һ�������ؼ���һ��ʵ���ľ��
	nWidth--------- Long��ͼ��ͼ��Ŀ�ȡ�����GetSystemMetrics�����ж�һ���ض��豸����ȷ��š�VGA�ı����32
	nHeight--------Long��ͼ��ͼ��ĸ߶ȡ�����GetSystemMetrics�����ж�һ���ض��豸����ȷ��š�VGA�ı����32
	nPlanes--------Byte��lpXORbits���������е�ɫ������
	nBitsPixel---- - Byte��lpXORbits����������ÿ���ص�λ��
	lpANDbits------Byte��ָ��ANDλͼ���ݵ�ָ��
	lpXORbits------Byte��ָ��XORλͼ���ݵ�ָ��
	*/
	BOOL Create(HINSTANCE hInstance,int nWidth,int nHeight,BYTE cPlanes,BYTE cBitsPixel,const BYTE *lpbANDbits,const BYTE *lpbXORbits);

	//����Դ�м���λͼ
	BOOL Load(UINT uRcid, HINSTANCE hInstance = NULL);

	//���ļ��м���λͼ
	BOOL Load(LPTSTR lpFileName, HINSTANCE hInstance = NULL);

	//����ͼ��
	BOOL Destroy();
public:
	//����ͼ�ꡣ
	BOOL DrawIcon(HDC hDC, int x, int y);
	//
	BOOL DrawIconEx(HDC hdc, int x, int y, int nWidth, int nHeight, UINT istepifAniCur=0, HBRUSH hbrFlickerFreeDraw=NULL, UINT diFlags=DI_NORMAL);
};

#endif