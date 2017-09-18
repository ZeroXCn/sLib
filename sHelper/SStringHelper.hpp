//������ʽת��,���,����,�и�,��ȡ��
//�����������ַ���ƴ��,
//�����ַ�������ת��
#include "../sCore/SString.h"
#include "../sCore/SStringList.h"
#include "../sCore/SRegex.h"
#ifndef SSTRINGHELPER_H
#define SSTRINGHELPER_H
#include <windows.h>
#include <time.h> 
#include <string>
namespace SStringHelper
{
	using namespace std;
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
			leftpos = org.find(left, leftpos, &leftmatchLength);
			if (leftpos != -1)
			{
				rightpos = org.find(right, leftpos + leftmatchLength, &rightmatchLength);
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

	SStringList SubString(SString org, tregex reg)
	{
		SStringList list;

		tsmatch what;
		tstring::const_iterator start = org.begin();
		tstring::const_iterator end = org.end();
		while (std::regex_search(start, end, what, reg))
		{
			list << what[0].str();
			start = what[0].second;
		}

		return list;
	}

	std::wstring StringToWstring(const std::string str)
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
	std::string WStringToString(const std::wstring str)
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


	/**
	*   @brief ��utf-8������ַ���ת��Ϊunicode������ַ�����
	*   @param[in] str	utf-8������ַ���
	*   @param[out] content	unicode������ַ���
	*   @retval true���ɹ���false��ʧ��
	*/
	bool Utf8ToUnicode(const char* str, wstring& content)
	{
		int textlen;
		wchar_t * result;
		textlen = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
		result = (wchar_t *)malloc((textlen + 1)*sizeof(wchar_t));
		::memset(result, 0, (textlen + 1)*sizeof(wchar_t));
		MultiByteToWideChar(CP_UTF8, 0, str, -1, (LPWSTR)result, textlen);

		content = result;
		free(result);

		return true;
	}

	/**
	*   @brief ��utf-8������ַ���ת��Ϊunicode������ַ�����
	*   @param[in] str	utf-8������ַ���
	*   @retval unicode������ַ���
	*   @note ���ʧ�ܣ�����""
	*/
	wstring Utf8ToUnicode(const char* str)
	{
		wstring temp;
		if (Utf8ToUnicode(str, temp))
		{
			return temp;
		}

		return L"";
	}


	/**
	*   @brief ��unicode������ַ���ת��Ϊansi������ַ�����
	*   @param[in] str	unicode������ַ���
	*   @param[out] content	ansi������ַ���
	*   @retval true���ɹ���false��ʧ��
	*/
	bool UnicodeToAscii(const wchar_t* str, string& content)
	{
		char* result;
		int textlen;
		textlen = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
		result = (char *)malloc((textlen + 1)*sizeof(char));
		memset(result, 0, sizeof(char)* (textlen + 1));
		WideCharToMultiByte(CP_ACP, 0, str, -1, result, textlen, NULL, NULL);

		content = result;
		free(result);

		return true;
	}

	/**
	*   @brief ��utf-8������ַ���ת��Ϊansi������ַ�����
	*   @param[in] str	utf-8������ַ���
	*   @retval ansi������ַ���
	*   @note ���ʧ�ܣ�����""
	*/
	string UnicodeToAscii(const wchar_t* str)
	{
		string temp;
		if (UnicodeToAscii(str, temp))
		{
			return temp;
		}

		return "";
	}

	/**
	*   @brief ��utf-8������ַ���ת��Ϊansi������ַ�����
	*   @param[in] str	utf-8������ַ���
	*   @param[out] content	ansi������ַ���
	*   @retval true���ɹ���false��ʧ��
	*/
	bool Utf8ToAscii(const char* str, string& content)
	{
		wstring temp;
		Utf8ToUnicode(str, temp);
		return UnicodeToAscii(temp.c_str(), content);
	}

	/**
	*   @brief ��utf-8������ַ���ת��Ϊansi������ַ�����
	*   @param[in] str	utf-8������ַ���
	*   @retval ansi������ַ���
	*   @note ���ʧ�ܣ�����""
	*/
	string Utf8ToAscii(const char* str)
	{
		string temp;
		if (Utf8ToAscii(str, temp))
		{
			return temp;
		}

		return "";
	}

	/**
	*   @brief ��ansi������ַ���ת��Ϊunicode������ַ�����
	*   @param[in] str	ansi������ַ���
	*   @param[out] content	unicode������ַ���
	*   @retval true���ɹ���false��ʧ��
	*/
	bool AsciiToUnicode(const char* str, wstring& content)
	{
		int textlen;
		wchar_t * result;
		textlen = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
		result = (wchar_t *)malloc((textlen + 1)*sizeof(wchar_t));
		::memset(result, 0, (textlen + 1)*sizeof(wchar_t));
		MultiByteToWideChar(CP_ACP, 0, str, -1, (LPWSTR)result, textlen);

		content = result;
		free(result);
		return true;
	}

	/**
	*   @brief ��ansi������ַ���ת��Ϊunicode������ַ�����
	*   @param[in] str	ansi������ַ���
	*   @retval unicode������ַ���
	*   @note ���ʧ�ܣ�����""
	*/
	wstring AsciiToUnicode(const char* str)
	{
		wstring temp;
		if (AsciiToUnicode(str, temp))
		{
			return temp;
		}

		return L"";
	}


	/**
	*   @brief ��unicode������ַ���ת��Ϊutf-8������ַ�����
	*   @param[in] str	unicode������ַ���
	*   @param[out] content	utf-8������ַ���
	*   @retval true���ɹ���false��ʧ��
	*/
	bool UnicodeToUtf8(const wchar_t* str, string& content)
	{
		char* result;
		int textlen;
		textlen = WideCharToMultiByte(CP_UTF8, 0, str, -1, NULL, 0, NULL, NULL);
		result = (char *)malloc((textlen + 1)*sizeof(char));
		memset(result, 0, sizeof(char)* (textlen + 1));
		WideCharToMultiByte(CP_UTF8, 0, str, -1, result, textlen, NULL, NULL);

		content = result;
		free(result);

		return true;
	}

	/**
	*   @brief ��unicode������ַ���ת��Ϊutf-8������ַ�����
	*   @param[in] str	ansi������ַ���
	*   @retval utf-8������ַ���
	*   @note ���ʧ�ܣ�����""
	*/
	string UnicodeToUtf8(const wchar_t* str)
	{
		string temp;
		if (UnicodeToUtf8(str, temp))
		{
			return temp;
		}

		return "";
	}


	/**
	*   @brief ��utf-8������ַ���ת��Ϊunicode������ַ�����
	*   @param[in] str	utf-8������ַ���
	*   @param[out] content	unicode������ַ���
	*   @retval true���ɹ���false��ʧ��
	*/
	bool AsciiToUtf8(const char* str, string& content)
	{
		wstring temp;
		AsciiToUnicode(str, temp);
		return UnicodeToUtf8(temp.c_str(), content);
	}

	/**
	*   @brief ��ansi������ַ���ת��Ϊutf-8������ַ�����
	*   @param[in] str	ansi������ַ���
	*   @retval utf-8������ַ���
	*   @note ���ʧ�ܣ�����""
	*/
	string AsciiToUtf8(const char* str)
	{
		string temp;
		if (AsciiToUtf8(str, temp))
		{
			return temp;
		}

		return "";
	}

};

#endif

