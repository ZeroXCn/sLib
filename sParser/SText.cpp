#include "SText.h"

SText::SText(char *Path) :File(Path)
{
	this->Path = Path;
}
SText::~SText(){
	File.close();
}

//TODO:这里没有就创建,不存在失败
void SText::Open(char *Path){
	this->Path = Path;
	File.open(Path);
}
void SText::Close()
{
	this->Path = "";
	File.close();
}
bool SText::WriteNew(string Str)
{
	ofstream file(Path.c_str(), ios::out);
	file << Str;
	file.close();
	return true;
}
bool SText::WriteAdd(string Str)
{
	//	ofstream file(Path.c_str(),ios::app);
	File.seekp(0, ios::end);
	File << Str;
	//file.close();
	return true;
}
bool SText::WriteLine(string Str)
{
	return WriteAdd(Str + "\r\n");
}
string SText::Read()
{
	ifstream AllFile(Path.c_str());
	if (!AllFile)return "";
	const int nSize = 1024;
	char sTemp[nSize] = { '\0' };
	string Result = "";
	while (!AllFile.eof())
	{
		AllFile.read(sTemp, nSize);
		Result += sTemp;
	}
	return Result;
}
bool SText::Check(char *path)
{
	ifstream file;
	if (path)file.open(path);
	else file.open(Path.c_str());
	if (!file)return false;
	else return true;
}
bool SText::Eof()
{
	if (!File.eof())return false;
	else return true;

}
bool SText::SetLine(string Str, int post)
{
	fstream file;
	file.open(Path.c_str());
	file.seekp(post);
	file << Str;
	//TODO:这里太直接了
	return true;
}
string SText::GetLine()
{
	static const int nSize = 128;
	static char sTemp[nSize] = { '\0' };
	File.getline(sTemp, sizeof(sTemp));
	return string(sTemp);

}
char *SText::GetStrLine()
{
	static const int nSize = 128;
	static char sTemp[nSize] = { '\0' };
	if (!File.eof())
	{
		File.getline(sTemp, sizeof(sTemp));
		return sTemp;
	}
	return NULL;
}
char SText::GetCh()
{
	char cTemp;
	if ((cTemp = File.get()) != EOF)return cTemp;
	return '\0';
}
int SText::Search(char *Key, int offset)
{
	fstream searchfile;
	searchfile.open(Path.c_str());
	searchfile.seekg(offset);
	int i = 0, j = 0;
	int Result;
	char cTemp;
	while ((cTemp = searchfile.get()) != EOF && Key[j])
	{
		if (cTemp == Key[j]){ Result = (int)searchfile.tellg(); j++; }
		else
		{
			searchfile.seekg((int)searchfile.tellg() - j); j = 0;
		}
	}
	searchfile.close();
	if (j == strlen(Key))
		return(Result - j);
	else
		return -1;
}