/**
* SText��
* ��װfstream -���м򵥵��ļ���д
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
	//��һ���ļ�
	void Open(char *Path);
	//�ر�һ���ļ�
	void Close();

	//·�����
	bool Check(char *path = NULL);
	
	//�Ƿ����
	bool Eof();
public:
	//��д
	bool WriteNew(string Str);

	//׷��
	bool WriteAdd(string Str);

	//׷����һ��
	bool WriteLine(string Str);

	//��ȡ��ƪ
	string Read();

	//����һ��
	bool SetLine(string Str, int post);

	//ȡ��һ��
	string GetLine();
	char *GetStrLine();

	//ȡ��һ���ַ�
	char GetCh();

	//��������ƫ��
	int Search(char *Key, int offset = 0);

};

#endif