#include "stdafx.h"
#include "TempletePraser.h"
#include "ReportTitle.h"
#include "ReportItem.h"
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

	TiXmlNode *root = doc.RootElement();
	assert(root);

	/*Prase Title node*/
	TiXmlNode *node = root->FirstChild("Title");
	assert(node);
	shared_ptr<ReportTitle> ptr = make_shared<ReportTitle>();
	ptr->SetValueByPraseNode(node);
	m_praseCenter.SetTitleValue(ptr);

	/*Prase keywords node*/
	node = root->FirstChild("Keywords");
	assert(node);
	TiXmlElement *ele = node->FirstChildElement("key");
	while(ele){
		CString key = ele->GetText();
		CString name = ele->FirstAttribute()->Value();
		m_praseCenter.AddParagraph(key, name);

		ele = ele->NextSiblingElement();
	}

	/*Prase file fomate node*/
	node = root->FirstChild("FileFormat");
	assert(node);
	ele = node->FirstChildElement();
	while (ele) {
		CString para = ele->GetText();
		m_praseCenter.AddFileFormat(para);

		ele = ele->NextSiblingElement();
	}

	return true;
}



