#include "StdAfx.h"
#include "CompareResult.h"


CompareResult::CompareResult(void)
{
	m_strTestName.Format("");
	m_strFileName.Format("");
	m_strItemName.Format("");
	m_strBaseInfoValue.Format("");
	m_strCurrentInfoValue.Format("");
	m_strConfig.Format("");
	m_bCompareResult = FALSE;
}


CompareResult::~CompareResult(void)
{
}


void CompareResult::SetTestName(CString inData)
{
	m_strTestName = inData;
}
void CompareResult::SetFileName(CString inData)
{
	m_strFileName = inData;
}
void CompareResult::SetItemName(CString inData)
{
	m_strItemName = inData;
}
void CompareResult::SetBaseInfoValue(CString inData)
{
	m_strBaseInfoValue = inData;
}
void CompareResult::SetCurrentInfoValue(CString inData)
{
	m_strCurrentInfoValue = inData;
}
void CompareResult::SetConfigInfo(CString inData)
{
	m_strConfig = inData;
}

void CompareResult::SetCompareResult(BOOL inData)
{
	m_bCompareResult = inData;
}


CString CompareResult::GetTestName()
{
	return m_strTestName;
}
CString CompareResult::GetFileName()
{
	return m_strFileName;
}
CString CompareResult::GetItemName()
{
	return m_strItemName;
}
CString CompareResult::GetBaseInfoValue()
{
	return m_strBaseInfoValue;
}
CString CompareResult::GetCurrentInfoValue()
{
	return m_strCurrentInfoValue;
}
CString CompareResult::GetConfigInfo()
{
	return m_strConfig;
}
BOOL CompareResult::GetCompareResult()
{
	return m_bCompareResult;
}