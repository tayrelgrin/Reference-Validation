#include "StdAfx.h"
#include "ConfigType.h"


ConfigType::ConfigType(void)
{
}


ConfigType::~ConfigType(void)
{
	InitList();
}


CString ConfigType::GetEXEDirectoryPath()
{
	CString strDirecPath;
	strDirecPath.Format("");
	TCHAR path[_MAX_PATH];

	GetModuleFileName(NULL, path, sizeof path);

	strDirecPath = path;

	int i = strDirecPath.ReverseFind('\\');//실행 파일 이름을 지우기 위해서 왼쪽에 있는 '/'를 찾는다.

	strDirecPath = strDirecPath.Left(i);//뒤에 있는 현재 실행 파일 이름을 지운다.

	return strDirecPath;
}

void ConfigType::AddNewTest(std::vector<CString> invPath, int inNInput)
{
	CString strTestName;
	CString strIndex8th;
	strIndex8th.Format("");
	strTestName.Format("");
	for (int i = 0; i<invPath.size(); i++)
	{
		TestType* cAddData = new TestType;
		int nIndex = invPath[i].ReverseFind('\\');
		CString strDir = invPath[i];
		strDir = strDir.Mid(nIndex+1);
		CString strIndex9th;
		strIndex9th.Format("");

		AfxExtractSubString(strTestName,strDir,5,'_');
		AfxExtractSubString(strIndex8th,strDir,7,'_');
		AfxExtractSubString(strIndex9th,strDir,8,'_');

		if (strIndex9th=="" && strIndex8th != "")
		{
			if(strIndex8th.Find('-') != -1)
				strIndex9th = strIndex8th;
		}

		if(strIndex9th != "" && strTestName != "")
		{
			strTestName = strIndex9th + "\\" + strTestName;
		}

		cAddData->SetTestName(strTestName);
		cAddData->AddNewTest(invPath[i],m_vBaseFiles, inNInput);

		m_pListTestType.AddTail(cAddData);
	}

}

void ConfigType::InitList()
{
	POSITION pTemp = NULL;
	POSITION pPos = m_pListTestType.GetHeadPosition();

	while(pPos && m_pListTestType.GetSize()>0)
	{
		pTemp = pPos;
	
		TestType* temp = m_pListTestType.GetNext(pPos);
		delete temp;
		m_pListTestType.RemoveAt(pTemp);
	}

	pTemp = NULL;
	pPos = m_pListBaseInfo.GetHeadPosition();

	while(pPos && m_pListBaseInfo.GetSize()>0)
	{
		pTemp = pPos;

		BasicData* temp = m_pListBaseInfo.GetNext(pPos);
		delete temp;
		m_pListBaseInfo.RemoveAt(pTemp);
	}
}