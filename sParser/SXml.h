/**
* SJson类
* 对jsoncpp进行简单封装
* @author ZeroX
* @version v1.0 03/08/2017
*/
#include "../sCore/SObject.h"
#include "../sCore/SString.h"
#include "extern/tinyxml2/tinyxml2.h"

#ifndef _SXML_H_
#define _SXML_H_
/* 这样做会无法继承父类的构造函数 */
//class SXmlDocument :public SObject, public XMLDocument{};
//class SXmlElement :public SObject, public XMLElement{};
//class SXmlAttribute :public SObject, public XMLAttribute{};
//class SXmlComment :public SObject, public XMLComment{};
//class SXmlText :public SObject, public XMLText{};
//class SXmlDeclaration :public SObject, public XMLDeclaration{};
//class SXmlUnknown :public SObject, public XMLUnknown{};
//class SXmlPrinter :public SObject, public XMLPrinter{};

typedef tinyxml2::XMLDocument SXmlDocument;
typedef tinyxml2::XMLElement SXmlElement;
typedef tinyxml2::XMLAttribute SXmlAttribute;
typedef tinyxml2::XMLComment SXmlComment;
typedef tinyxml2::XMLText SXmlText;
typedef tinyxml2::XMLDeclaration SXmlDeclaration;
typedef tinyxml2::XMLUnknown SXmlUnknown;
typedef tinyxml2::XMLPrinter SXmlPrinter;

#endif