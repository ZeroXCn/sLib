#include "tagSPOINT.h"

tagSPOINT::tagSPOINT()
{

}

tagSPOINT::tagSPOINT(const POINT pt)
{
	this->x = pt.x;
	this->y = pt.y;
}

tagSPOINT::tagSPOINT(int x, int y)
{
	this->x = x;
	this->y = y;
}

bool tagSPOINT::IsCollsion(tagSPOINT pt)
{
	if (this->x == pt.x && this->y == pt.y)
		return true;
	else return false;
}

bool tagSPOINT::IsCollsion(RECT rt) 
{
	if (this->x >= rt.left && this->x <= rt.right && this->y >= rt.top && this->y <= rt.bottom) {
		return true;
	}
	return false;
}

bool tagSPOINT::IsInRect(RECT rt)
{
	if (this->x > rt.left &&this->x < rt.right
		&& this->y > rt.top && this->y < rt.bottom)
		return true;
	else
		return false;
}
bool tagSPOINT::IsOnRect(RECT rt)
{
	if (this->x == rt.left || this->x == rt.right || this->y == rt.top || this->y == rt.bottom)return true;
	else return false;
}

bool tagSPOINT::operator == (const POINT pt)
{
	if (this->x == pt.x && this->y == pt.y)
		return true;
	else return false;
}

SPOINT &tagSPOINT::operator =(const tagSPOINT pt)
{
	this->x = pt.x;
	this->y = pt.y;
	return *this;
}