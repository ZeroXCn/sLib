/**
*
*	SARGB类
*	封装颜色类
*	@author ZeroX
*	@version v1.0 22/07/2017()
*
*/

#include "SObject.h"

#ifndef _SARGB_H_
#define _SARGB_H_
class SARGB
{
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
	void SetARGB(unsigned int argb){
		this->blue=(argb>>0 & 0xff);
		this->green=(argb>>8 & 0xff);
		this->red=(argb>>16 & 0xff);
		this->alpha=(argb>>24 & 0xff);
		
	}
	unsigned int GetARGB(){
		unsigned int argb=0;
		argb=(argb<<0 | this->alpha);
		argb=(argb<<8 | this->red); 
		argb=(argb<<8 | this->green);
		argb=(argb<<8 | this->blue);
		return argb;
	}
public:
	SARGB(unsigned char alpha,unsigned char red,unsigned char green,unsigned char blue)
	{
		SetAlpha(alpha);
		SetRed(red);
		SetGreen(green);
		SetBlue(blue);
	}
	SARGB(unsigned int argb)
	{
		SetARGB(argb);
	}

};

#endif