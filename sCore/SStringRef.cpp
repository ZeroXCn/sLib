#include "SStringRef.h"
#include <algorithm>
SStringRef::SStringRef() :m_ptr(nullptr), m_len(0)
{

}
SStringRef::SStringRef(const TCHAR* str) : m_ptr(str), m_len(_tcslen(str))
{

}
SStringRef::SStringRef(const TCHAR* str, std::string::size_type len) : m_ptr(str), m_len(len)
{

}
SStringRef::SStringRef(const SStringRef &ref) 
{
	m_ptr = ref.m_ptr;
	m_len = ref.m_len;
}

SStringRef&SStringRef::operator = (const SStringRef &ref)
{
	this->m_ptr = ref.m_ptr;
	this->m_len = ref.m_len;
	return *this;
}

int SStringRef::size() const
{
	return length();
}
int SStringRef::length() const
{
	return m_len;
}

bool SStringRef::empty() const
{
	if (m_ptr == nullptr || m_len == 0)return true;
	else return false;
}

const TCHAR &SStringRef::font()const
{
	return at(0);
}
const TCHAR &SStringRef::back()const
{
	return at(m_len-1);
}
const TCHAR *SStringRef::data()const
{
	return m_ptr;
}

void SStringRef::clear()
{
	m_len = 0;
	m_ptr = nullptr;
}

SStringRef SStringRef::substr(std::string::size_type pos, std::string::size_type n)
{
	return SStringRef(m_ptr + pos, n);
}
bool SStringRef::starts_with(TCHAR c) const
{
	if (font() == c)return true;
	else return false;
}
bool SStringRef::starts_with(SStringRef x) const
{
	int figure = memcmp(this->m_ptr, x.m_ptr, this->m_len<x.m_len ? this->m_len : x.m_len);
	if (figure == 0)
		return true;
	else
		return false;
}

bool SStringRef::ends_with(TCHAR c) const
{
	if (back() == c)return true;
	else return false;
}
bool SStringRef::ends_with(SStringRef x) const
{
	int len = x.length(), lenA = this->length();

	for (int i = 0; i<len; i++)
	{
		if (this->at(i + lenA - len) != x.at(i))
			return false;
	}
	return true;
}

int SStringRef::equals(SStringRef x) const
{

	int min = this->m_len < x.m_len ? this->m_len : x.m_len;
	int i = 0;
	for (i = 0; i < min; i++)
	{
		if (this->at(i) != x.at(i))
			return (int)this->at(i) - x.at(i);
	}

	if (this->m_len != x.m_len){
		return (int)this->m_len < x.m_len ? this->at(i) : x.at(i);
	}else return 0;
}
int SStringRef::equals(SStringRef x, std::string::size_type len) const
{
	return _tcsncmp(m_ptr, x.m_ptr, len);
}

int SStringRef::find(TCHAR c, std::string::size_type pos)const
{
	for (std::string::size_type i = pos; i < m_len; i++){
		if (this->at(i) == c)return i;
	}
	return std::string::npos;
	
}
int SStringRef::find(SStringRef x, std::string::size_type pos)const
{
	const TCHAR *p = std::find_first_of(this->m_ptr + pos, this->m_ptr + this->m_len, x.m_ptr, x.m_ptr + m_len);
	if (p)return p - m_ptr;
	else return std::string::npos;
}
int SStringRef::find_first_of(TCHAR c)const
{
	for (size_t i = 0; i < m_len; i++){
		if (at(i) == c)return i;
	}
	return std::string::npos;
}
int SStringRef::find_first_of(SStringRef x)const
{
	const TCHAR *p = std::find_first_of(this->m_ptr, this->m_ptr + this->m_len, x.m_ptr, x.m_ptr + m_len);
	if (p)return p - m_ptr;
	else return std::string::npos;
}
int SStringRef::find_last_of(TCHAR c)const
{
	for (auto i = m_len; i >= 0; i--){
		if (at(i) == c)return i;
	}
	return std::string::npos;
}
int SStringRef::find_last_of(SStringRef x)const
{

	//Ä£Ê½Æ¥Åä
	int i = m_len-1, j = x.m_len-1;
	while ((i>=0) && (j>=0))
	{
		if (this->at(i) == x.at(j))
		{
			i--; j--;
		}
		else
		{
			i = i + (x.m_len - 1 - j) - 1;
			j = x.m_len - 1;
		}
	}
	if (j <= 0)
		return i+1 ;
	else
		return std::string::npos;
}

tstring SStringRef::to_string() const
{
	return tstring(m_ptr, m_len);
}

const TCHAR &SStringRef::operator[](int index)const
{
	return at(index);
}
const TCHAR &SStringRef::at(int index)const
{
	return *(m_ptr + index);
}

bool SStringRef::operator==(SStringRef x)const
{
	if (this->m_ptr == x.m_ptr && this->m_len == x.m_len)return true;
	else return false;
}