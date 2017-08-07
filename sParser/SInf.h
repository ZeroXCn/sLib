/**
* SInf��
* inf�ļ���д����
* @author ZeroX
* @version v1.3 07/08/2017(12/11/2016)
*/
#include "../sCore/SObject.h"
#include "../sCore/SString.h"

#ifndef _SINF_H_
#define _SINF_H_
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

class SInfDocument;
class SInfSection;
class SInfValue;

//Inf�ĵ�
class SInfDocument:public SObject
{
private:
	vector<SInfSection *> m_vSections;		//����б�
public:
	SInfDocument();
	~SInfDocument();
public:
	/*���ݻ�ȡ,����*/
	SInfValue GetValue(string szSection, string szKey);
	SInfValue GetValue(string szSection, string szKey, SInfValue def );
	bool SetValue(string szSection, string szKey, SInfValue value);

	SInfSection *GetSection(string szSection);
	vector<SInfSection *> *GetList();

	//�б���
	int GetSize();

	//����һ�����
	bool Insert(SInfSection *pSection);
	bool Insert(SInfSection &section);

	SInfSection &operator [](string szSection);
	SInfSection &operator [](int index);
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
	map<string, SInfValue> m_mKeyMap;	//��ֵ��
public:
	string GetName();
	void SetName(string szName);

	map<string, SInfValue> *GetMap();

	SInfValue GetValue(string key);
	SInfValue GetValue(string key, SInfValue def);
	void SetValue(string key, SInfValue value);

	bool Insert(string key, SInfValue value);
	bool Remove(string key);

	SInfValue &operator [](string szkey);
};

//Infֵ-���ڶ�ֵ����ת��
class SInfValue :public SObject
{
	friend ostream& operator <<(ostream&, SInfValue&);
	friend istream& operator >>(istream&, SInfValue&);

private:
	string m_szValue;
public:
	SInfValue();
	SInfValue(const char ch);
	SInfValue(const char *szStr);

	SInfValue(int value);
	SInfValue(double value);
	SInfValue(float value);
	SInfValue(bool value);
	SInfValue(long value);
	SInfValue(string szValue);

	SInfValue &operator = (const char * szValue);
	SInfValue &operator = (const char Value);
	SInfValue &operator = (string szValue);
	SInfValue &operator = (int Value);
	SInfValue &operator = (double Value);
	SInfValue &operator = (float Value);
	SInfValue &operator = (bool Value);
	SInfValue &operator = (long Value);
public:
	int ToInt();
	float ToFloat();
	double ToDouble();
	bool ToBool();
	string ToStrString();
	SString ToString();
	long ToLong();
};

#endif