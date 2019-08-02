#pragma once
#include "reportitem.h"
class ReportList :
	public ReportItem
{
public:
	ReportList(void);
	~ReportList(void);

	virtual void SetValueByPraseNode(TiXmlNode *node);

	CString GetSplite(){ return m_spilt; }
	void SetSplite(CString split){ m_spilt =  split; }

private:
	CString m_spilt;
};

