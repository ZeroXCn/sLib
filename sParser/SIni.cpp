#include "SIni.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

using namespace std;

int INI_BUF_SIZE = 2048;

SIniDocument::SIniDocument()
{
	flags_.push_back("#");
	flags_.push_back(";");
}

bool SIniDocument::Parse(const string &content, string &key, string &value, char c/*= '='*/)
{
	int i = 0;
	int len = content.length();

	while (i < len && content[i] != c) {
		++i;
	}

	if (i >= 0 && i < len) {
		key = string(content.c_str(), i);
		value = string(content.c_str() + i + 1, len - i - 1);
		return true;
	}

	return false;
}

int SIniDocument::GetLine(string &str, FILE *fp)
{
	int plen = 0;
	int buf_size = INI_BUF_SIZE * sizeof(char);

	char *buf = (char *)malloc(buf_size);
	char *pbuf = NULL;
	char *p = buf;

	if (buf == NULL) {
		fprintf(stderr, "no enough memory!exit!\n");
		exit(-1);
	}

	memset(buf, 0, buf_size);
	int total_size = buf_size;

	while (fgets(p, buf_size, fp) != NULL) {
		plen = strlen(p);

		if (plen > 0 && p[plen - 1] != '\n' && !feof(fp)) {

			total_size = strlen(buf) + buf_size;
			pbuf = (char *)realloc(buf, total_size);

			if (pbuf == NULL) {
				free(buf);
				fprintf(stderr, "no enough memory!exit!\n");
				exit(-1);
			}

			buf = pbuf;

			p = buf + strlen(buf);

			continue;
		}
		else {
			break;
		}
	}

	str = buf;

	free(buf);
	buf = NULL;
	return str.length();

}
int SIniDocument::Load(const string &filename)
{
	Release();
	fname_ = filename;
	SIniSection *section = NULL;
	errno_t err; FILE *fp;
	err = fopen_s(&fp, filename.c_str(), "r");

	if (fp == NULL) {
		return -1;
	}

	string line;
	string comment;

	//增加默认段
	section = new SIniSection();
	sections_[""] = section;

	while (GetLine(line, fp) > 0) {

		TrimRight(line, '\n');
		TrimRight(line, '\r');
		Trim(line);

		if (!IsComment(line)) {
			/* 针对 “value=1 #测试” 这种后面有注释的语句
			* 重新分割line，并添加注释到commnet
			* 注意：这种情况保存后会变成
			* #测试
			* value=1
			* */
			string subline;
			string tmp = line;

			for (size_t i = 0; i < flags_.size(); ++i) {
				subline = line.substr(0, line.find(flags_[i]));
				line = subline;
			}

			comment += tmp.substr(line.length());
		}

		Trim(line);

		if (line.length() <= 0) {
			continue;
		}

		if (line[0] == '[') {
			section = NULL;
			int index = line.find_first_of(']');

			if (index == -1) {
				fclose(fp);
				fprintf(stderr, "没有找到匹配的]\n");
				return -1;
			}

			int len = index - 1;

			if (len <= 0) {
				fprintf(stderr, "段为空\n");
				continue;
			}

			string s(line, 1, len);

			if (GetSection(s.c_str()) != NULL) {
				fclose(fp);
				fprintf(stderr, "此段已存在:%s\n", s.c_str());
				return -1;
			}

			section = new SIniSection();
			sections_[s] = section;

			section->name = s;
			section->comment = comment;
			comment = "";
		}
		else if (IsComment(line)) {
			if (comment != "") {
				comment += SIni::delim + line;
			}
			else {
				comment = line;
			}
		}
		else {
			string key, value;

			if (Parse(line, key, value)) {
				SIniItem item;
				item.key = key;
				item.value = value;
				item.comment = comment;

				section->items.push_back(item);
			}
			else {
				fprintf(stderr, "解析参数失败[%s]\n", line.c_str());
			}

			comment = "";
		}
	}

	fclose(fp);

	return 0;
}

