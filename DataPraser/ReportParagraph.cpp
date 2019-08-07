#include "stdafx.h"
#include "ReportParagraph.h"
#include "tinyxml.h"


ReportParagraph::ReportParagraph(void)
{
}


ReportParagraph::~ReportParagraph(void)
{
}

void ReportParagraph::SetValueByPraseNode(TiXmlNode *node)
{
	assert(node);

	SetSplit(GetNodeAttributeStringValue(node, "split"));
}

/// <summary>
/// Get the value of the child node if node not exist return ""
/// </summary>
/// <param name="parent">parent node</param>
/// <param name="nodeName">the name of the child node</param>
CString ReportParagraph::GetChildNodeValue(TiXmlNode *parent,CString nodeName)
{
	if(!parent->FirstChildElement(nodeName)){
		return "";
	}
	return parent->FirstChildElement(nodeName)->GetText();
}

/// <summary>
/// Get named attribute string value of node 
/// </summary>
CString ReportParagraph::GetNodeAttributeStringValue(TiXmlNode *node,CString attributeName)
{
	assert(node);
	TiXmlElement *ele =  node->ToElement();
	TiXmlAttribute *pAttr = ele->FirstAttribute();
	while(pAttr){
		if(pAttr->NameTStr() == attributeName){
			return ChangeCStringToCharacter(pAttr->Value());
		}
		else 
			pAttr = pAttr->Next();
	}
	return "";
}

/// <summary>
/// Get named attribute bool value of node 
/// </summary>
bool ReportParagraph::GetNodeAttributeBoolValue(TiXmlNode *node,CString attributeName)
{
	assert(node);
	TiXmlElement *ele =  node->ToElement();
	TiXmlAttribute *pAttr = ele->FirstAttribute();
	while(pAttr){
		if(pAttr->NameTStr() == attributeName){
			return pAttr->IntValue();
		}
		else 
			pAttr = pAttr->Next();
	}
	return false;
}

/// <summary>
/// Get named attribute int value of node 
/// </summary>
int ReportParagraph::GetNodeAttributeIntValue(TiXmlNode *node,CString attributeName)
{
	assert(node);
	TiXmlElement *ele =  node->ToElement();
	TiXmlAttribute *pAttr = ele->FirstAttribute();
	while(pAttr){
		if(pAttr->NameTStr() == attributeName){
			return pAttr->IntValue();
		}
		else 
			pAttr = pAttr->Next();
	}
	return 0;
}

/// <summary>
/// Change CString to character such as \t \n \r \r\n \r\n\r\n
/// </summary>
/// <param name="str"></param>
CString ReportParagraph::ChangeCStringToCharacter(CString str)
{
	if (str.Compare("\\r\\n") == 0) {
		return "\r\n";
	}
	else if (str.Compare("\\r\\n\\r\\n") == 0) {
		return "\r\n\r\n";
	}
	else if (str.Compare("\\n") == 0) {
		return "\n";
	}
	else if (str.Compare("\\r") == 0) {
		return "\r";
	}
	else if (str.Compare("\\t") == 0) {
		return "\t";
	}
	return str;
}
