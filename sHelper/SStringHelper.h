//������ʽת��,���,����,�и�,��ȡ��
//�����������ַ���ƴ��,
//�����ַ�������ת��
#include "../sCore/SString.h"
#include "../sCore/SStringList.h"
#ifndef SSTRINGHELPER_H
#define SSTRINGHELPER_H

namespace SStringHelper
{
	//�ַ�����ȡ
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
	//�ַ�����ȡ
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
		unsigned len = str.size() * 2;// Ԥ���ֽ���
		size_t converted = 0;
		setlocale(LC_CTYPE, "");     //������ô˺���
		wchar_t *p = new wchar_t[len];// ����һ���ڴ���ת������ַ���
		mbstowcs_s(&converted, p, len, str.c_str(), _TRUNCATE);// ת��
		std::wstring str1(p);
		delete[] p;// �ͷ�������ڴ�
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