int SIniDocument::Save()
{
	return SaveAs(fname_);
}

int SIniDocument::SaveAs(const string &filename)
{
	string data = "";

	for (iterator sect = sections_.begin(); sect != sections_.end(); ++sect) {
		if (sect->second->comment != "") {
			data += sect->second->comment;
			data += SIni::delim;
		}

		if (sect->first != "") {
			data += string("[") + sect->first + string("]");
			data += SIni::delim;
		}

		for (SIniSection::iterator item = sect->second->items.begin(); item != sect->second->items.end(); ++item) {
			if (item->comment != "") {
				data += item->comment;
				data += SIni::delim;
			}

			data += item->key + "=" + item->value;
			data += SIni::delim;
		}
	}
	errno_t err; FILE *fp;
	err = fopen_s(&fp, filename.c_str(), "w");

	fwrite(data.c_str(), 1, data.length(), fp);

	fclose(fp);

	return 0;
}
SIniSection *SIniDocument::GetSection(const string &section /*=""*/)
{
	iterator it = sections_.find(section);

	if (it != sections_.end()) {
		return it->second;
	}

	return NULL;
}

string SIniDocument::GetStringValue(const string &section, const string &key, int &ret)
{
	string value, comment;

	ret = GetValue(section, key, value, comment);

	return value;
}

int SIniDocument::GetIntValue(const string &section, const string &key, int &ret)
{
	string value, comment;

	ret = GetValue(section, key, value, comment);

	return atoi(value.c_str());
}

double SIniDocument::GetDoubleValue(const string &section, const string &key, int &ret)
{
	string value, comment;

	ret = GetValue(section, key, value, comment);

	return atof(value.c_str());

}

int SIniDocument::GetValue(const string &section, const string &key, string &value)
{
	string comment;
	return GetValue(section, key, value, comment);
}
int SIniDocument::GetValue(const string &section, const string &key, string &value, string &comment)
{
	SIniSection *sect = GetSection(section);

	if (sect != NULL) {
		for (SIniSection::iterator it = sect->begin(); it != sect->end(); ++it) {
			if (it->key == key) {
				value = it->value;
				comment = it->comment;
				return SIni::RET_OK;
			}
		}
	}

	return SIni::RET_ERR;
}
int SIniDocument::GetValues(const string &section, const string &key, vector<string> &values)
{
	vector<string> comments;
	return GetValues(section, key, values, comments);
}
int SIniDocument::GetValues(const string &section, const string &key,
	vector<string> &values, vector<string> &comments)
{
	string value, comment;

	values.clear();
	comments.clear();

	SIniSection *sect = GetSection(section);

	if (sect != NULL) {
		for (SIniSection::iterator it = sect->begin(); it != sect->end(); ++it) {
			if (it->key == key) {
				value = it->value;
				comment = it->comment;

				values.push_back(value);
				comments.push_back(comment);
			}
		}
	}

	return (values.size() ? SIni::RET_OK : SIni::RET_ERR);

}
bool SIniDocument::HasSection(const string &section)
{
	return (GetSection(section) != NULL);

}

bool SIniDocument::HasKey(const string &section, const string &key)
{
	SIniSection *sect = GetSection(section);

	if (sect != NULL) {
		for (SIniSection::iterator it = sect->begin(); it != sect->end(); ++it) {
			if (it->key == key) {
				return true;
			}
		}
	}

	return false;
}
int SIniDocument::GetSectionComment(const string &section, string &comment)
{
	comment = "";
	SIniSection *sect = GetSection(section);

	if (sect != NULL) {
		comment = sect->comment;
		return SIni::RET_OK;
	}

	return SIni::RET_ERR;
}
int SIniDocument::SetSectionComment(const string &section, const string &comment)
{
	SIniSection *sect = GetSection(section);

	if (sect != NULL) {
		sect->comment = comment;
		return SIni::RET_OK;
	}

	return SIni::RET_ERR;
}

