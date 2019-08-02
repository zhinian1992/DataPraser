#pragma once
#include <memory>
#include <vector>

class TiXmlNode;
class PraseCenter;
class ReportParagraph;
class TempletePraser
{
private:
	PraseCenter &m_praseCenter;
public:
	TempletePraser(PraseCenter &praseCenter);
	~TempletePraser(void);

	bool PraseTempleteFile(CString &file);

};

