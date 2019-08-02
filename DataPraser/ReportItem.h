#pragma once
#include "reportparagraph.h"
class ReportItem :
	public ReportParagraph
{
public:
	ReportItem(void);
	~ReportItem(void);

	virtual void SetValueByPraseNode(TiXmlNode *node);

	CString GetStart(){ return m_start; }
	void SetStart(CString start){ m_start =  start; }

	CString GetEnd(){ return m_end; }
	void SetEnd(CString end){ m_end =  end; }

private:
	CString m_start;
	CString m_end;
};

