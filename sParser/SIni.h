/**
* SIni��
* ��ȡini�����ļ�
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
	/* �򿪲�����һ����Ϊfname��INI�ļ� */
	int Load(const std::string &fname);
	/*�����ݱ��浽��ǰ�ļ�*/
	int Save();
	/*��������浽һ����Ϊfname���ļ�*/
	int SaveAs(const std::string &fname);

	/*��ȡsection�ε�һ����Ϊkey��ֵ,��������std::string�͵�ֵ*/
	std::string GetStringValue(const std::string &section, const std::string &key, int &ret);
	/*��ȡsection�ε�һ����Ϊkey��ֵ,��������int�͵�ֵ*/
	int GetIntValue(const std::string &section, const std::string &key, int &ret);
	/*��ȡsection�ε�һ����Ϊkey��ֵ,��������double�͵�ֵ*/
	double GetDoubleValue(const std::string &section, const std::string &key, int &ret);

	/*��ȡsection�ε�һ����Ϊkey��ֵ,����ֵ����value��*/
	int GetValue(const std::string &section, const std::string &key, std::string &value);
	/*��ȡsection�ε�һ����Ϊkey��ֵ,����ֵ����value��,��ע�͸���comment��*/
	int GetValue(const std::string &section, const std::string &key, std::string &value, std::string &comment);

	/*��ȡsection�����м�Ϊkey��ֵ,����ֵ����values��std::vector��*/
	int GetValues(const std::string &section, const std::string &key, std::vector<std::string> &values);
	/*��ȡsection�����м�Ϊkey��ֵ,����ֵ����values��std::vector��,,��ע�͸���comments��std::vector��*/
	int GetValues(const std::string &section, const std::string &key, std::vector<std::string> &value, std::vector<std::string> &comments);

	bool HasSection(const std::string &section);
	bool HasKey(const std::string &section, const std::string &key);

	/* ��ȡsection�ε�ע�� */
	int GetSectionComment(const std::string &section, std::string &comment);
	/* ����section�ε�ע�� */
	int SetSectionComment(const std::string &section, const std::string &comment);
	/*��ȡע�ͱ�Ƿ��б�*/
	void GetCommentFlags(std::vector<std::string> &flags);
	/*����ע�ͱ�Ƿ��б�*/
	void SetCommentFlags(const std::vector<std::string> &flags);

	/*ͬʱ����ֵ��ע��*/
	int SetValue(const std::string &section, const std::string &key, const std::string &value, const std::string &comment = "");
	/*ɾ����*/
	void DeleteSection(const std::string &section);
	/*ɾ���ض��ε��ض�����*/
	void DeleteKey(const std::string &section, const std::string &key);
public:
	/*ȥ��str�����c�ַ�*/
	static void TrimLeft(std::string &str, char c = ' ');
	/*ȥ��strǰ���c�ַ�*/
	static void TrimRight(std::string &str, char c = ' ');
	/*ȥ��strǰ��ͺ���Ŀո��,Tab���ȿհ׷�*/
	static void Trim(std::string &str);
	/*���ַ���str���ָ��delim�ָ�ɶ���Ӵ�*/
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