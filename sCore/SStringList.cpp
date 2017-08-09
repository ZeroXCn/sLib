#include "SStringList.h"
using namespace std;

SStringList::SStringList(){}
SStringList::SStringList(char ch){
	SString sch; sch += ch;
	push_back(sch);
}
SStringList::SStringList(SString str){
	push_back(str);
}

SStringList::SStringList(const SStringList &strlist){
	for (SStringList::const_iterator it = strlist.begin(); it != strlist.end(); it++)
		push_back(*it);
}

SStringList::SStringList(const vector<SString> &vec){
	for (vector<SString>::const_iterator it = vec.begin(); it != vec.end(); it++)
		push_back(*it);
}

SStringList &SStringList::operator &= (SStringList &stl)
{
	for (iterator ita = this->begin(); ita != this->end();){
		SStringList::iterator itb;
		for (itb = stl.begin(); itb != stl.end(); itb++){
			if (*ita == *itb) break;
		}
		if (itb == stl.end())
			ita = this->erase(ita);
		else ita++;
	}

	return *this;
}

SStringList &SStringList::operator |= (SStringList &stl)
{

	for (iterator itb = stl.begin(); itb != stl.end(); itb++){
		iterator ita = this->end();
		for (ita = this->begin(); ita != this->end();)
		if (*ita == *itb) break;
		else ita++;
		if (ita == this->end())
			this->push_back(*itb);
	}

	return *this;
}
SStringList SStringList::operator & (SStringList &stl)
{
	SStringList result;

	for (iterator itb = stl.begin(); itb != stl.end(); itb++){
		iterator ita = this->end();
		for (ita = this->begin(); ita != this->end();)
		if (*ita == *itb) break;
		else ita++;
		if (ita != this->end())
			result.push_back(*itb);
	}

	return result;
}

SStringList SStringList::operator | (SStringList &stl)
{
	SStringList result = *this;

	for (iterator itb = stl.begin(); itb != stl.end(); itb++){
		iterator ita;
		for (ita = result.begin(); ita != result.end(); ita++)
		if (*ita == *itb) break;
		if (ita == result.end())
			result.push_back(*itb);
	}

	return result;
}

SStringList &SStringList::operator -= (SStringList &stl)
{
	for (iterator itb = stl.begin(); itb != stl.end(); itb++){
		for (iterator ita = this->begin(); ita != this->end();)
		if (*ita == *itb) ita = this->erase(ita);
		else ita++;
	}
	return *this;
}

SStringList SStringList::operator - (SStringList &stl)
{
	SStringList result = *this;
	for (iterator itb = stl.begin(); itb != stl.end(); itb++){
		for (iterator ita = result.begin(); ita != result.end();)
		if (*ita == *itb) ita = result.erase(ita);
		else ita++;
	}
	return result;
}

SStringList &SStringList::operator += (SStringList &stl)
{
	for (iterator it = stl.begin(); it != stl.end(); it++)
		this->push_back(*it);
	return *this;
}

SStringList SStringList::operator + (SStringList &stl)
{
	SStringList result = *this;
	for (iterator it = stl.begin(); it != stl.end(); it++)
		result.push_back(*it);
	return result;
}

SStringList &SStringList::operator =(SStringList &strlist)
{
	this->clear();
	for (SStringList::const_iterator it = strlist.begin(); it != strlist.end(); it++)
		push_back(*it);
	return *this;
}

bool SStringList::operator == (SStringList &stl)
{
	iterator ita = this->begin();
	SStringList::iterator itb = stl.begin();
	while (ita != this->end() && itb != stl.end())
	{
		if (*ita == *itb){ ita++; itb++; }
		else return false;
	}
	if (ita == this->end() && itb == stl.end())return true;
	else return false;
}

///
SStringList &SStringList::operator &= (SString str)
{
	this->clear();
	this->push_back(str);
	return *this;
}

SStringList &SStringList::operator |= (SString str)
{
	for (iterator it = this->begin(); it != this->end(); it++)
	if (*it == str) return *this;
	this->push_back(str);
	return *this;
}
SStringList SStringList::operator & (SString str)
{
	SStringList result;
	result.push_back(str);
	return result;
}

SStringList SStringList::operator | (SString str)
{
	SStringList result = *this;
	for (iterator it = result.begin(); it != result.end(); it++)
	if (*it == str) return *this;
	this->push_back(str);
	return result;
}


SStringList &SStringList::operator += (SString str)
{
	this->push_back(str);
	return *this;
}

SStringList SStringList::operator + (SString str)
{
	SStringList result = *this;
	result.push_back(str);
	return result;
}

SStringList &SStringList::operator -= (SString str)
{
	for (iterator it = this->begin(); it != this->end();)
	{
		if (*it == str) it = this->erase(it);
		else it++;
	}
	return *this;
}

SStringList SStringList::operator - (SString str)
{
	SStringList result = *this;
	for (iterator ita = result.begin(); ita != result.end();){
		if (*ita == str) ita = this->erase(ita);
		else ita++;
	}
	return result;
}


SStringList &SStringList::operator <<(SString str)
{
	this->push_back(str);
	return *this;
}

SStringList &SStringList::operator <<(SStringList &stl)
{
	for (iterator it = stl.begin(); it != stl.end(); it++)
		this->push_back(*it);
	return *this;
}


int SStringList::find(SString str, int start)
{
	if (start >= (int)this->size() || start < 0)
		return -1;
	for (int i = start; i<(int)this->size(); i++)
	if (str == this->at(i))return i;
	return -1;
}

SStringList SStringList::sublist(int start, int length)
{
	SStringList result;

	if (start < 0)
		return result;

	int maxsize = this->size();
	length = length<0 ? (maxsize) : length;
	for (int i = start; i<(start + length); i++)
	{
		if (i >= maxsize) break;
		result.push_back(this->at(i));
	}

	return result;

}
SString &SStringList::at(int index)
{
	return vector<SString>::at(index);
}
SString SStringList::at(int index, SString defaultstr)
{
	try{
		return vector<SString>::at(index);
	}
	catch (...){
		return defaultstr;
	}
}


SStringList &SStringList::distinct()
{
	for (iterator ita = this->begin(); ita != this->end(); ita++)
	for (iterator itb = ita + 1; itb != this->end();)
	if (*ita == *itb) itb = this->erase(itb);
	else itb++;

	return *this;
}

SString SStringList::toString()
{
	SString result;
	for (iterator it = this->begin(); it != this->end(); it++)
		result += *it;
	return result;
}

tostream &operator << (tostream& os, SStringList &ob)
{
	for (SStringList::iterator it = ob.begin(); it != ob.end(); it++)
		os << *it << endl;
	return os;
}

tistream &operator >> (tistream& is, SStringList &ob)
{
	SString str;
	is >> str;
	ob.push_back(str);
	return is;
}
