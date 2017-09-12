/**
* SBitmapDc��
* λͼDC��
* @author �������緹��
* @link http://blog.csdn.net/w18767104183/article/details/7390835
* @version v1.0 2012-03-24 20:19
*/

#include "SDc.h"
#include "SBitmap.h"
#ifndef _SBITMAPDC_H_
#define _SBITMAPDC_H_

class SBitmapDc :
	public SDc,
	public SBitmap
{
private:
	using SBitmap::SetHandle;
	using SBitmap::GetHandle;
	using SBitmap::GetHandleStruct;
	using SBitmap::Create;
	using SBitmap::CreateCompatible;
	using SBitmap::CreateIndirect;
	using SBitmap::CreateDIBSection;
	using SBitmap::Load;
	using SBitmap::Delete;

	using SDc::SetHandle;
	using SDc::GetHandle;
	using SDc::CreateDC;
	using SDc::CreateCompatibleDC;
	using SDc::DeleteDC;
public:
	SBitmapDc();
	virtual ~SBitmapDc();

	//ɾ������
	void Delete();
	//��������
	void Create(int nWidth, int nHeight);

	//ȡ�ø������
	HDC GetSafeHdc();
	HBITMAP GetBmpHandle();
	DWORD* GetBits(void);

protected:
	char*   m_pBits;
};

#endif