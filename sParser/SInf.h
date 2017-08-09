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

class SInfDocument;
class SInfSection;
class SInfValue;

//Inf文档
class SInfDocument:public SObject
{
private:
	std::vector<SInfSection *> m_vSections;		//结点列表
public:
	SInfDocument();
	~SInfDocument();
public:
	/*数据获取,设置*/
	SInfValue GetValue(std::string szSection, std::string szKey);
	SInfValue GetValue(std::string szSection, std::string szKey, SInfValue def);
	bool SetValue(std::string szSection, std::string szKey, SInfValue value);

	SInfSection *GetSection(std::string szSection);
	std::vector<SInfSection *> *GetList();

	//列表长度
	int GetSize();

	//插入一个结点
	bool Insert(SInfSection *pSection);
	bool Insert(SInfSection &section);

	SInfSection &operator [](std::string szSection);
	SInfSection &operator [](int index);
public:
	/* 读写操作 */
	bool Load(std::string path);
	bool Save(std::string path);


};

//节点-允许重复节点
class SInfSection :public SObject
{
	friend class SInfDocument;
private:
	static SInfSection g_nullptr_section;
private:
	std::string m_szName;					//节点名称
	std::map<std::string, SInfValue> m_mKeyMap;	//键值对
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

//Inf值-用于对值进行转换
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