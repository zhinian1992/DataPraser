#include "stdafx.h"
#include "ReportList.h"
#include "tinyxml.h"

ReportList::ReportList(void)
{
}


ReportList::~ReportList(void)
{
}

void ReportList::SetValueByPraseNode(TiXmlNode *node)
{
	assert(node);

	SetSplite(GetNodeAttributeStringValue(node,"split"));

	__super::SetValueByPraseNode(node);
}
