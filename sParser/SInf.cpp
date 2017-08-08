#include "SInf.h"

//定义两个空引用
SInfSection SInfSection::g_nullptr_section;
SInfValue SInfValue::g_nullptr_value;
///
SInfDocument::SInfDocument()
{

}
SInfDocument::~SInfDocument()
{
	for (auto it : m_vSections)
		delete it;
}
///

SInfValue SInfDocument::GetValue(string szSection, string szKey)
{
	SInfValue def = "";
	return GetValue(szSection, szKey, def);
}
SInfValue SInfDocument::GetValue(string szSection, string szKey, SInfValue def)
{
	SInfValue result;
	for (auto ita = m_vSections.begin(); ita != m_vSections.end(); ita++)
	{
		SInfSection *pSection = *ita;
		if (pSection->GetName() == szSection)
			return pSection->GetValue(szKey, def);
	}
	return def;
}
bool SInfDocument::SetValue(string szSection, string szKey, SInfValue value)
{
	//如果没有则新建,有则插入
	auto ita = m_vSections.begin();
	SInfSection *pSection = nullptr;
	for (ita = m_vSections.begin(); ita != m_vSections.end(); ita++)
	{
		pSection = *ita;
		if (pSection->GetName() == szSection)
			break;
	}

	//如果找到了
	if (ita != m_vSections.end())
	{
		pSection->SetValue(szKey, value);
		return true;
	}
	else{//没找到
		pSection = new SInfSection();
		pSection->SetName(szSection);
		pSection->Insert(szKey, value);
		return Insert(pSection);
	}
}


SInfSection *SInfDocument::GetSection(string szSection)
{
	for (auto ita = m_vSections.begin(); ita != m_vSections.end(); ita++)
	{
		SInfSection *pSection = *ita;
		if (pSection->GetName() == szSection)
			return pSection;
	}
	return nullptr;
}
vector<SInfSection *> *SInfDocument::GetList()
{
	return &m_vSections;
}

int SInfDocument::GetSize()
{
	return m_vSections.size();
}

	//插入一个结点
bool SInfDocument::Insert(SInfSection *pSection)
{
	m_vSections.push_back(pSection);
	return true;
}
bool SInfDocument::Insert(SInfSection &section)
{
	SInfSection *temp = new SInfSection(section);
	return Insert(temp);

}

SInfSection &SInfDocument::operator [](string szSection)
{
	SInfSection *temp = this->GetSection(szSection);
	if (temp)return *temp;
	else return SInfSection::g_nullptr_section;	//空字段,由Value处理未获取的情况
	//else throw "nullptr";	//抛出一个异常,字符串
}

SInfSection &SInfDocument::operator [](int index) 
{
	try{
		return *m_vSections.at(index);
	}
	catch (...){ return SInfSection::g_nullptr_section; }
}

	/* 读写操作 */
bool SInfDocument::Load(string path)
{
	ifstream in(path.c_str(), ios::in);     //ios::app为追加
	if (!in.is_open())return false;
	else
	{
		const int bufferSize = 1024;	//定义缓冲区大小
		char buffer[bufferSize];
		SInfSection *nowSection;		//一个指向本结点的指针
		bool isNewSection = false;		//是否遇到新结点的标志

		while (!in.eof())
		{
			string strLine; 

			/*以下操作为读取一行内容*/
			//这里姑且认为一行不超过1024字节,否则错误
			in.getline(buffer, bufferSize);				//标准的去一行内容
			strLine = string(buffer);					//如果包含回车
			

			/*trim()忽略首尾空格*/
			strLine.erase(0, strLine.find_first_not_of(" "));
			strLine.erase(strLine.find_last_not_of(" ") + 1);

			/*内容解析*/
			//如果之前没遇到新结点
			if (isNewSection == false)
			{
				//TODO:内容分析
				//寻找结点
				if (strLine.empty())continue;

				if (strLine.at(0) == '[' && strLine.at(strLine.size() - 1) == ']')
				{
					string sectionName = strLine.substr(1, strLine.size() - 2);

					isNewSection = true;
					nowSection = new SInfSection();
					nowSection->SetName(sectionName);
					m_vSections.push_back(nowSection);

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
						string sectionName = strLine.substr(1, strLine.size() - 2);

						isNewSection = true;
						nowSection = new SInfSection();
						nowSection->SetName(sectionName);
						m_vSections.push_back(nowSection);

						continue;	//返回读取下一行
					}
					else{
						int startPos = -1;
						startPos = strLine.find_first_of('=');
						if (startPos >= 0)
						{
							string key = strLine.substr(0, startPos);
							string value = strLine.substr(startPos + 1);
							
							//修理一下,去除首尾空格
							key.erase(key.find_last_not_of(" ") + 1);
							value.erase(value.find_last_not_of(" ") + 1);

							nowSection->GetMap()->insert(pair<string, SInfValue>(key, value));
						}
					}

				}
				else	//否则代表此次Section结束
				{
					isNewSection = false;
				}

			}


		}
		in.close();
	}
	return true;
}
bool SInfDocument::Save(string path)
{
	ofstream out(path.c_str(), ios::out);     //ios::app为追加
	if (!out.is_open())return false;
	else
	{
		for (auto pSection : m_vSections)
		{
			out << "[" << pSection->GetName() << "]" << endl;
			for (auto it = pSection->GetMap()->begin(); it != pSection->GetMap()->end(); it++)
				out << it->first << " = " << it->second << endl;
			out << endl;
		}
		
		out.close();
	}
	return true;
}


