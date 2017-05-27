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
	strDirecPath.Format(_T(""));
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

	strTestName.Format(_T(""));
	for (int i = 0; i<invPath.size(); i++)
	{
		TestType* cAddData = new TestType;
		CString strDir = invPath[i];
		CString strTemp;
		strTemp.Format(_T("%s%c"),m_strInputDirPath,'\\');
		strDir.Replace(strTemp, _T(""));
		CString strSubDir;
		strSubDir.Format(_T(""));

		AfxExtractSubString(strTestName,strDir,5,'_');

		if (strDir.Find('\\') != -1)
		{
			int nIndex = strDir.Find('\\');
			strSubDir = strDir.Left(nIndex);
			CString strTempTest = strTestName;
			strTestName.Format(_T("%s\\%s"),strSubDir, strTempTest);
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
 }


void ConfigType::SetProject(CString inData)
{
	m_strPrj = inData;
}

void ConfigType::SetBuildNum(CString inData)
{
	m_strBuildNum = inData;
}

void ConfigType::SetConfigNum(CString inData)
{
	m_strConfigNum = inData;
}

void ConfigType::SetDOE(CString inData)
{
	m_strDOE = inData;
}

void ConfigType::LoadDataFiles(CString inStrPath)
{
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError eResult = xmlDoc.LoadFile( LPSTR(LPCTSTR(inStrPath)));

	InitList();

	SearchXMLData(&xmlDoc);

	xmlDoc.Clear();
}


void ConfigType::SearchXMLData(tinyxml2::XMLNode* pParent, int inIndex)
{
	tinyxml2::XMLNode* pNode;
	tinyxml2::XMLElement* pElent;

	for (pNode = (tinyxml2::XMLNode*)pParent->FirstChild(); pNode != 0; pNode = (tinyxml2::XMLNode*)pNode->NextSibling())
	{
		CString strTemp = (CString)pNode->Value();
		if (strTemp == "BaseFile" || strTemp == "BaseInfo")
		{
			continue;
		}
		else
		{
			if(pElent = pNode->ToElement())
			{
				if(inIndex==1)
				{
					TestType* cNewTest = new TestType;
					
					cNewTest->SetTestName((CString)pElent->Value());
					CString strTempValue = (CString)pElent->Value();

					m_vTestName.push_back(strTempValue);

					cNewTest->LoadDataFromXML(pNode);
					std::vector<CString> vTemp;

					cNewTest->GetFileNames(strTempValue,vTemp);

					for (int i = 0; i<vTemp.size(); i++)
					{
						CString strFile;
						CString strDir;

						AfxExtractSubString(strDir, vTemp[i], 2,':');
						if (strDir=="")
						{
							AfxExtractSubString(strFile, vTemp[i], 1,':');
						}
						else
							strFile = strDir;

						m_vBaseFiles.push_back(strFile);
					}
					m_pListTestType.AddTail(cNewTest);
				}
				else
				{
					SearchXMLData(pNode, ++inIndex);
				}
			}
		}
	}
}


BOOL ConfigType::ConfigCompare(ConfigType* inTarget, std::vector<CString>& outFail, CList<CompareResult*>& outDifferent)
{
	CList<TestType*> pListTargetTest;

	// inTarget의 리스트 카피해오기
	inTarget->GetDataList(pListTargetTest);

	// this list 와 inTarget list 비교 수행
	POSITION pThisListPos = m_pListTestType.GetHeadPosition();
	POSITION pTargetListPos = pListTargetTest.GetHeadPosition();
	TestType* pThis;
	TestType* pTarget;

	while(pThisListPos)
	{
		pThis = m_pListTestType.GetNext(pThisListPos);
		pTargetListPos = pListTargetTest.GetHeadPosition();

		while (pTargetListPos)
		{
			pTarget = pListTargetTest.GetNext(pTargetListPos);
			CString strTargetName = pTarget->GetTestName();
			strTargetName.Replace(':','\\');
			if(pThis->GetTestName() == strTargetName)
			{
				CString strTestLog;
				strTestLog.Format(_T("======================  %s Compare Start ====================="), strTargetName);
				outFail.push_back(strTestLog);
				CompareResult* cNewConfig = new CompareResult;
				cNewConfig->SetTestName(strTargetName);
				outDifferent.AddTail(cNewConfig);

				pThis->CompareTest(pTarget, outFail, outDifferent);

				break;
			}
		}
	}
	
	// TestType->Compare 수행
	return TRUE;
}

void ConfigType::GetDataList(CList<TestType*>& outData)
{
	outData.RemoveAll();
	POSITION pPos = m_pListTestType.GetHeadPosition();

	TestType* pTemp;

	while(pPos)
	{
		pTemp = m_pListTestType.GetNext(pPos);
		outData.AddTail(pTemp);
	}
}


void ConfigType::SetRootPath(CString inPath)
{
	m_strInputDirPath = inPath;
}

void ConfigType::SetListLog(ListLog* inData)
{
	m_ListLog = inData;
}
