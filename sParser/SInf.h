/**
* SInf类
* inf文件读写操作
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

//Inf文档
class SInfDocument:public SObject
{
private:
	vector<SInfSection *> m_vSections;		//结点列表
public:
	SInfDocument();
	~SInfDocument();
public:
	/*数据获取,设置*/
	SInfValue GetValue(string szSection, string szKey);
	SInfValue GetValue(string szSection, string szKey, SInfValue def );
	bool SetValue(string szSection, string szKey, SInfValue value);

	SInfSection *GetSection(string szSection);
	vector<SInfSection *> *GetList();

	//列表长度
	int GetSize();

	//插入一个结点
	bool Insert(SInfSection *pSection);
	bool Insert(SInfSection &section);

	SInfSection &operator [](string szSection);
	SInfSection &operator [](int index);
public:
	/* 读写操作 */
	bool Load(string path);
	bool Save(string path);


};

//节点-允许重复节点
class SInfSection :public SObject
{
private:
	string m_szName;				//节点名称
	map<string, SInfValue> m_mKeyMap;	//键值对
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

//Inf值-用于对值进行转换
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