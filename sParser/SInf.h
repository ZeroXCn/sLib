/**
* SInf类
* inf文件读写操作
* @author ZeroX
* @version v1.1 03/08/2017(12/11/2016)
*/
#include "../sCore/SObject.h"
#include "../sCore/SString.h"

#ifndef _SINF_H_
#define _SINF_H_
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

class SInf:public SObject
{

};



class InFWriter{
protected:
	string m_filePath;
public:
	class Section{
	protected:
		friend class InFWriter;
		string m_strSection;
	public:
		Section();
		Section(string strSection);
		void AddItem(string key, string value = "");
		void Clean();
	};
public:
	void NewFile(string content = "");
	bool Exist();
	static bool Exist(string filePath);

	//	void WriteSection(Section a);
	//	void AddSection(Section a);
	void Write(string Content);
	void Write(Section a);
	void Add(string Content);
	void Add(Section a);
	void Append(Section a);
	void AddLine(string Content = "");
public:
	InFWriter(string filePath);
};

InFWriter::Section::Section()
{

}

InFWriter::Section::Section(string strSection)
{
	m_strSection = "[" + strSection + "]" + "\r\n";
}

void InFWriter::Section::AddItem(string key, string value)
{
	m_strSection += key + "=" + value + "\r\n";
}
void InFWriter::Section::Clean()
{
	m_strSection = "";
}

////////////
InFWriter::InFWriter(string filePath)
{
	m_filePath = filePath;
}


void InFWriter::NewFile(string content)
{
	ofstream out(m_filePath.c_str(), ios::ate);
	out << content.c_str();
}
bool InFWriter::Exist()
{
	fstream file(m_filePath.c_str());
	if (!file)return false;
	else return true;
}
bool InFWriter::Exist(string filePath)
{
	fstream file(filePath.c_str());
	if (!file)return false;
	else return true;
}
void InFWriter::Write(string Content)
{
	//有则覆,没有创建覆盖
	ofstream out(m_filePath.c_str(), ios::ate);
	out << Content.c_str();
}
void InFWriter::Add(string Content)
{
	ofstream out(m_filePath.c_str(), ios::app);
	out << Content.c_str();
}
void InFWriter::AddLine(string Content)
{
	ofstream out(m_filePath.c_str(), ios::app);
	out << Content.c_str() << "\r\n";
}
void InFWriter::Write(Section a)
{
	ofstream out(m_filePath.c_str(), ios::ate);
	out << a.m_strSection.c_str();
}

void InFWriter::Add(Section a)
{
	ofstream out(m_filePath.c_str(), ios::app);
	out << a.m_strSection.c_str();
}

void InFWriter::Append(Section a)
{
	ofstream out(m_filePath.c_str(), ios::app);
	out << a.m_strSection.c_str();
}















/////////////////////////////////////////////////////






class InfReader
{
protected:
	friend class DSLItem;
	friend class DSLArray;
	friend class ItemInfo;
protected:
	string m_filePath;
public:

	class DSLArray
	{
	public:
		friend class InfReader;
		friend class ItemInfo;
		friend class DSLItem;
	public:
		class DSLItem
		{
		protected:
			friend class InfReader;
			friend class ItemInfo;
			friend class DSLArray;
		protected:
			map<string, string>	m_mItem;
		protected:
			void Put(string key, string value);
			DSLItem();
			DSLItem(string key, string value);
		public:
			string GetValue(string key, string defaultValue = "");
		};

	private:
		class ItemInfo
		{
		public:
			string m_strSection;
			DSLItem	*m_pItem;

			ItemInfo();
			ItemInfo(string section, DSLItem *pItem);

		};
	protected:
		vector<ItemInfo> m_vecItemInfoArray;
	protected:
		void Add(string section, DSLItem *pItem);
	public:
		DSLArray();
		int Size();
		DSLItem *GetSection(string section);
		DSLItem *Get(int index);
	};

protected:
	bool CheckIgnoreContent(string strLine);
public:
	static bool Exist(string filePath);
	static string GetFileContent(string FilePath);
	DSLArray *GetDSLArray(string strContent);
public:
	InfReader(string filePath);

};

InfReader::InfReader(string filePath)
{
	m_filePath = filePath;
}

bool InfReader::Exist(string filePath)
{
	fstream file(filePath.c_str());
	if (!file)return false;
	else return true;
}

string InfReader::GetFileContent(string FilePath)
{
	string result = "";
	ifstream in(FilePath.c_str());
	if (!in)
	{
		cout << "Can't open file" << endl;
		return "";
	}
	else
	{
		char buffer[1024]; int n = -1;
		while (!in.eof())
		{
			in.read(buffer, 1024);
			n = in.gcount();
			result += string(buffer, n);
		}

	}
	return result;
}

bool InfReader::CheckIgnoreContent(string strLine)
{

	if (strLine.size() >= 2 && strLine.at(0) == '/' && (strLine.at(1) == '/' || strLine.at(1) == '*'))return true;
	return false;

}

