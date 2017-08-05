//包括格式转换,拆分,查找,切割,截取等
//包括数字与字符串拼接,
//各种字符串类型转换
#include "../sCore/SString.h"
#include "../sCore/SStringList.h"
#ifndef SSTRINGHELPER_H
#define SSTRINGHELPER_H

namespace SStringHelper
{
	//字符串截取
	SStringList SubString(SString org, SString left, SString right)
	{
		SStringList list;
		int leftpos = 0, rightpos = 0;
		while (1)
		{
			if (left.empty())
				leftpos = leftpos;
			else
				leftpos = org.find_first_of(left, leftpos);

			if (leftpos != -1)
			{
				if (right.empty())
					rightpos = org.size();
				else
					rightpos = org.find_first_of(right, leftpos + left.size());

				if (rightpos != -1){
					list << org.substr(leftpos + left.size(), rightpos - leftpos - left.size());
					leftpos = rightpos + right.size();
				}
				else break;
			}
			else break;
		}
		return list;
	}
	//字符串截取
	SStringList SubString(SString org, tregex left, tregex right)
	{
		SStringList list;

		int leftpos = 0, rightpos = 0;
		int leftmatchLength, rightmatchLength;
		while (1)
		{
			leftpos = org.indexOf(left, leftpos, &leftmatchLength);
			if (leftpos != -1)
			{
				rightpos = org.indexOf(right, leftpos + leftmatchLength, &rightmatchLength);
				if (rightpos != -1){
					list << org.substr(leftpos + leftmatchLength, rightpos - leftpos - leftmatchLength);
					leftpos = rightpos + rightmatchLength;
				}
				else break;
			}
			else break;
		}
		return list;
	}

	static wstring StringToWstring(const string str)
	{
		unsigned len = str.size() * 2;// 预留字节数
		size_t converted = 0;
		setlocale(LC_CTYPE, "");     //必须调用此函数
		wchar_t *p = new wchar_t[len];// 申请一段内存存放转换后的字符串
		mbstowcs_s(&converted, p, len, str.c_str(), _TRUNCATE);// 转换
		std::wstring str1(p);
		delete[] p;// 释放申请的内存
		return str1;
	}
	static string WStringToString(const wstring str)
	{
		unsigned len = str.size() * 4;
		size_t converted = 0;
		setlocale(LC_CTYPE, "");
		char *p = new char[len];
		wcstombs_s(&converted, p, len, str.c_str(), _TRUNCATE);
		std::string str1(p);
		delete[] p;
		return str1;
	}

};

#endif

