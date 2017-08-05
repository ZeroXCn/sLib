#include "SInf.h"

SInfDocument::SInfDocument()
{

}
SInfDocument::~SInfDocument()
{
	for (auto it : m_vSections)
		delete it;
}
///
string SInfDocument::GetValue(string szSection, string szKey, string def)
{
	string result;
	for (auto ita = m_vSections.begin(); ita != m_vSections.end(); ita++)
	{
		SInfSection *pSection = *ita;
		if (pSection->GetName() == szSection)
			return pSection->GetValue(szKey, def);
	}
	return def;
}
bool SInfDocument::SetValue(string szSection, string szKey, string value)
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

							nowSection->GetMap()->insert(pair<string,string>(key, value));
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

string SInfSection::GetValue(string key, string def)
{
	auto it = m_mKeyMap.find(key);
	if (it != m_mKeyMap.end())
		return it->second;
	else
		return def;
}
void SInfSection::SetValue(string key, string value)
{
	auto it = m_mKeyMap.find(key);
	if (it != m_mKeyMap.end())
		it->second = value;
}

map<string, string> *SInfSection::GetMap()
{
	return &m_mKeyMap;
}

bool SInfSection::Insert(string key, string value)
{
	auto it = m_mKeyMap.find(key);
	if (it != m_mKeyMap.end())
		return false;
	else{
		m_mKeyMap.insert(pair<string,string>(key, value));
	}
	return true;
}
bool SInfSection::Remove(string key)
{
	m_mKeyMap.erase(key);
	return true;
}