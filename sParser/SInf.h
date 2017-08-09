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

class SInfDocument;
class SInfSection;
class SInfValue;

//Inf�ĵ�
class SInfDocument:public SObject
{
private:
	std::vector<SInfSection *> m_vSections;		//����б�
public:
	SInfDocument();
	~SInfDocument();
public:
	/*���ݻ�ȡ,����*/
	SInfValue GetValue(std::string szSection, std::string szKey);
	SInfValue GetValue(std::string szSection, std::string szKey, SInfValue def);
	bool SetValue(std::string szSection, std::string szKey, SInfValue value);

	SInfSection *GetSection(std::string szSection);
	std::vector<SInfSection *> *GetList();

	//�б���
	int GetSize();

	//����һ�����
	bool Insert(SInfSection *pSection);
	bool Insert(SInfSection &section);

	SInfSection &operator [](std::string szSection);
	SInfSection &operator [](int index);
public:
	/* ��д���� */
	bool Load(std::string path);
	bool Save(std::string path);


};

//�ڵ�-�����ظ��ڵ�
class SInfSection :public SObject
{
	friend class SInfDocument;
private:
	static SInfSection g_nullptr_section;
private:
	std::string m_szName;					//�ڵ�����
	std::map<std::string, SInfValue> m_mKeyMap;	//��ֵ��
public:
	std::string GetName();
	void SetName(std::string szName);

	std::map<std::string, SInfValue> *GetMap();

	SInfValue GetValue(std::string key);
	SInfValue GetValue(std::string key, SInfValue def);
	void SetValue(std::string key, SInfValue value);

	bool Insert(std::string key, SInfValue value);
	bool Remove(std::string key);

	SInfValue &operator [](std::string szkey);
};

//Infֵ-���ڶ�ֵ����ת��
class SInfValue :public SObject
{
	friend class SInfSection;
	friend std::ostream& operator <<(std::ostream&, SInfValue&);
	friend std::istream& operator >>(std::istream&, SInfValue&);
private:
	static SInfValue g_nullptr_value;
private:
	std::string m_szValue;
public:
	SInfValue();
	SInfValue(const char ch);
	SInfValue(const char *szStr);

	SInfValue(int value);
	SInfValue(double value);
	SInfValue(float value);
	SInfValue(bool value);
	SInfValue(long value);
	SInfValue(std::string szValue);

	SInfValue &operator = (const char * szValue);
	SInfValue &operator = (const char Value);
	SInfValue &operator = (std::string szValue);
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
	std::string ToStrString();
	SString ToString();
	long ToLong();
};

#endif