InfReader::DSLArray *InfReader::GetDSLArray(string strContent)
{
	InfReader::DSLArray *temp = new InfReader::DSLArray();
	const int bufferSize = 1024;	//定义缓冲区大小
	char buffer[bufferSize];
	istringstream in(strContent);


	/*
	while(getline(in,str))
	cout<<str<<endl;
	*/
	bool isNewSection = false;	//是否遇到新结点的标志
	while (!in.eof())
	{
		string strLine = ""; int n = -1;
		//这里姑且认为一行不超过1024字节,否则错误
		in.getline(buffer, 1024);		//读取的时候会把最后的回车也读取
		n = in.gcount();

		if (n >= 2)strLine = string(buffer, n - 2);	//如果包含回车

		//if(CheckIgnoreContent(strLine))continue;

		//如果之前没遇到新结点
		if (isNewSection == false)
		{
			//寻找结点
			if (strLine.empty())continue;
			//			if(CheckIgnoreContent(strLine))continue;	//如果是欲忽略的字符串则跳过

			if (strLine.at(0) == '[' && strLine.at(strLine.size() - 1) == ']')
			{
				isNewSection = true;
				InfReader::DSLArray::DSLItem *newSection = new InfReader::DSLArray::DSLItem();
				string sectionName = strLine.substr(1, strLine.size() - 2);
				temp->Add(sectionName, newSection);

				continue;	//返回读取下一行

			}
		}
		else
		{
			//寻找项
			//若不是空的时候
			if (!strLine.empty())
			{
				if (strLine.at(0) == '[' && strLine.at(strLine.size() - 1) == ']')
				{
					isNewSection = true;
					InfReader::DSLArray::DSLItem *newSection = new InfReader::DSLArray::DSLItem();
					string sectionName = strLine.substr(1, strLine.size() - 1);
					temp->Add(sectionName, newSection);

					continue;	//返回读取下一行
				}
				else{
					int startPos = -1;
					startPos = strLine.find_first_of('=');
					if (startPos >= 0)
					{
						string key = strLine.substr(0, startPos);
						string value = strLine.substr(startPos + 1);
						temp->m_vecItemInfoArray.at(temp->m_vecItemInfoArray.size() - 1).m_pItem->Put(key, value);
					}
				}

			}
			else	//否则代表此次Section结束
			{
				isNewSection = false;
			}

		}
	}
	/*
	if(temp->m_vecItemInfoArray.size()<=0)
	{
	delete temp;
	return NULL;
	}
	else */
	return temp;
}
InfReader::DSLArray::DSLArray()
{

}

InfReader::DSLArray::ItemInfo::ItemInfo()
{
}

InfReader::DSLArray::ItemInfo::ItemInfo(string section, DSLItem *pItem)
{
	m_strSection = section;
	m_pItem = pItem;
}


void InfReader::DSLArray::Add(string section, DSLItem *pItem)
{
	ItemInfo temp;
	temp.m_pItem = pItem;
	temp.m_strSection = section;
	m_vecItemInfoArray.push_back(temp);
}

InfReader::DSLArray::DSLItem *InfReader::DSLArray::Get(int index)
{
	if (index<0 || index >= m_vecItemInfoArray.size())return NULL;
	else return m_vecItemInfoArray.at(index).m_pItem;

}

InfReader::DSLArray::DSLItem *InfReader::DSLArray::GetSection(string section)
{
	vector<ItemInfo>::iterator it = m_vecItemInfoArray.begin();
	for (; it != m_vecItemInfoArray.end(); it++){
		if ((*it).m_strSection == section){
			return (*it).m_pItem;
		}
	}
	return NULL;
}

int InfReader::DSLArray::Size()
{
	return m_vecItemInfoArray.size();
}

InfReader::DSLArray::DSLItem::DSLItem()
{

}

InfReader::DSLArray::DSLItem::DSLItem(string key, string value)
{
	Put(key, value);
}
void InfReader::DSLArray::DSLItem::Put(string key, string value)
{
	m_mItem.insert(make_pair(key, value));
}

string InfReader::DSLArray::DSLItem::GetValue(string key, string defaultValue)
{
	map<string, string>::iterator it;
	it = m_mItem.find(key);
	if (it != m_mItem.end()) return (*it).second;
	else return defaultValue;
}


//void main()
//{
//	/*
//	InFWriter t("D:\\ert.txt");
//	InFWriter::Section s1("nihao");
//	s1.AddItem("gg","423");
//	s1.AddItem("ff","eqw");
//	t.Append(s1);
//	*/
//
//	InfReader j("D:\\ert.txt");
//	string content = InfReader::GetFileContent("D:\\ert.txt");
//	InfReader::DSLArray *i = j.GetDSLArray(content);
//	InfReader::DSLArray::DSLItem *o = i->GetSection("nihao");
//	cout << i->Size() << endl;
//	cout << o->GetValue("gg") << endl;
//
//}


#endif