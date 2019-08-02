#include "stdafx.h"
#include "ReportTitle.h"
#include "tinyxml.h"


ReportTitle::ReportTitle(void)
{
}


ReportTitle::~ReportTitle(void)
{
}

void ReportTitle::SetValueByPraseNode(TiXmlNode *node)
{
	assert(node);

	SetSplite(GetNodeAttributeStringValue(node,"split"));
	
	__super::SetValueByPraseNode(node);
}
