/**
* SJson��
* ��jsoncpp���м򵥷�װ
* @author ZeroX
* @version v1.0 03/08/2017
*/
#include "../sCore/SObject.h"
#include "../sCore/SString.h"
#include "extern/tinyxml2/tinyxml2.h"
using namespace tinyxml2;

#ifndef _SXML_H_
#define _SXML_H_
/* ���������޷��̳и���Ĺ��캯�� */
//class SXmlDocument :public SObject, public XMLDocument{};
//class SXmlElement :public SObject, public XMLElement{};
//class SXmlAttribute :public SObject, public XMLAttribute{};
//class SXmlComment :public SObject, public XMLComment{};
//class SXmlText :public SObject, public XMLText{};
//class SXmlDeclaration :public SObject, public XMLDeclaration{};
//class SXmlUnknown :public SObject, public XMLUnknown{};
//class SXmlPrinter :public SObject, public XMLPrinter{};

typedef XMLDocument SXmlDocument;
typedef XMLElement SXmlElement;
typedef XMLAttribute SXmlAttribute;
typedef XMLComment SXmlComment;
typedef XMLText SXmlText;
typedef XMLDeclaration SXmlDeclaration;
typedef XMLUnknown SXmlUnknown;
typedef XMLPrinter SXmlPrinter;

#endif