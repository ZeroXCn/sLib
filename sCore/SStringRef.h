/**
*
*	SStringRef��
*	�ַ���������,�����κε��ڴ濽������
*	@author ZeroX
*	@version v1.0 10/08/2017
*
*/
#include "SObject.h"
#ifndef _SSTRINGREF_H_
#define _SSTRINGREF_H_
#include <string>
#include <tchar.h>
class SStringRef :public SObject
{
public:
	SStringRef();
	SStringRef(const TCHAR* str);
	SStringRef(const TCHAR* str,std::string::size_type len);
	SStringRef(const SStringRef &ref);

	SStringRef& operator=(const SStringRef &ref);
public:
	int size() const;
	int length() const;

	bool empty() const;

	const TCHAR &font()const;	//��
	const TCHAR &back()const;	//β
	const TCHAR *data()const;

	void clear();

	SStringRef substr(std::string::size_type pos, std::string::size_type n = std::string::npos);
	bool starts_with(TCHAR c) const;
	bool starts_with(SStringRef x) const;

	bool ends_with(TCHAR c) const;
	bool ends_with(SStringRef x) const;

	int equals(SStringRef x) const;//�Ƚ������Ƿ���ͬ
	int equals(SStringRef x, std::string::size_type len) const;

	int find(TCHAR c, std::string::size_type pos=0)const;
	int find(SStringRef x, std::string::size_type pos = 0)const;
	int find_first_of(TCHAR c)const;
	int find_first_of(SStringRef x)const;
	int find_last_of(TCHAR c)const;
	int find_last_of(SStringRef x)const;

	tstring to_string() const;
public:
	const TCHAR &operator[](int index)const;
	const TCHAR &at(int index)const;

	bool operator==(SStringRef x)const;	//ֻ�Ƚϵ�ַ�Ƿ���ͬ

private:
	const TCHAR *m_ptr;		//�ַ���ָ��
	size_t m_len;			//�ַ�������
};

#endif