#include "stdafx.h"
#include "ReportItem.h"
#include "tinyxml.h"

ReportItem::ReportItem(void)
{
}


ReportItem::~ReportItem(void)
{
}

void ReportItem::SetValueByPraseNode(TiXmlNode *node)
{
	assert(node);

	SetStart(GetNodeAttributeStringValue(node,"start"));
	SetEnd(GetNodeAttributeStringValue(node,"end"));

	__super::SetValueByPraseNode(node);
}
