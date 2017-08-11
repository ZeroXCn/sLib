/**
* SIcon类
* 图标类
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
	HICON m_hIcon;			//图标
public:
	SIcon();
	SIcon(HICON hIcon);
	virtual ~SIcon();
public:
	void SetHandle(HICON hIcon);
	HICON GetHandle();

public:
	/*
	hInstance------Long，准备拥有图标的应用程序的实例的句柄。可用GetWindowWord函数获得拥有一个窗体或控件的一个实例的句柄
	nWidth--------- Long，图标图象的宽度。可用GetSystemMetrics函数判断一个特定设备的正确编号。VGA的编号是32
	nHeight--------Long，图标图象的高度。可用GetSystemMetrics函数判断一个特定设备的正确编号。VGA的编号是32
	nPlanes--------Byte，lpXORbits数据数组中的色层数量
	nBitsPixel---- - Byte，lpXORbits数据数组中每像素的位数
	lpANDbits------Byte，指向AND位图数据的指针
	lpXORbits------Byte，指向XOR位图数据的指针
	*/
	BOOL Create(HINSTANCE hInstance,int nWidth,int nHeight,BYTE cPlanes,BYTE cBitsPixel,const BYTE *lpbANDbits,const BYTE *lpbXORbits);

	//从资源中加载位图
	BOOL Load(UINT uRcid, HINSTANCE hInstance = NULL);

	//从文件中加载位图
	BOOL Load(LPTSTR lpFileName, HINSTANCE hInstance = NULL);

	//撤销图标
	BOOL Destroy();
public:
	//绘制图标。
	BOOL DrawIcon(HDC hDC, int x, int y);
	//
	BOOL DrawIconEx(HDC hdc, int x, int y, int nWidth, int nHeight, UINT istepifAniCur=0, HBRUSH hbrFlickerFreeDraw=NULL, UINT diFlags=DI_NORMAL);
};

#endif