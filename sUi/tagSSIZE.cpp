#include "tagSSIZE.h"

tagSSIZE::tagSSIZE()
{

}
tagSSIZE::tagSSIZE(const SIZE size)
{
	this->cx = size.cx;
	this->cy = size.cy;
}

tagSSIZE::tagSSIZE(int cx, int cy)
{
	this->cx = cx;
	this->cy = cy;
}


bool tagSSIZE::operator ==(tagSSIZE size)
{
	if (this->cx == size.cx && this->cy == size.cy)
		return true;
	else return false;
}
tagSSIZE &tagSSIZE::operator =(tagSSIZE size)
{
	this->cx = size.cx;
	this->cy = size.cy;
	return *this;
}