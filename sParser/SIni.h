/**
* SIni类
* 读取ini配置文件
* @author Winnerhust
* @link https://github.com/Winnerhust/inifile2
* @version v2.0 02/11/2015(2014-08-15)
*/
#include "../sCore/SObject.h"

#ifndef _SINI_H_
#define _SINI_H_
#include <map>
#include <vector>
#include <string>
#include <string.h>
namespace SIni{
	const int RET_OK = 0;
	const int RET_ERR = -1;
	const std::string delim = "\n";
}
struct SIniItem {
	std::string key;
	std::string value;
	std::string comment;
};
struct SIniSection {
	typedef std::vector<SIniItem>::iterator iterator;
	iterator begin() {
		return items.begin();
	}
	iterator end() {
		return items.end();
	}

	std::string name;
	std::string comment;
	std::vector<SIniItem> items;
};

class SIniDocument
{
public:
	SIniDocument();
	~SIniDocument() {
		Release();
	}

public:
	typedef std::map<std::string, SIniSection *>::iterator iterator;

	iterator begin() {
		return sections_.begin();
	}
	iterator end() {
		return sections_.end();
	}
public:
	/* 打开并解析一个名为fname的INI文件 */
	int Load(const std::string &fname);
	/*将内容保存到当前文件*/
	int Save();
	/*将内容另存到一个名为fname的文件*/
	int SaveAs(const std::string &fname);

	/*获取section段第一个键为key的值,并返回其std::string型的值*/
	std::string GetStringValue(const std::string &section, const std::string &key, int &ret);
	/*获取section段第一个键为key的值,并返回其int型的值*/
	int GetIntValue(const std::string &section, const std::string &key, int &ret);
	/*获取section段第一个键为key的值,并返回其double型的值*/
	double GetDoubleValue(const std::string &section, const std::string &key, int &ret);

	/*获取section段第一个键为key的值,并将值赋到value中*/
	int GetValue(const std::string &section, const std::string &key, std::string &value);
	/*获取section段第一个键为key的值,并将值赋到value中,将注释赋到comment中*/
	int GetValue(const std::string &section, const std::string &key, std::string &value, std::string &comment);

	/*获取section段所有键为key的值,并将值赋到values的std::vector中*/
	int GetValues(const std::string &section, const std::string &key, std::vector<std::string> &values);
	/*获取section段所有键为key的值,并将值赋到values的std::vector中,,将注释赋到comments的std::vector中*/
	int GetValues(const std::string &section, const std::string &key, std::vector<std::string> &value, std::vector<std::string> &comments);

	bool HasSection(const std::string &section);
	bool HasKey(const std::string &section, const std::string &key);

	/* 获取section段的注释 */
	int GetSectionComment(const std::string &section, std::string &comment);
	/* 设置section段的注释 */
	int SetSectionComment(const std::string &section, const std::string &comment);
	/*获取注释标记符列表*/
	void GetCommentFlags(std::vector<std::string> &flags);
	/*设置注释标记符列表*/
	void SetCommentFlags(const std::vector<std::string> &flags);

	/*同时设置值和注释*/
	int SetValue(const std::string &section, const std::string &key, const std::string &value, const std::string &comment = "");
	/*删除段*/
	void DeleteSection(const std::string &section);
	/*删除特定段的特定参数*/
	void DeleteKey(const std::string &section, const std::string &key);
public:
	/*去掉str后面的c字符*/
	static void TrimLeft(std::string &str, char c = ' ');
	/*去掉str前面的c字符*/
	static void TrimRight(std::string &str, char c = ' ');
	/*去掉str前面和后面的空格符,Tab符等空白符*/
	static void Trim(std::string &str);
	/*将字符串str按分割符delim分割成多个子串*/
private:
	SIniSection *GetSection(const std::string &section = "");
	void Release();
	int GetLine(std::string &str, FILE *fp);
	bool IsComment(const std::string &str);
	bool Parse(const std::string &content, std::string &key, std::string &value, char c = '=');
	//for dubug
	void Print();

private:
	std::map<std::string, SIniSection *> sections_;
	std::string fname_;
	std::vector<std::string> flags_;
};



#endif