/**
* tagSSIZE½á¹¹Ìå
* ³ß´ç
* @author ZeroX
* @version v1.0 03/09/2017
*/
#ifndef _TAGSSIZE_H_
#define _TAGSSIZE_H_
#include <Windows.h>
typedef struct tagSSIZE:public SIZE
{
	tagSSIZE();
	tagSSIZE(const SIZE size);
	tagSSIZE(int cx, int cy);

	bool operator ==(tagSSIZE size);
	tagSSIZE &operator =(tagSSIZE size);
}SSIZE;

#endif