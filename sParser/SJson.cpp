#include "SJson.h"
using namespace std;
SJsonValue SJsonDocument::FromJson(ifstream &is, bool *result)
{
	Json::Reader reader;

	SJsonValue json_object;
	bool ret=reader.parse(is, json_object,false);
	if (result)*result = ret;

	return json_object;

}

SJsonValue SJsonDocument::FromJson(string content, bool *result)
{
	Json::Reader reader;

	SJsonValue json_object;
	const char *json_document = content.c_str();
	bool ret = reader.parse(json_document, json_object);
	if (result)*result = ret;

	return json_object;

}
string SJsonDocument::ToJson(SJsonValue value)
{
	Json::FastWriter fast_writer;
	return fast_writer.write(value);
}

SJsonValue &SJsonDocument::GetRoot()
{
	return m_JsonRoot;
}

bool SJsonDocument::Load(TCHAR *lpszPath)
{
	std::ifstream is;
	is.open(lpszPath, std::ios::binary);
	if (is.is_open())
	{
		m_JsonRoot = FromJson(is);
		return true;
	}
	return false;
}
bool SJsonDocument::Save(TCHAR *lpszPath)
{
	std::ofstream ofs;
	ofs.open(lpszPath);
	if (ofs.is_open())
	{
		ofs << ToJson(m_JsonRoot);
		return true;
	}
	
	ofs.close();
	return false;
}