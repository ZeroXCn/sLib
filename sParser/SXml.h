/**
* SJson类
* 对jsoncpp进行简单封装
* @author ZeroX
* @version v1.0 03/08/2017
*/
#include "../sCore/SObject.h"
#include "../sCore/SString.h"
#include "extern/tinyxml2/tinyxml2.h"
using namespace tinyxml2;

#ifndef _SXML_H_
#define _SXML_H_

typedef XMLDocument SXmlDocument;
typedef XMLElement SXmlElement;
typedef XMLAttribute SXmlAttribute;
typedef XMLComment SXmlComment;
typedef XMLText SXmlText;
typedef XMLDeclaration SXmlDeclaration;
typedef XMLUnknown SXmlUnknown;
typedef XMLPrinter SXmlPrinter;


class SXml :public SObject
{

};
#endif