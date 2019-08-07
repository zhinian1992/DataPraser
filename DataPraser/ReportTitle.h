#pragma once
#include "reportparagraph.h"

class ReportTitle :
	public ReportParagraph
{
public:
	ReportTitle(void);
	~ReportTitle(void);

	virtual void SetValueByPraseNode(TiXmlNode *node);

	virtual TiXmlElement* parse(CString &data);

};

