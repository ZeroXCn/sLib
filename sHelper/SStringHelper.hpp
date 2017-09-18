//包括格式转换,拆分,查找,切割,截取等
//包括数字与字符串拼接,
//各种字符串类型转换
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
		unsigned len = str.size() * 2;// 预留字节数
		size_t converted = 0;
		setlocale(LC_CTYPE, "");     //必须调用此函数
		wchar_t *p = new wchar_t[len];// 申请一段内存存放转换后的字符串
		mbstowcs_s(&converted, p, len, str.c_str(), _TRUNCATE);// 转换
		std::wstring str1(p);
		delete[] p;// 释放申请的内存
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
	*   @brief 将utf-8编码的字符串转换为unicode编码的字符串。
	*   @param[in] str	utf-8编码的字符串
	*   @param[out] content	unicode编码的字符串
	*   @retval true：成功，false；失败
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
	*   @brief 将utf-8编码的字符串转换为unicode编码的字符串。
	*   @param[in] str	utf-8编码的字符串
	*   @retval unicode编码的字符串
	*   @note 如果失败，返回""
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
	*   @brief 将unicode编码的字符串转换为ansi编码的字符串。
	*   @param[in] str	unicode编码的字符串
	*   @param[out] content	ansi编码的字符串
	*   @retval true：成功，false；失败
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
	*   @brief 将utf-8编码的字符串转换为ansi编码的字符串。
	*   @param[in] str	utf-8编码的字符串
	*   @retval ansi编码的字符串
	*   @note 如果失败，返回""
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
	*   @brief 将utf-8编码的字符串转换为ansi编码的字符串。
	*   @param[in] str	utf-8编码的字符串
	*   @param[out] content	ansi编码的字符串
	*   @retval true：成功，false；失败
	*/
	bool Utf8ToAscii(const char* str, string& content)
	{
		wstring temp;
		Utf8ToUnicode(str, temp);
		return UnicodeToAscii(temp.c_str(), content);
	}

	/**
	*   @brief 将utf-8编码的字符串转换为ansi编码的字符串。
	*   @param[in] str	utf-8编码的字符串
	*   @retval ansi编码的字符串
	*   @note 如果失败，返回""
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
	*   @brief 将ansi编码的字符串转换为unicode编码的字符串。
	*   @param[in] str	ansi编码的字符串
	*   @param[out] content	unicode编码的字符串
	*   @retval true：成功，false；失败
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
	*   @brief 将ansi编码的字符串转换为unicode编码的字符串。
	*   @param[in] str	ansi编码的字符串
	*   @retval unicode编码的字符串
	*   @note 如果失败，返回""
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
	*   @brief 将unicode编码的字符串转换为utf-8编码的字符串。
	*   @param[in] str	unicode编码的字符串
	*   @param[out] content	utf-8编码的字符串
	*   @retval true：成功，false；失败
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
	*   @brief 将unicode编码的字符串转换为utf-8编码的字符串。
	*   @param[in] str	ansi编码的字符串
	*   @retval utf-8编码的字符串
	*   @note 如果失败，返回""
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
	*   @brief 将utf-8编码的字符串转换为unicode编码的字符串。
	*   @param[in] str	utf-8编码的字符串
	*   @param[out] content	unicode编码的字符串
	*   @retval true：成功，false；失败
	*/
	bool AsciiToUtf8(const char* str, string& content)
	{
		wstring temp;
		AsciiToUnicode(str, temp);
		return UnicodeToUtf8(temp.c_str(), content);
	}

	/**
	*   @brief 将ansi编码的字符串转换为utf-8编码的字符串。
	*   @param[in] str	ansi编码的字符串
	*   @retval utf-8编码的字符串
	*   @note 如果失败，返回""
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

