#include "stdafx.h"
#include "ReportControlFactory.h"
#include "ReportParagraph.h"
#include "ReportTitle.h"
#include "ReportItem.h"
#include "ReportList.h"
#include "tinyxml.h"

using namespace std;

ReportControlFactory::ReportControlFactory(void)
{
}


ReportControlFactory::~ReportControlFactory(void)
{
}

/// <summary>
/// Prase Templete paragraph node by name
/// </summary>
/// <param name="node">TiXmlNode</param>
shared_ptr<ReportParagraph> ReportControlFactory::PraseParagraphNode(TiXmlNode *node)
{
	shared_ptr<ReportParagraph> ptr = NULL;
	if(node->Value() == "Title"){
		ptr = make_shared<ReportTitle>();
	}
	else if(node->Value() == "Item"){
		ptr = make_shared<ReportList>();
	}
	else if(node->Value() == "List"){
		ptr = make_shared<ReportItem>();
	}
	else{
		return NULL;
	}

	ptr->SetValueByPraseNode(node);
	return ptr;
}
