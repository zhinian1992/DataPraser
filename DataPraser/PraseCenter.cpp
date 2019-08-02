#include "stdafx.h"
#include "PraseCenter.h"
#include "ReportParagraph.h"
#include <windows.h>
#include <iostream>
#include <fstream>

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
		if(m_vChild.empty()){
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

	if(m_vChild.empty()){
		WriteLog("Error:please load templete files befor prasing!");
		return false;
	}

	vector<CString>::iterator iter = m_vDataFiles.begin();
	while(iter!=m_vDataFiles.end()){
		CFile file;
		if(!file.Open(*iter,CFile::modeReadWrite)){
			WriteLog("Error:open data files failed! the file name is:");
			WriteLog(*iter);
			iter++;
			continue;
		}
		DWORD len=file.GetLength();
		char* buffer = NULL;
		buffer = new char[len + 1];
		buffer[len] = '\0';
		
		file.Read(buffer,len);
		file.Close();

		CString sContent = buffer;

		delete[] buffer;
		buffer = NULL;
	}
	return true;
}

/// <summary>
/// Add paragraph detail to vector
/// </summary>
/// <param name="elem">ReportParagraph node</param>
void PraseCenter::AddParagraph(std::shared_ptr<ReportParagraph> &elem)
{
	assert(elem);

	m_vChild.push_back(elem);
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
void PraseCenter::ClearChild()
{
	m_vChild.clear();
}
