/**
*
*	SStringBuilder类
*	字符串处理类
*	@author keke8634
*	@version v1.0 2008-11-21
*
*/
#include "SObject.h"

#ifndef _SSTRINGBUILDER_H_
#define _SSTRINGBUILDER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <tchar.h>

class SStringBuilder :public SObject
{
	//变长后需要重新分配空间,可用new(),realloc(),melloc()
public:
	TCHAR *a;
	int strlength;

public:
	SStringBuilder();
	SStringBuilder(const TCHAR *strbuf);
	SStringBuilder(const TCHAR *bytes, int offset, int length);
	SStringBuilder(const SStringBuilder& str);
	~SStringBuilder();

public:
	int length() const;
	void append(const TCHAR* strbuf);
	void append(const TCHAR ch);
	void insert(int index, const TCHAR *strbuf);
	void insert(int index, const TCHAR ch);

	int equals(const TCHAR *strbuf);
	int equals(const SStringBuilder& str);

	int isNull();
	int isEmpty();
	TCHAR charAt(int index);
	int indexOf(TCHAR ch);
	int indexOf(TCHAR ch, int fromIndex);
	int lastIndexOf(TCHAR ch);
	int lastIndexOf(int ch, int fromIndex);

	SStringBuilder copy(const TCHAR* str);//把自己拷贝一份
	SStringBuilder substring(int beginIndex);
	SStringBuilder substring(int beginIndex, int endIndex);
	SStringBuilder toLowerCase();
	SStringBuilder toUpperCase();

	void trim();//去掉了所有的空格
	void trimLeft();
	void trimRight();
	void mergeSpace();

	int startsWith(const SStringBuilder& prefix);//原参数为SStringBuilder &prefix
	int endsWith(const SStringBuilder& suffix);//原参数为SStringBuilder &suffix

	void remove(TCHAR *str);

	void replaceAll(char oldChar, char newChar);
	void replaceAll(SStringBuilder oldsubString, SStringBuilder newsubString);
	void replaceFirst(SStringBuilder oldsubString, SStringBuilder newsubString);

	int parseInt(int base);//实现转换为十进制,10 or 16, 2//?
	double parseFloat();

	const SStringBuilder& operator=(const SStringBuilder& str);
	const SStringBuilder& operator=(const TCHAR *strbuf);
	SStringBuilder operator+(const SStringBuilder& str);
	SStringBuilder operator+(const TCHAR *strbuf);
	const SStringBuilder& operator+=(const SStringBuilder& str);//与operator+一样?
	const SStringBuilder& operator+=(const TCHAR *strbuf);
	int operator==(const SStringBuilder& str);
	int operator==(const TCHAR *strbuf);
	int operator!=(const SStringBuilder& str);
	int operator!=(const TCHAR *strbuf);

	friend SStringBuilder operator +(const SStringBuilder& str1, const SStringBuilder& str2);
	/*
	SStringBuilder operator +(const SStringBuilder& str, const TCHAR *strbuf);
	SStringBuilder operator +(const TCHAR *strbuf, const SStringBuilder& str);
	*/
};
#endif