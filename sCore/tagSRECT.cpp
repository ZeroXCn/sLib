#include "tagSRECT.h"

tagSRECT::tagSRECT()
{

}
tagSRECT::tagSRECT(const RECT rt)
{
	this->left = rt.left;
	this->right = rt.right;
	this->top = rt.top;
	this->bottom = rt.bottom;
}

tagSRECT::tagSRECT(int left, int top, int right, int bottom)
{
	this->left = left;
	this->right = right;
	this->top = top;
	this->bottom = bottom;
}
int tagSRECT::GetX()
{
	return left;
}
int tagSRECT::GetY()
{
	return right;
}
int tagSRECT::GetWidth()
{
	return right - left;
}

int tagSRECT::GetHeight()
{
	return bottom - top;
}
//ȡ�����
int tagSRECT::GetArea()
{
	return GetWidth() * GetHeight();
}
//ȡ���ܳ�
int tagSRECT::GetPerimeter()
{
	return 2 * (GetWidth() + GetHeight());
}
//ȡ�ü�������
POINT tagSRECT::GetCenter()
{
	POINT pt;
	pt.x = (this->right - this->left) / 2;
	pt.y = (this->bottom - this->top) / 2;
	return pt;
}
//�������ƶ�����
void tagSRECT::Move(int x, int y)
{
	this->left += x;
	this->right += x;
	this->top += y;
	this->bottom += y;
}
//�ƶ���ָ�����ε�����
void tagSRECT::MoveToCenter(RECT rt)
{
	//ȡ��rt���ĵ�Ͷ����е�
	int rtCenterX = (rt.right - rt.left) / 2;
	int rtCenterY = (rt.bottom - rt.top) / 2;
	int objCenterX = (this->right - this->left) / 2;
	int objCenterY = (this->bottom - this->top) / 2;

	//���λ������
	int disX = rtCenterX - objCenterX;
	int disY = rtCenterY - objCenterY;

	//�ö������ĵ�����ͼ���ĵ��غ�
	Move(disX, disY);

}

bool tagSRECT::IsCollision(tagSRECT rt)
{
	int x1 = this->GetX(), x2 = rt.GetX(), y1 = this->GetY(), y2 = rt.GetY();
	int w1 = this->GetWidth(), w2 = rt.GetWidth(), h1 = this->GetHeight(), h2 = rt.GetHeight();

	if (x1 >= x2 && x1 >= x2 + w2) {
		return false;
	}
	else if (x1 <= x2 && x1 + w1 <= x2) {
		return false;
	}
	else if (y1 >= y2 && y1 >= y2 + h2) {
		return false;
	}
	else if (y1 <= y2 && y1 + h1 <= y2) {
		return false;
	}
	return true;
}

bool tagSRECT::IsCollision(RECT rt, RECT *out)
{
	return ::IntersectRect(out, this, &rt)?true:false;
}

bool tagSRECT::IsInRect(tagSRECT rt)
{
	if (((GetX() >= rt.GetX()) && ((GetX() + GetWidth()) <= (rt.GetX() + rt.GetWidth()))) && ((GetY() >= rt.GetY()) && ((GetY() + GetHeight()) <= (rt.GetY() + rt.GetHeight()))))
		return true;
	else
		return true;
}

bool tagSRECT::operator ==(tagSRECT rt)
{
	if (this->left == rt.left &&
		this->right == rt.right &&
		this->top == rt.top &&
		this->bottom == rt.bottom
		) return true;
	else return false;
}
tagSRECT &tagSRECT::operator =(tagSRECT rt)
{
	this->left = rt.left;
	this->right = rt.right;
	this->top = rt.top;
	this->bottom = rt.bottom;
	return *this;
}