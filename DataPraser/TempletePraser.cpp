#include "stdafx.h"
#include "TempletePraser.h"
#include "ReportControlFactory.h"
#include "PraseCenter.h"
#include "tinyxml.h"
#include <string>
using namespace std;


TempletePraser::TempletePraser(PraseCenter &praseCenter)
	:m_praseCenter(praseCenter)
{

}

TempletePraser::~TempletePraser(void)
{
}

/// <summary>
/// Get paragraph list by prase the templete file
/// </summary>
/// <param name="sData">full content in templete file</param>
bool TempletePraser::PraseTempleteFile(CString &file)
{
	m_praseCenter.WriteLog("start prase templete file!");

	TiXmlDocument doc(file);
	bool bRet = doc.LoadFile();
	if(!bRet){
		m_praseCenter.WriteLog("Error:TiXmlDocument LoadFile failed!");
		return false;
	}

	TiXmlNode *node = doc.RootElement();
	assert(node);

	node = node->FirstChild();

	while(node){
		ReportControlFactory RCtrl;
		shared_ptr<ReportParagraph> ptr = RCtrl.PraseParagraphNode(node);

		if(!ptr){
			m_praseCenter.WriteLog("Error:Prase Templete file failed ! the type of node is not exist");
			return false;
		}
		m_praseCenter.AddParagraph(ptr);

		node = node->NextSibling();
	}

	return true;
}



