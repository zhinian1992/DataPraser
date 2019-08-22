#include "stdafx.h"
#include "PraseCenter.h"
#include "ReportParagraph.h"
#include "ReportItem.h"
#include "ReportTitle.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include "tinyxml.h"
#include <algorithm>

using namespace std;


PraseCenter::PraseCenter(void)
	:m_xmlPraser(*this),
	m_isMultiple(false)
{
}


PraseCenter::~PraseCenter(void)
{
}

/// <summary>
/// Load date files
/// </summary>
vector<CString> PraseCenter::LoadDataFiles()
{
	m_vDataFiles.clear();

	WriteLog("enter PraseCenter::LoadDataFiles!");

	CFileDialog dlg(TRUE, _T("*.txt"), NULL, OFN_ALLOWMULTISELECT|OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,
		_T("Txt Files(*.txt)|*.txt|"), NULL);
	dlg.m_ofn.lpstrTitle = _T("选择数据文件");
	if(dlg.DoModal() == IDOK){
		POSITION fileNamesPosition = dlg.GetStartPosition();
		while(fileNamesPosition != NULL){
			m_vDataFiles.push_back(dlg.GetNextPathName(fileNamesPosition));
		}
	}
	return m_vDataFiles;
}

/// <summary>
/// Load  & prase templete file
/// </summary>
CString PraseCenter::LoadTempleteFile()
{
	ClearLastTempleteData();

	WriteLog("enter PraseCenter::LoadTempleteFile!");
	CFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Describe Files (*.xml)|*.xml|Txt Files (*.xml)|*.xml||"), NULL);

	if (dlgFile.DoModal())
	{
		m_templeteFile = dlgFile.GetPathName();
		bool bRet = m_xmlPraser.PraseTempleteFile(m_templeteFile);
		if(!bRet){
			WriteLog("Error:praser templete file failed!");
			m_templeteFile = "";
		}
		if(m_keyMap.empty()){
			WriteLog("Error:praser templete file failed!no paragraph exist!");
		}
	}

	return m_templeteFile;
}

/// <summary>
/// Set the file path after prase 
/// </summary>
CString PraseCenter::SetSaveFilePath()
{
	WriteLog("enter PraseCenter::SetSaveFile!");
	m_saveFile = "";

	TCHAR           szFolderPath[MAX_PATH] = {0};    

	BROWSEINFO      sInfo;  
	::ZeroMemory(&sInfo, sizeof(BROWSEINFO));  
	sInfo.pidlRoot   = 0;  
	sInfo.lpszTitle   = _T("请选择处理结果存储路径");  
	sInfo.ulFlags   = BIF_RETURNONLYFSDIRS|BIF_EDITBOX|BIF_DONTGOBELOWDOMAIN;  
	sInfo.lpfn     = NULL;  

	LPITEMIDLIST lpidlBrowse = ::SHBrowseForFolder(&sInfo);   
	if (lpidlBrowse != NULL)  
	{  
		if (::SHGetPathFromIDList(lpidlBrowse,szFolderPath))    
		{  
			m_saveFile = szFolderPath;  
		}  
	}  
	if(lpidlBrowse != NULL)  
	{  
		::CoTaskMemFree(lpidlBrowse);  
	}

	return m_saveFile;
}

/// <summary>
/// Prase data files
/// </summary>
bool PraseCenter::ParseDataFiles()
{
	if(m_vDataFiles.empty()){
		WriteLog("Error:please choose data files first!");
		return false;
	}

	if(m_keyMap.empty()){
		WriteLog("Error:please load templete files befor prasing!");
		return false;
	}

	vector<CString>::iterator iter = m_vDataFiles.begin();
	while(iter!=m_vDataFiles.end()){

		CString filePath = "";
		/*set the path to save*/
		if (m_saveFile.IsEmpty()) {
			filePath = *iter;
			const size_t last_slash_idx = filePath.ReverseFind('.');
			assert(last_slash_idx != std::string::npos);
			filePath = filePath.Left(last_slash_idx);
			filePath.Append("_data.xml");
		}
		else {
			size_t last_slash_idx = (*iter).ReverseFind('\\');
			CString fileName = (*iter).Right((*iter).GetLength() - last_slash_idx);
			last_slash_idx = fileName.ReverseFind('.');
			fileName = fileName.Left(last_slash_idx);
			filePath = m_saveFile;
			filePath.Append(fileName);
			filePath.Append("_data.xml");
		}
		PraseFile(*iter);

		/*save xml to file*/
		if (!m_vElement.empty()) {
			saveXMl2File(filePath);
		}

		iter++;
	}

	return true;
}

/// <summary>
/// Add paragraph detail to vector
/// </summary>
/// <param name="elem">ReportParagraph node</param>
void PraseCenter::AddParagraph(CString &key, CString &name)
{
	m_keyMap[key] = name;
}

/// <summary>
/// Add paragraphs to vector
/// </summary>
/// <param name="paragraph">paragraph type</param>
void PraseCenter::AddFileFormat(CString paragraph)
{
	m_vFormat.push_back(paragraph);
}

/// <summary>
/// Write operate log to receive dialog
/// </summary>
void PraseCenter::WriteLog(CString log)
{
	assert(m_hWnd);

	log.Append("\r\n");
	::SendMessageA(m_hWnd,WM_WRITELOG,0,(LPARAM)&log);
}

