/**
* SBitmap��
* GDI����-λͼ��
* @author ZeroX
* @version v1.0 25/07/2017
*/
#include "SGdiObject.h"
#ifndef _SBITMAP_H_
#define _SBITMAP_H_
class SBitmap:public SGdiObject
{
protected:
	BITMAP m_sBitmap;		//λͼ�ṹ��
public:
	//����һ�������ض���ȡ��߶Ⱥ���ɫ��ʽ��λͼ��
	HBITMAP CreateBitmap(int nWidth, int nHeight, UINT cPlanes, UINT cBitsPeral, CONST VOID *lpvBits);

	//������ָ�����豸������ص��豸���ݵ�λͼ
	HBITMAP CreateCompatibleBitmap(HDC hdc, int nWidth, int nHeight);

	//����һ�������ض���ȡ��߶Ⱥ���ɫ��ʽ��λͼ
	HBITMAP CreateBitmaplndirect(CONST BITMAP *lpbm);

public:
	//��ģ��Ŀ�ִ���ļ��м���ָ����λͼ��Դ-�ѱ�ȡ��
	HBITMAP LoadBitmap(HINSTANCE hInstance, LPCTSTR lpBitmapName);

	//�ú���װ��ͼ�꣬��꣬��λͼ
	HANDLE LoadImage(
		HINSTANCE hinst,
		LPCTSTR lpszName,
		UINT uType,
		int cxDesired,
		int cyDesired,
		UINT fuLoad
		);
public:

	int GetWidth();

	int GetHeight();
public:


};

#endif