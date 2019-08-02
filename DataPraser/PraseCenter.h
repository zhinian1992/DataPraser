#pragma once
#include <vector>
#include <string>
#include <memory>
#include "TempletePraser.h"


class ReportParagraph;
class PraseCenter
{
public:
	PraseCenter(void);
	~PraseCenter(void);

	void SetLogReceiver(HWND hWnd) { m_hWnd = hWnd; }

	std::vector<CString> LoadDataFiles();

	CString LoadTempleteFile();

	CString SetSaveFilePath();

	void SetMultipleDataSplit(CString split){ m_split = split; }

	void SetDataFileType(bool isMultiple){  m_isMultiple = isMultiple; }

	bool ParseDataFiles();

	void AddParagraph(std::shared_ptr<ReportParagraph> &elem);

	void WriteLog(CString log);

private:
	void ClearChild();

private:
	HWND m_hWnd;

	std::vector<CString> m_vDataFiles;

	CString m_templeteFile;

	CString m_saveFile;

	CString m_split;

	bool m_isMultiple;

	std::vector<std::shared_ptr<ReportParagraph>> m_vChild;
	
	TempletePraser m_xmlPraser;
};