int SIniDocument::SetValue(const string &section, const string &key,
	const string &value, const string &comment /*=""*/)
{
	SIniSection *sect = GetSection(section);

	string comt = comment;

	if (comt != "") {
		comt = flags_[0] + comt;
	}

	if (sect == NULL) {
		sect = new SIniSection();

		if (sect == NULL) {
			fprintf(stderr, "no enough memory!\n");
			exit(-1);
		}

		sect->name = section;
		sections_[section] = sect;
	}

	for (SIniSection::iterator it = sect->begin(); it != sect->end(); ++it) {
		if (it->key == key) {
			it->value = value;
			it->comment = comt;
			return SIni::RET_OK;
		}
	}

	//not found key
	SIniItem item;
	item.key = key;
	item.value = value;
	item.comment = comt;

	sect->items.push_back(item);

	return SIni::RET_OK;

}
void SIniDocument::GetCommentFlags(vector<string> &flags)
{
	flags = flags_;
}
void SIniDocument::SetCommentFlags(const vector<string> &flags)
{
	flags_ = flags;
}
void SIniDocument::DeleteSection(const string &section)
{
	SIniSection *sect = GetSection(section);

	if (sect != NULL) {

		sections_.erase(section);
		delete sect;
	}
}
void SIniDocument::DeleteKey(const string &section, const string &key)
{
	SIniSection *sect = GetSection(section);

	if (sect != NULL) {
		for (SIniSection::iterator it = sect->begin(); it != sect->end(); ++it) {
			if (it->key == key) {
				sect->items.erase(it);
				break;
			}
		}
	}

}

void SIniDocument::Release()
{
	fname_ = "";

	for (iterator i = sections_.begin(); i != sections_.end(); ++i) {
		delete i->second;
	}

	sections_.clear();

}

bool SIniDocument::IsComment(const string &str)
{
	bool ret = false;

	for (size_t i = 0; i < flags_.size(); ++i) {
		size_t k = 0;

		if (str.length() < flags_[i].length()) {
			continue;
		}

		for (k = 0; k < flags_[i].length(); ++k) {
			if (str[k] != flags_[i][k]) {
				break;
			}
		}

		if (k == flags_[i].length()) {
			ret = true;
			break;
		}
	}

	return ret;
}
//for debug
void SIniDocument::Print()
{
	printf("filename:[%s]\n", fname_.c_str());

	printf("flags_:[");

	for (size_t i = 0; i < flags_.size(); ++i) {
		printf(" %s ", flags_[i].c_str());
	}

	printf("]\n");

	for (iterator it = sections_.begin(); it != sections_.end(); ++it) {
		printf("section:[%s]\n", it->first.c_str());
		printf("comment:[%s]\n", it->second->comment.c_str());

		for (SIniSection::iterator i = it->second->items.begin(); i != it->second->items.end(); ++i) {
			printf("    comment:%s\n", i->comment.c_str());
			printf("    parm   :%s=%s\n", i->key.c_str(), i->value.c_str());
		}
	}
}

void SIniDocument::TrimLeft(string &str, char c/*=' '*/)
{
	//trim head

	int len = str.length();

	int i = 0;

	while (str[i] == c && str[i] != '\0') {
		i++;
	}

	if (i != 0) {
		str = string(str, i, len - i);
	}
}

void SIniDocument::TrimRight(string &str, char c/*=' '*/)
{
	//trim tail
	int i = 0;
	int len = str.length();


	for (i = len - 1; i >= 0; --i) {
		if (str[i] != c) {
			break;
		}
	}

	str = string(str, 0, i + 1);
}

void SIniDocument::Trim(string &str)
{
	//trim head

	int len = str.length();

	int i = 0;

	while (isspace(str[i]) && str[i] != '\0') {
		i++;
	}

	if (i != 0) {
		str = string(str, i, len - i);
	}

	//trim tail
	len = str.length();

	for (i = len - 1; i >= 0; --i) {
		if (!isspace(str[i])) {
			break;
		}
	}

	str = string(str, 0, i + 1);
}
