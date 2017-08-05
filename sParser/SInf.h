/**
* SInf��
* inf�ļ���д����
* @author ZeroX
* @version v1.2 05/08/2017(12/11/2016)
*/
#include "../sCore/SObject.h"
#include "../sCore/SString.h"

#ifndef _SINF_H_
#define _SINF_H_
#include <sstream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

class SInfDocument;
class SInfSection;

class SInfDocument:public SObject
{
private:
	vector<SInfSection *> m_vSections;		//����б�
public:
	SInfDocument();
	~SInfDocument();
public:
	/*���ݻ�ȡ,����*/
	string GetValue(string szSection, string szKey, string def = "");
	bool SetValue(string szSection, string szKey, string value);

	SInfSection *GetSection(string szSection);
	vector<SInfSection *> *GetList();
	

	//����һ�����
	bool Insert(SInfSection *pSection);
	bool Insert(SInfSection &section);
public:
	/* ��д���� */
	bool Load(string path);
	bool Save(string path);


};

//�ڵ�-�����ظ��ڵ�
class SInfSection :public SObject
{
private:
	string m_szName;				//�ڵ�����
	map<string,string> m_mKeyMap;	//��ֵ��
public:
	string GetName();
	void SetName(string szName);

	map<string, string> *GetMap();

	string GetValue(string key, string def = "");
	void SetValue(string key, string value);

	bool Insert(string key, string value);
	bool Remove(string key);

};

#endif