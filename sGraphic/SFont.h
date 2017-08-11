/**
* SFont类
* GDI对象-字体类
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
	//创建默认
	BOOL Create();

	//创建字体-字体,样式,大小
	BOOL Create(int nHeight, LPCTSTR lpszFace=NULL, DWORD fdwItalic = FALSE, DWORD fdwUnderline = FALSE, DWORD fdwStrikeOut = FALSE);

	//创建指定样式字体
	BOOL Create(int nHeight,								// 逻辑字体高度的高度-字体大小(取负值)
				int nWidth,									// 字符平均宽度
				int nEscapement=0,								// 行距角度-指定移位向量和设备X轴之间的一个角度
				int nOrientation=0,								// 基线方向角-每个字符与X轴角度
				int fnWeight=0,									// 字体的重量-粗黑400表示标准体，700表示黑（粗）体，如果此值为0，则使用缺省的权值
				DWORD fdwItalic=FALSE,							// 斜体属性标志
				DWORD fdwUnderline = FALSE,						// 下划线属性标志
				DWORD fdwStrikeOut = FALSE,						// 删除线属性标志
				DWORD fdwCharSet=ANSI_CHARSET,					// 字符集标识符
				DWORD fdwOutputPrecision=OUT_TT_ONLY_PRECIS,	// 输出精度
				DWORD fdwClipPrecision=CLIP_DEFAULT_PRECIS,		// 剪切精度
				DWORD fdwQuality=DEFAULT_QUALITY,				// 输出质量
				DWORD fdwPitchAndFamily=FF_DONTCARE,			// 音高和家庭
				LPCTSTR lpszFace=NULL							// 指针指向字体名称字符串
		);

	//创建一种在指定结构定义其特性的逻辑字体
	BOOL CreateIndirect(LOGFONT lFont);
public:

};

#endif;