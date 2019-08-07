#pragma once
#include <vector>
#include <string>
#include <memory>
#include <map>
#include "TempletePraser.h"

class TiXmlElement;
class ReportTitle;
class PraseCenter
{
public:
	PraseCenter(void);
	~PraseCenter(void);

	void SetLogReceiver(HWND hWnd) { m_hWnd = hWnd; }

	std::vector<CString> LoadDataFiles();

	CString LoadTempleteFile();

	CString SetSaveFilePath();

	void SetMultipleDataSplit(CString split){ m_itemSplit = split; }

	void SetDataFileType(bool isMultiple){  m_isMultiple = isMultiple; }

	bool ParseDataFiles();

	void SetTitleValue(std::shared_ptr<ReportTitle> ptr) { m_title = ptr; }

	void AddParagraph(CString &key, CString &name);

	void AddFileFormat(CString paragraph);

	void WriteLog(CString log);

private:
	void ClearLastTempleteData();

	void PraseFile(CString &fileName);

	void PraseFileData();

	void saveXMl2File(CString &fileName);

	void RemoveSpecialCharacter(CString& data);

private:
	HWND m_hWnd;

	std::vector<CString> m_vDataFiles;

	CString m_templeteFile;

	CString m_saveFile;

	CString m_itemSplit;

	bool m_isMultiple;

	TempletePraser m_xmlPraser;

	std::shared_ptr<ReportTitle> m_title;

	std::map<CString,CString> m_keyMap;

	std::vector<CString> m_vFormat;

	std::vector<TiXmlElement *> m_vElement;

	std::vector<CString> m_vItems;
};