/// <summary>
/// Clear Child vector
/// </summary>
void PraseCenter::ClearLastTempleteData()
{
	m_templeteFile = "";
	m_title = NULL;
	m_keyMap.clear();
	m_vFormat.clear();
	m_vElement.clear();
	m_vItems.clear();
}

/// <summary>
/// Prase single data file
/// </summary>
/// <param name="fileName">single file path</param>
void PraseCenter::PraseFile(CString & fileName)
{
	CFile file;
	if (!file.Open(fileName, CFile::modeReadWrite)) {
		WriteLog("Error:open data files failed! the file name is:");
		WriteLog(fileName);
		return;
	}
	DWORD len = file.GetLength();
	char* buffer = NULL;
	buffer = new char[len + 1];
	buffer[len] = '\0';

	file.Read(buffer, len);
	file.Close();

	CString sContent = buffer;
	
	/*cut multiple file data to single data list*/
	if (m_isMultiple) {
		if (m_itemSplit.IsEmpty()) {
			WriteLog("Error:itme split character is null!");
		}
		else {
			size_t index = sContent.Find(m_itemSplit);
			while (index != std::string::npos) {
				CString temp = sContent.Left(index);
				m_vItems.push_back(temp);
				sContent = sContent.Right(sContent.GetLength() - index - m_itemSplit.GetLength());
				index = sContent.Find(m_itemSplit);
			}
		}
	}
	m_vItems.push_back(sContent);
	PraseFileData();

	WriteLog("prase file data success!");

	delete[] buffer;
	buffer = NULL;
}

/// <summary>
/// Prase the data in file
/// </summary>
void PraseCenter::PraseFileData()
{
	vector<CString>::iterator iter = m_vItems.begin();
	vector<CString>::iterator iter_formate;
	for (;iter!=m_vItems.end();iter++)
	{
		TiXmlElement* element = new TiXmlElement("Item");

		for (iter_formate = m_vFormat.begin(); iter_formate != m_vFormat.end(); iter_formate++) {
			if ((*iter_formate).Compare("Title") == 0){
				TiXmlElement* ele = m_title->parse(*iter);
				assert(ele);
				element->LinkEndChild(ele);
			}
			else if ((*iter_formate).Compare("Details") == 0)
			{
				TiXmlElement* ele_detail = new TiXmlElement("Details");
				/*get the pos of all the keys in data*/
				map<CString,CString>::iterator iter_map = m_keyMap.begin();
				map<int,CString> key_pos;
				vector<int> posArry;
				for (;iter_map!=m_keyMap.end();iter_map++)
				{
					const size_t last_slash_idx = (*iter).Find((*iter_map).first);
					if (last_slash_idx != std::string::npos) {
						key_pos[last_slash_idx] = (*iter_map).second;
						posArry.push_back(last_slash_idx);
					}
				}
				sort(posArry.begin(), posArry.end());

				if (!posArry.empty()) {
					if (posArry[0] > 10) {
						TiXmlElement* ele_ex = new TiXmlElement("Note");
						ele_ex->LinkEndChild(new TiXmlText((*iter).Left(posArry[0])));
						assert(ele_ex);
						element->LinkEndChild(ele_ex);
					}
				}	

				vector<int>::iterator iter_pos = posArry.begin();
				map<int, CString>::iterator iter_key;
				for (; iter_pos != posArry.end(); iter_pos++) {
					iter_key = key_pos.find(*iter_pos);
					assert(iter_key != key_pos.end());

					CString data;
					if (iter_pos + 1 != posArry.end())
						data = (*iter).Mid(*iter_pos, *(iter_pos + 1) - *iter_pos);
					else
						data = (*iter).Right((*iter).GetLength() - *iter_pos);

					RemoveCharacteristic(data);

					TiXmlElement* ele = new TiXmlElement((*iter_key).second);
					ele->LinkEndChild(new TiXmlText(data));

					ele_detail->LinkEndChild(ele);
				}
				element->LinkEndChild(ele_detail);
			}
		}
		if(element->FirstChild())
			m_vElement.push_back(element);
	}
	m_vItems.clear();
}

void PraseCenter::saveXMl2File(CString &fileName)
{
	TiXmlDocument *doc = new TiXmlDocument;
	TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "", "");
	doc->LinkEndChild(decl);
	TiXmlElement* root = new TiXmlElement("root");
	doc->LinkEndChild(root);

	vector<TiXmlElement*>::iterator iter = m_vElement.begin();
	for (; iter != m_vElement.end(); iter++)
	{
		root->LinkEndChild(*iter);
	}

	doc->SaveFile(fileName);
	m_vElement.clear();

	WriteLog("Save Xml file finished. the file path is:");
	WriteLog(fileName);
}

/// <summary>
/// Remove \r \n from CString
/// </summary>
/// <param name="data"></param>
void PraseCenter::RemoveCharacteristic(CString& data)
{
	data.Remove('\t');
	data.Remove('\r');
	data.Remove('\n');

	const size_t last_slash_idx = data.Find("]");

	assert(last_slash_idx!=std::string::npos);

	data = data.Right(data.GetLength() - last_slash_idx);
}
