/**
* SText类
* 封装fstream -进行简单的文件读写
* @author ZeroX
* @version v1.0 03/08/2017(02/02/2016)
*/
#include "../sCore/SObject.h"
#include "../sCore/SString.h"

#ifndef _STEXT_H_
#define _STEXT_H_
#include<iostream>
#include<fstream>
using namespace std;

class SText :public SObject
{
private:
	fstream File;
	string Path;
public:
	SText(char *Path);
	~SText();
public:
	//打开一个文件
	void Open(char *Path);
	//关闭一个文件
	void Close();

	//路径检测
	bool Check(char *path = NULL);
	
	//是否结束
	bool Eof();
public:
	//重写
	bool WriteNew(string Str);

	//追加
	bool WriteAdd(string Str);

	//追加新一行
	bool WriteLine(string Str);

	//读取整篇
	string Read();

	//插入一行
	bool SetLine(string Str, int post);

	//取得一行
	string GetLine();
	char *GetStrLine();

	//取得一个字符
	char GetCh();

	//搜索文字偏移
	int Search(char *Key, int offset = 0);

};

#endif