//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////


string SInfSection::GetName()
{
	return m_szName;
}
void SInfSection::SetName(string szName)
{
	m_szName = szName;
}

SInfValue SInfSection::GetValue(string key)
{
	SInfValue def = "";
	return GetValue(key, def);
}
SInfValue SInfSection::GetValue(string key, SInfValue def)
{
	auto it = m_mKeyMap.find(key);
	if (it != m_mKeyMap.end())
		return it->second;
	else
		return def;
}
void SInfSection::SetValue(string key, SInfValue value)
{
	auto it = m_mKeyMap.find(key);
	if (it != m_mKeyMap.end())
		it->second = value;
}

map<string, SInfValue> *SInfSection::GetMap()
{
	return &m_mKeyMap;
}

bool SInfSection::Insert(string key, SInfValue value)
{
	auto it = m_mKeyMap.find(key);
	if (it != m_mKeyMap.end())
		return false;
	else{
		m_mKeyMap.insert(pair<string, SInfValue>(key, value));
	}
	return true;
}
bool SInfSection::Remove(string key)
{
	m_mKeyMap.erase(key);
	return true;
}

SInfValue &SInfSection::operator [](string szkey)
{
	auto it = m_mKeyMap.find(szkey);
	if (it != m_mKeyMap.end())
		return it->second;
	else
		return SInfValue::g_nullptr_value;
}

///////////////////////////////////////////////////////
//////////////////////////////////////////////////////

SInfValue::SInfValue()
{

}

SInfValue::SInfValue(string szValue) :m_szValue(szValue)
{

}

SInfValue::SInfValue(const char ch) 
{
	m_szValue += ch;
}

SInfValue::SInfValue(const char *szStr) :m_szValue(szStr)
{

}


SInfValue::SInfValue(int value)
{
	*this = value;
}
SInfValue::SInfValue(double value)
{
	*this = value;
}
SInfValue::SInfValue(float value)
{
	*this = value;

}
SInfValue::SInfValue(bool value)
{
	*this = value;
}
SInfValue::SInfValue(long value)
{
	*this = value;
}


SInfValue &SInfValue::operator = (const char * szValue)
{
	m_szValue = szValue;
	return *this;
}
SInfValue &SInfValue::operator = (const char Value)
{
	m_szValue += Value;
	return *this;
}
SInfValue &SInfValue::operator = (string szValue)
{
	m_szValue = szValue;
	return *this;
}
SInfValue &SInfValue::operator = (int Value)
{
	char str[32];
	sprintf_s(str, "%d", Value);
	m_szValue = str;
	return *this;
}
SInfValue &SInfValue::operator = (double Value)
{
	char str[32];
	sprintf_s(str, "%lf", Value);
	m_szValue = str;
	return *this;
}
SInfValue &SInfValue::operator = (float Value)
{
	char str[32];
	sprintf_s(str, "%f", Value);
	m_szValue = str;
	return *this;
}
SInfValue &SInfValue::operator = (bool Value)
{
	if (Value)m_szValue = "true";
	else m_szValue = "false";
	return *this;
}
SInfValue &SInfValue::operator = (long Value)
{
	char str[32];
	sprintf_s(str, "%ld", Value);
	m_szValue = str;
	return *this;
}


int SInfValue::ToInt()
{
	return (int)atoi(m_szValue.c_str());
}
float SInfValue::ToFloat()
{
	return (float)atof(m_szValue.c_str());
}
double SInfValue::ToDouble()
{
	return (double)atof(m_szValue.c_str());
}
bool SInfValue::ToBool()
{
	string ret = m_szValue;
	transform(ret.begin(), ret.end(), ret.begin(), ::tolower);
	if (ret == "true")return true;
	else return false;
}
string SInfValue::ToStrString()
{
	return m_szValue;
}
SString SInfValue::ToString()
{
	return SString::Parse(m_szValue);
}
long SInfValue::ToLong()
{
	return (long)atol(m_szValue.c_str());
}


ostream& operator <<(ostream& out, SInfValue&obj)
{
	out << obj.m_szValue;
	return out;
}
istream& operator >>(istream& in, SInfValue&obj)
{
	in >> obj.m_szValue;
	return in;
}