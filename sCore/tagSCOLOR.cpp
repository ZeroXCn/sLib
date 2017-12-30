#include "tagSCOLOR.h"

tagSCOLOR::tagSCOLOR()
{
	dwColor = 0x00;
}
tagSCOLOR::tagSCOLOR(unsigned long dwColor)
{
	this->dwColor = dwColor;
}
tagSCOLOR::tagSCOLOR(unsigned char alpha, unsigned char red, unsigned char green, unsigned char blue)
{
	SetAlpha(alpha);
	SetRed(red);
	SetGreen(green);
	SetBlue(blue);
}
tagSCOLOR::tagSCOLOR(unsigned char red, unsigned char green, unsigned char blue)
{
	SetAlpha(0xff);
	SetRed(red);
	SetGreen(green);
	SetBlue(blue);
}

void tagSCOLOR::SetAlpha(unsigned char alpha)
{
	this->dwColor = ((this->dwColor & 0x00ffffff) | (alpha << 24));
}
void tagSCOLOR::SetRed(unsigned char red)
{
	this->dwColor = ((this->dwColor & 0xff00ffff) | (red << 16));
}
void tagSCOLOR::SetGreen(unsigned char green)
{
	this->dwColor = ((this->dwColor & 0xffff00ff) | (green << 8));
}
void tagSCOLOR::SetBlue(unsigned char blue)
{
	this->dwColor = ((this->dwColor & 0xffffff00) | (blue << 0));
}

unsigned char tagSCOLOR::GetAlpha()
{
	return ((this->dwColor >> 24) & 0xff);
}
unsigned char tagSCOLOR::GetRed()
{
	return ((this->dwColor >> 16) & 0xff);

}
unsigned char tagSCOLOR::GetGreen()
{
	return ((this->dwColor >> 8) & 0xff);
}
unsigned char tagSCOLOR::GetBlue()
{
	return ((this->dwColor >> 0) & 0xff);
}

unsigned long tagSCOLOR::GetColor()
{
	return this->dwColor;
}
void tagSCOLOR::SetColor(unsigned long dwColor)
{
	this->dwColor = dwColor;
}
tagSCOLOR &tagSCOLOR::operator =(unsigned long dwColor)
{
	SetColor(dwColor);
	return *this;
}

tagSCOLOR &tagSCOLOR::operator =(const tagSCOLOR sColor)
{
	this->dwColor = sColor.dwColor;
	return *this;
}