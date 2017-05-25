#pragma once
class CompareResult
{
public:
	CompareResult(void);
	~CompareResult(void);
	void SetTestName(CString inData);
	void SetFileName(CString inData);
	void SetItemName(CString inData);
	void SetBaseInfoValue(CString inData);
	void SetCurrentInfoValue(CString inData);
	void SetConfigInfo(CString inData);
	void SetCompareResult(BOOL inData);
	
	CString GetTestName();
	CString GetFileName();
	CString GetItemName();
	CString GetBaseInfoValue();
	CString GetCurrentInfoValue();
	CString GetConfigInfo();
	BOOL GetCompareResult();
private:
	CString m_strTestName;
	CString m_strFileName;
	CString m_strItemName;
	CString m_strBaseInfoValue;
	CString m_strCurrentInfoValue;
	CString m_strConfig;
	BOOL m_bCompareResult;
};

