/**
* SCurson类
* 光标类
* @author ZeroX
* @version v1.0 29/07/2017
*/
#include "SHandle.h"
#ifndef _SCURSOR_H_
#define _SCURSOR_H_

class SCursor :public SHandle<HCURSOR>
{
public:
	SCursor(HCURSOR hCursor=NULL);
	virtual ~SCursor();
public:
	//创建一个指定大小、位模式和热点的光标
	BOOL Create(HINSTANCE htnst, int xHotSpot, int yHotSpot, int nWidth, int nHeight, CONST VOID *pvANDPlane, CONST VOID *pvXORPlane);

	//从资源中加载位图
	BOOL Load(UINT uRcid, HINSTANCE hInstance = NULL);

	//从文件中加载位图
	BOOL Load(LPTSTR lpFileName, HINSTANCE hInstance = NULL);

	//销毁一个光标并释放它占用的任何内存,不要使用该函数去销毁一个共享光标
	BOOL Destroy();


};

#endif