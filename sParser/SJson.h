/**
* SJson类
* 对jsoncpp进行简单封装
* @author ZeroX
* @version v1.0 03/08/2017
*/
#include "../sCore/SObject.h"
#include "extern/jsoncpp/json.h"

#ifndef _SJSON_H_
#define _SJSON_H_
#include <string>
#include <fstream>

typedef Json::Reader SJsonRender;
typedef Json::FastWriter SJsonWriter;

class SJsonDocument;
class SJsonValue;


class SJsonValue :
	public SObject,
	public Json::Value
{
public:
	SJsonValue(Json::ValueType type = Json::nullValue) :Value(type){}
	SJsonValue(Int value) :Value(value){}
	SJsonValue(UInt value) :Value(value){}
#if defined(JSON_HAS_INT64)
	SJsonValue(Int64 value) : Value(value){}
	SJsonValue(UInt64 value) :Value(value){}
#endif // if defined(JSON_HAS_INT64)
	SJsonValue(double value) : Value(value){}
	SJsonValue(const char* value) :Value(value){}
	SJsonValue(const char* begin, const char* end) :Value(begin, end){}
	SJsonValue(const Json::StaticString& value) :Value(value){}
	SJsonValue(const JSONCPP_STRING& value) :Value(value){}
#ifdef JSON_USE_CPPTL
	SJsonValue(const CppTL::ConstString& value) : Value(value){}
#endif
	SJsonValue(bool value) : Value(value){}
	SJsonValue(const SJsonValue& other) :Value(other){}
#if JSON_HAS_RVALUE_REFERENCES
	SJsonValue(SJsonValue&& other) : Value(other){}
#endif

};

class SJsonDocument :public SObject
{
protected:
	SJsonValue m_JsonRoot;
public:
	static SJsonValue FromJson(std::ifstream &is, bool *result = nullptr);
	static SJsonValue FromJson(std::string content, bool *result = nullptr);
	static std::string ToJson(SJsonValue value);
public:
	//取得Json根
	SJsonValue &GetRoot();

	bool Load(TCHAR *lpszPath);
	bool Save(TCHAR *lpszPath);

};


#endif