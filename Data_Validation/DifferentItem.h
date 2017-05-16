#pragma once
class DifferentItem
{
public:
	DifferentItem(void);
	~DifferentItem(void);

private:
	CString m_strTestName;
	CString m_strFileName;
	CString m_strItemName;
	CString m_strBaseInfo;
	CString m_strCurrentInfo;
	BOOL m_bCompareResult;
};

