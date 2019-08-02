#pragma once

class TiXmlNode;
class ReportParagraph
{
public:
	ReportParagraph(void);
	~ReportParagraph(void);

	virtual void SetValueByPraseNode(TiXmlNode *node);

	CString GetNode(){ return m_node; }
	void SetNode(CString node){ m_node =  node; }

	CString GetName(){ return m_name; }
	void SetName(CString name){ m_name =  name; }

private:
	CString m_node;
	CString m_name;

protected:
	CString GetChildNodeValue(TiXmlNode *parent,CString nodeName);

	CString GetNodeAttributeStringValue(TiXmlNode *node,CString attributeName);

	bool GetNodeAttributeBoolValue(TiXmlNode *node,CString attributeName);

	int GetNodeAttributeIntValue(TiXmlNode *node,CString attributeName);
};

