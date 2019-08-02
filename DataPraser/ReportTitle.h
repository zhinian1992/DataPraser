#pragma once
#include "reportparagraph.h"

class ReportTitle :
	public ReportParagraph
{
public:
	ReportTitle(void);
	~ReportTitle(void);

	virtual void SetValueByPraseNode(TiXmlNode *node);

	CString GetSplite(){ return m_spilt; }
	void SetSplite(CString split){ m_spilt =  split; }

private:
	CString m_spilt;
};

