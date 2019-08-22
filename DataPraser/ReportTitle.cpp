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

	__super::SetValueByPraseNode(node);
}

TiXmlElement* ReportTitle::parse(CString &data)
{
	int iStart = 0;
	CString cstr;
	/*find valid start pos*/
	while (iStart < data.GetLength()) {
		CString temp(data[iStart]);
		if (temp != "\r\n" && temp != " ") {
			break;
		}
		iStart++;
	}

	int iEnd = iStart;
	CString temp;
	int iLength = m_split.GetLength();
	while (iEnd < data.GetLength())
	{
		temp = data.Mid(iEnd, iLength);
		if (temp == m_split) {
			cstr = data.Mid(iStart, iEnd - iStart);
			iEnd += iLength;
			break;
		}
		iEnd++;
	}
	data = data.Right(data.GetLength() - iEnd);

	cstr.Remove('\t');
	cstr.Remove('\r');
	cstr.Remove('\n');

	TiXmlElement* ele = new TiXmlElement("title");
	ele->LinkEndChild(new TiXmlText(cstr));

	return ele;
}
