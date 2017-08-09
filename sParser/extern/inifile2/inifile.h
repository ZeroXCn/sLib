#ifndef _INIFILE_H
#define _INIFILE_H

#include <map>
#include <vector>
#include <string>
#include <string.h>

namespace inifile
{
	const int RET_OK = 0;
	const int RET_ERR = -1;
	const std::string delim = "\n";
	struct IniItem {
		std::string key;
		std::string value;
		std::string comment;
	};
	struct IniSection {
		typedef std::vector<IniItem>::iterator iterator;
		iterator begin() {
			return items.begin();
		}
		iterator end() {
			return items.end();
		}

		std::string name;
		std::string comment;
		std::vector<IniItem> items;
	};

	class IniFile
	{
	public:
		IniFile();
		~IniFile() {
			release();
		}

	public:
		typedef std::map<std::string, IniSection *>::iterator iterator;

		iterator begin() {
			return sections_.begin();
		}
		iterator end() {
			return sections_.end();
		}
	public:
		/* �򿪲�����һ����Ϊfname��INI�ļ� */
		int load(const std::string &fname);
		/*�����ݱ��浽��ǰ�ļ�*/
		int save();
		/*��������浽һ����Ϊfname���ļ�*/
		int saveas(const std::string &fname);

		/*��ȡsection�ε�һ����Ϊkey��ֵ,��������std::string�͵�ֵ*/
		std::string getStringValue(const std::string &section, const std::string &key, int &ret);
		/*��ȡsection�ε�һ����Ϊkey��ֵ,��������int�͵�ֵ*/
		int getIntValue(const std::string &section, const std::string &key, int &ret);
		/*��ȡsection�ε�һ����Ϊkey��ֵ,��������double�͵�ֵ*/
		double getDoubleValue(const std::string &section, const std::string &key, int &ret);

		/*��ȡsection�ε�һ����Ϊkey��ֵ,����ֵ����value��*/
		int getValue(const std::string &section, const std::string &key, std::string &value);
		/*��ȡsection�ε�һ����Ϊkey��ֵ,����ֵ����value��,��ע�͸���comment��*/
		int getValue(const std::string &section, const std::string &key, std::string &value, std::string &comment);

		/*��ȡsection�����м�Ϊkey��ֵ,����ֵ����values��std::vector��*/
		int getValues(const std::string &section, const std::string &key, std::vector<std::string> &values);
		/*��ȡsection�����м�Ϊkey��ֵ,����ֵ����values��std::vector��,,��ע�͸���comments��std::vector��*/
		int getValues(const std::string &section, const std::string &key, std::vector<std::string> &value, std::vector<std::string> &comments);

		bool hasSection(const std::string &section);
		bool hasKey(const std::string &section, const std::string &key);

		/* ��ȡsection�ε�ע�� */
		int getSectionComment(const std::string &section, std::string &comment);
		/* ����section�ε�ע�� */
		int setSectionComment(const std::string &section, const std::string &comment);
		/*��ȡע�ͱ�Ƿ��б�*/
		void getCommentFlags(std::vector<std::string> &flags);
		/*����ע�ͱ�Ƿ��б�*/
		void setCommentFlags(const std::vector<std::string> &flags);

		/*ͬʱ����ֵ��ע��*/
		int setValue(const std::string &section, const std::string &key, const std::string &value, const std::string &comment = "");
		/*ɾ����*/
		void deleteSection(const std::string &section);
		/*ɾ���ض��ε��ض�����*/
		void deleteKey(const std::string &section, const std::string &key);
	public:
		/*ȥ��str�����c�ַ�*/
		static void trimleft(std::string &str, char c = ' ');
		/*ȥ��strǰ���c�ַ�*/
		static void trimright(std::string &str, char c = ' ');
		/*ȥ��strǰ��ͺ���Ŀո��,Tab���ȿհ׷�*/
		static void trim(std::string &str);
		/*���ַ���str���ָ��delim�ָ�ɶ���Ӵ�*/
	private:
		IniSection *getSection(const std::string &section = "");
		void release();
		int getline(std::string &str, FILE *fp);
		bool isComment(const std::string &str);
		bool parse(const std::string &content, std::string &key, std::string &value, char c = '=');
		//for dubug
		void print();

	private:
		std::map<std::string, IniSection *> sections_;
		std::string fname_;
		std::vector<std::string> flags_;
	};
}

#endif
