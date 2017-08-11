/**
* SFont��
* GDI����-������
* @author ZeroX
* @version v1.0 25/07/2017
*/
#include "SGdiObject.h"
#ifndef _SFONT_H_
#define _SFONT_H_

#include <Windows.h>

class SFont :public SGdiObject
{
public:
	SFont();
	SFont(SGdiObject Obj);
	SFont(HFONT hFont);
	virtual ~SFont();
public:
	void SetHandle(HFONT hFont);

	HFONT GetHandle();

	LOGFONT GetFontStruct();
public:
	//����Ĭ��
	BOOL Create();

	//��������-����,��ʽ,��С
	BOOL Create(int nHeight, LPCTSTR lpszFace=NULL, DWORD fdwItalic = FALSE, DWORD fdwUnderline = FALSE, DWORD fdwStrikeOut = FALSE);

	//����ָ����ʽ����
	BOOL Create(int nHeight,								// �߼�����߶ȵĸ߶�-�����С(ȡ��ֵ)
				int nWidth,									// �ַ�ƽ�����
				int nEscapement=0,								// �о�Ƕ�-ָ����λ�������豸X��֮���һ���Ƕ�
				int nOrientation=0,								// ���߷����-ÿ���ַ���X��Ƕ�
				int fnWeight=0,									// ���������-�ֺ�400��ʾ��׼�壬700��ʾ�ڣ��֣��壬�����ֵΪ0����ʹ��ȱʡ��Ȩֵ
				DWORD fdwItalic=FALSE,							// б�����Ա�־
				DWORD fdwUnderline = FALSE,						// �»������Ա�־
				DWORD fdwStrikeOut = FALSE,						// ɾ�������Ա�־
				DWORD fdwCharSet=ANSI_CHARSET,					// �ַ�����ʶ��
				DWORD fdwOutputPrecision=OUT_TT_ONLY_PRECIS,	// �������
				DWORD fdwClipPrecision=CLIP_DEFAULT_PRECIS,		// ���о���
				DWORD fdwQuality=DEFAULT_QUALITY,				// �������
				DWORD fdwPitchAndFamily=FF_DONTCARE,			// ���ߺͼ�ͥ
				LPCTSTR lpszFace=NULL							// ָ��ָ�����������ַ���
		);

	//����һ����ָ���ṹ���������Ե��߼�����
	BOOL CreateIndirect(LOGFONT lFont);
public:

};

#endif;