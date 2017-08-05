/**
* SInf类
* inf文件读写操作
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
	vector<SInfSection *> m_vSections;		//结点列表
public:
	SInfDocument();
	~SInfDocument();
public:
	/*数据获取,设置*/
	string GetValue(string szSection, string szKey, string def = "");
	bool SetValue(string szSection, string szKey, string value);

	SInfSection *GetSection(string szSection);
	vector<SInfSection *> *GetList();
	

	//插入一个结点
	bool Insert(SInfSection *pSection);
	bool Insert(SInfSection &section);
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
	map<string,string> m_mKeyMap;	//键值对
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