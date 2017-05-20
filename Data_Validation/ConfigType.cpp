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

	InitListAndVectors();

	SearchXMLData(&xmlDoc);
}


void ConfigType::InitListAndVectors()
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

void ConfigType::SearchXMLData(tinyxml2::XMLNode* pParent, int inIndex)
{
	tinyxml2::XMLNode* pNode;
	tinyxml2::XMLElement* pElent;

	for (pNode = (tinyxml2::XMLNode*)pParent->FirstChild(); pNode != 0; pNode = (tinyxml2::XMLNode*)pNode->NextSibling())
	{
		CString strTemp = (CString)pNode->Value();
		if (strTemp == "BaseFile" || strTemp == "File")
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
					CString strTempValue = pElent->Value();

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