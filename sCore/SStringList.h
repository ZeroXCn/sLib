/**
*
*	SStringList类
*	增强型字符串数组处理类
*	@author ZeroX
*	@version v1.0 22/07/2017(22/07/2017)
*
*/
#include "SObject.h"
#include "SString.h"

#ifndef _SSTRINGLIST_H_
#define _SSTRINGLIST_H_
#include <iostream>
#include <vector>



class SStringList :
	public SObject,
	public std::vector<SString> 
{
	friend tostream& operator <<(tostream&, SStringList&);
	friend tistream& operator >>(tistream&, SStringList&);
public:
	SStringList();
	SStringList(char ch);
	SStringList(SString str);
	SStringList(const SStringList &strlist);
	SStringList(const std::vector<SString> &vec);

	//

	//TODO:交集与并集
	SStringList &operator &= (SStringList &stl);

	SStringList &operator |= (SStringList &stl);
	SStringList operator & (SStringList &stl);

	SStringList operator | (SStringList &stl);

	SStringList &operator -= (SStringList &stl);

	SStringList operator - (SStringList &stl);
	SStringList &operator += (SStringList &stl);
	SStringList operator + (SStringList &stl);

	SStringList &operator =(SStringList &strlist);
	bool operator == (SStringList &stl);

	///
	SStringList &operator &= (SString str);

	SStringList &operator |= (SString str);
	SStringList operator & (SString str);

	SStringList operator | (SString str);


	SStringList &operator += (SString str);

	SStringList operator + (SString str);

	SStringList &operator -= (SString str);

	SStringList operator - (SString str);


	SStringList &operator <<(SString str);

	SStringList &operator <<(SStringList &stl);


	int find(SString str, int start = 0);

	SStringList sublist(int start, int length = -1);

	SString &at(int index);
	SString at(int index, SString defaultstr);

	SStringList &distinct();

	SString toString();

};


typedef SStringList stringList;
typedef SStringList StringList;

#endif