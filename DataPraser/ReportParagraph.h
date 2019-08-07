#pragma once

class TiXmlElement;
class TiXmlNode;
class ReportParagraph
{
public:
	ReportParagraph(void);
	~ReportParagraph(void);

	virtual void SetValueByPraseNode(TiXmlNode *node);

	virtual TiXmlElement* parse(CString &data) = 0;

	CString GetSplit() { return m_split; }
	void SetSplit(CString split) { m_split = split; }

protected:
	CString m_split;

protected:
	CString GetChildNodeValue(TiXmlNode *parent,CString nodeName);

	CString GetNodeAttributeStringValue(TiXmlNode *node,CString attributeName);

	bool GetNodeAttributeBoolValue(TiXmlNode *node,CString attributeName);

	int GetNodeAttributeIntValue(TiXmlNode *node,CString attributeName);

private:
	CString ChangeCStringToCharacter(CString str);
};

