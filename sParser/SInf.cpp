#include "SInf.h"

//��������������
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
	//���û�����½�,�������
	auto ita = m_vSections.begin();
	SInfSection *pSection = nullptr;
	for (ita = m_vSections.begin(); ita != m_vSections.end(); ita++)
	{
		pSection = *ita;
		if (pSection->GetName() == szSection)
			break;
	}

	//����ҵ���
	if (ita != m_vSections.end())
	{
		pSection->SetValue(szKey, value);
		return true;
	}
	else{//û�ҵ�
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

	//����һ�����
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
	else return SInfSection::g_nullptr_section;	//���ֶ�,��Value����δ��ȡ�����
	//else throw "nullptr";	//�׳�һ���쳣,�ַ���
}

SInfSection &SInfDocument::operator [](int index) 
{
	try{
		return *m_vSections.at(index);
	}
	catch (...){ return SInfSection::g_nullptr_section; }
}

	/* ��д���� */
bool SInfDocument::Load(string path)
{
	ifstream in(path.c_str(), ios::in);     //ios::appΪ׷��
	if (!in.is_open())return false;
	else
	{
		const int bufferSize = 1024;	//���建������С
		char buffer[bufferSize];
		SInfSection *nowSection;		//һ��ָ�򱾽���ָ��
		bool isNewSection = false;		//�Ƿ������½��ı�־

		while (!in.eof())
		{
			string strLine; 

			/*���²���Ϊ��ȡһ������*/
			//���������Ϊһ�в�����1024�ֽ�,�������
			in.getline(buffer, bufferSize);				//��׼��ȥһ������
			strLine = string(buffer);					//��������س�
			

			/*trim()������β�ո�*/
			strLine.erase(0, strLine.find_first_not_of(" "));
			strLine.erase(strLine.find_last_not_of(" ") + 1);

			/*���ݽ���*/
			//���֮ǰû�����½��
			if (isNewSection == false)
			{
				//TODO:���ݷ���
				//Ѱ�ҽ��
				if (strLine.empty())continue;

				if (strLine.at(0) == '[' && strLine.at(strLine.size() - 1) == ']')
				{
					string sectionName = strLine.substr(1, strLine.size() - 2);

					isNewSection = true;
					nowSection = new SInfSection();
					nowSection->SetName(sectionName);
					m_vSections.push_back(nowSection);

					continue;	//���ض�ȡ��һ��

				}
			}
			else
			{
				//Ѱ����
				//�����ǿյ�ʱ��
				if (!strLine.empty())
				{
					if (strLine.at(0) == '[' && strLine.at(strLine.size() - 1) == ']')
					{
						string sectionName = strLine.substr(1, strLine.size() - 2);

						isNewSection = true;
						nowSection = new SInfSection();
						nowSection->SetName(sectionName);
						m_vSections.push_back(nowSection);

						continue;	//���ض�ȡ��һ��
					}
					else{
						int startPos = -1;
						startPos = strLine.find_first_of('=');
						if (startPos >= 0)
						{
							string key = strLine.substr(0, startPos);
							string value = strLine.substr(startPos + 1);
							
							//����һ��,ȥ����β�ո�
							key.erase(key.find_last_not_of(" ") + 1);
							value.erase(value.find_last_not_of(" ") + 1);

							nowSection->GetMap()->insert(pair<string, SInfValue>(key, value));
						}
					}

				}
				else	//�������˴�Section����
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
	ofstream out(path.c_str(), ios::out);     //ios::appΪ׷��
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