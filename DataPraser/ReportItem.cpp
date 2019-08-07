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

TiXmlElement* ReportItem::parse(CString &data)
{
	int iStart = 0;
	CString temp;
	CString cName, cData;
	int iLength = m_start.GetLength();
	/*find valid start pos of item*/
	while (iStart < data.GetLength()) {

		temp = data.Mid(iStart, iLength);
		if (temp.Compare(m_start) == 0) {
			iStart += iLength;
			break;
		}
		iStart++;
	}

	int iEnd = iStart;
	iLength = m_end.GetLength();
	while (iEnd < data.GetLength())
	{
		temp = data.Mid(iEnd, iLength);
		if (temp.Compare(m_end) == 0) {
			cName = data.Mid(iStart, iEnd - iStart);
			break;
		}
		iEnd++;
	}

	iEnd += iLength;
	/*find valid start pos of data*/
	while (iEnd < data.GetLength()) {
		CString temp(data[iEnd]);
		if (temp != "\r" && temp != " " && temp != "\n" && temp != "\t") {
			break;
		}
		iEnd++;
	}

	iStart = iEnd;
	iLength = m_split.GetLength();
	while (iEnd < data.GetLength())
	{
		temp = data.Mid(iEnd, iLength);
		if (temp.Compare(m_split) == 0) {
			cData = data.Mid(iStart, iEnd - iStart);
			break;
		}
		iEnd++;
	}
	data = data.Right(data.GetLength() - iEnd);

	TiXmlElement* ele = new TiXmlElement("detail");
	ele->SetAttribute("name", cName);
	ele->LinkEndChild(new TiXmlText(cData));

	return ele;
}
