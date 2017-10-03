/**
*
*	SColor类
*	封装颜色类
*	@author ZeroX
*	@version v1.0 22/07/2017()
*
*/
/* 不同编译器下unsigned int长度不同,32位下是32位,16位下是16位,最好用unsigned long代替(最低32位) */

#include "../sCore/SObject.h"

#ifndef _SCOLOR_H_
#define _SCOLOR_H_
class SColor:public SObject
{
protected:
	unsigned char alpha,red,green,blue;
public:
	unsigned char GetAlpha(){
		return alpha;
	}
	unsigned char GetRed(){
		return red;
	}
	unsigned char GetGreen(){
		return green;
	}
	unsigned char GetBlue(){
		return blue;
	}

	void SetAlpha(unsigned char alpha){
		this->alpha=alpha;
	}
	void SetRed(unsigned char red){
		this->red=red;
	}
	void SetGreen(unsigned char green){
		this->green=green;
	}
	void SetBlue(unsigned char blue){
		this->blue=blue;
	}
public:
	void SetARGB(unsigned long argb){
		this->blue=(argb>>0 & 0xff);
		this->green=(argb>>8 & 0xff);
		this->red=(argb>>16 & 0xff);
		this->alpha=(argb>>24 & 0xff);
		
	}
	unsigned long GetARGB(){
		unsigned long argb=0;
		argb=(argb<<0 | this->alpha);
		argb=(argb<<8 | this->red); 
		argb=(argb<<8 | this->green);
		argb=(argb<<8 | this->blue);
		return argb;
	}
public:
	SColor(unsigned char red, unsigned char green, unsigned char blue)
	{
		SetAlpha(255);
		SetRed(red);
		SetGreen(green);
		SetBlue(blue);
	}

	SColor(unsigned char alpha,unsigned char red,unsigned char green,unsigned char blue)
	{
		SetAlpha(alpha);
		SetRed(red);
		SetGreen(green);
		SetBlue(blue);
	}
	SColor(unsigned long argb)
	{
		SetARGB(argb);
	}

};

#endif