#pragma once
#include <memory>


class TiXmlNode;
class ReportParagraph;
class ReportTitle;
class ReportItem;
class ReportList;

class ReportControlFactory
{
public:
	ReportControlFactory(void);
	~ReportControlFactory(void);

	std::shared_ptr<ReportParagraph> PraseParagraphNode(TiXmlNode *node);

};

