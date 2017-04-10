#include "StdAfx.h"
#include "ConfigDMData.h"


ConfigDMData::ConfigDMData(void)
{
	m_bNewData = false;
}


ConfigDMData::~ConfigDMData(void)
{
	for(int i = 0; i<m_vTestDirPath.size(); i++)
	{
		m_vTestDirPath.erase(m_vTestDirPath.begin()+i);
	}
	for(int i = 0; i<m_vTestName.size(); i++)
	{
		m_vTestName.erase(m_vTestName.begin()+i);
	}
// 	for(int i = 0; i<m_vFilePath.size(); i++)
// 	{
// 		m_vFilePath.erase(m_vFilePath.begin()+i);
// 	}
	m_vTestDirPath.clear();
	m_vTestName.clear();
	//m_vFilePath.clear();
	
	
	POSITION pTemp = NULL;
	POSITION pPos = m_pListTestType.GetHeadPosition();

	while(pPos)
	{
		pTemp = pPos;
		TestType* temp = m_pListTestType.GetNext(pPos);
		delete temp;
		m_pListTestType.RemoveAt(pTemp);
		
	}
	
	m_pListTestType.RemoveAll();
}

void ConfigDMData::RefNameParsing(CString instrData)
{
	CString strProject, strConfig, strDOE, strTest;

	AfxExtractSubString(strProject, instrData, 0, '_');
	AfxExtractSubString(strConfig,  instrData, 4, '_');
	AfxExtractSubString(strTest,	instrData, 5, '_');
	AfxExtractSubString(strDOE,		instrData, 6, '_');
}

void ConfigDMData::GetDirList(CString instrPath, std::vector<CString>& inVDirList,  std::vector<CString>& inVFileList)
{
	SetCurrentDirectory(instrPath); //���� �˻��� ���͸� ����.

	CFileFind finder;

	BOOL bWorking = finder.FindFile();
	CString DirName;
	CString fileName;

	while (bWorking)
	{
		//���� ����or������ �����ϸ�ٸ� TRUE ��ȯ
		bWorking = finder.FindNextFile();

		//���͸� �϶�
		if (finder.IsDirectory() && !finder.IsDots())
		{
			DirName = finder.GetFilePath();
			GetDirList(DirName, inVDirList, inVFileList);
		}
		if (finder.IsDirectory() && finder.IsDots() == false )
		{
			inVDirList.push_back(DirName);
		}
		if (finder.IsArchived())
		{
			fileName = finder.GetFilePath();
			inVFileList.push_back(fileName);
		}
	}
}

void ConfigDMData::GetConfigInfoFromVector(std::vector<CString> invData, CString inRootPath, CString& outPrj, CString& outBuild, CString& outConfig, CString& outDOE)
{
	inRootPath+="\\";

	CString temp;

	for(int i = 0; i<(signed)invData.size(); i++)
	{
		invData[i].Replace(inRootPath,_T(""));

		if(invData[i].FindOneOf(_T("\\")) == -1 && invData[i].FindOneOf(_T("Dark")) != -1)
		{
			AfxExtractSubString(outPrj,		invData[i], 0, '_');
			AfxExtractSubString(outConfig,	invData[i], 4, '_');
			AfxExtractSubString(outBuild,	invData[i], 4, '_');
			AfxExtractSubString(outDOE,		invData[i], 6, '_');
			AfxExtractSubString(temp,		invData[i], 7, '_');

			if(temp=="")
				outDOE = "Main Build";

			outBuild = outBuild.Left(3);
			outBuild.Insert(2,'.');

			break;
		}
	}

	for (int i= 0; i< invData.size(); i++)
	{
		invData.erase(invData.begin()+i);
	}
	invData.clear();
}

void ConfigDMData::SetBuildNum(CString inData)
{
	m_strBuildNum = inData;
}

void ConfigDMData::SetConfigNum(CString inData)
{
	m_strConfigNum = inData;
}

void ConfigDMData::SetProject(CString inData)
{
	m_strPrj = inData;
}

void ConfigDMData::SetDOE(CString inData)
{
	m_strDOE = inData;
}

bool ConfigDMData::operator ==(const ConfigDMData& inData)
{
	bool bResult= false;

	if (inData.m_strBuildNum == this->m_strBuildNum && inData. m_strConfigNum == this->m_strConfigNum &&
		inData.m_strDOE == this->m_strDOE && inData.m_strPrj == this->m_strPrj)
	{
		bResult = true;
	}

	return bResult;
}

CString ConfigDMData::GetBuildNum()
{
	return m_strBuildNum;
}

// void ConfigDMData::operator =(const ConfigDMData& inData)
// {
// 	m_strBuildNum	= inData.m_strBuildNum;
// 	m_strPrj		= inData.m_strPrj;
// 	m_strConfigNum	= inData.m_strConfigNum;
// 	m_strDOE		= inData.m_strDOE;
// 	
// 	m_vTestDirPath.clear();
// 	m_vTestDirPath.assign(inData.m_vTestDirPath.begin(), inData.m_vTestDirPath.end());
// }

void ConfigDMData::GetTestDirFromVector(std::vector<CString> invData, std::vector<CString>& outvData, CString inRootPath)
{
	inRootPath+="\\";
	
	for (INT i= 0 ; i<invData.size(); i++)
	{
		CString temp = invData[i];
		
		temp.Replace(inRootPath,_T(""));

		outvData.push_back(temp);
	}
	for (int i= 0; i< invData.size(); i++)
	{
		invData.erase(invData.begin()+i);
	}
	invData.clear();
}

void ConfigDMData::GetTestNameFromDirVector(std::vector<CString> invData, std::vector<CString>& outvData)
{
	for (INT i= 0 ; i<invData.size(); i++)
	{
		CString temp = invData[i];
		CString temp2 = "";

		if(temp.Find('\\') == -1)
		{
			AfxExtractSubString(temp,		invData[i], 5, '_');
			AfxExtractSubString(temp2,		invData[i], 8, '_');
			if (temp2 != "")
			{
				temp = temp2 +'\\'+ temp;
			}
		}
		else
		{
			AfxExtractSubString(temp2,		invData[i], 0, '\\');
			AfxExtractSubString(temp,		invData[i], 1, '\\');
			AfxExtractSubString(temp,		temp, 5, '_');
			temp = temp2 +'\\'+ temp;
		}
		if(temp!="")
			outvData.push_back(temp);
	}
	for (int i= 0; i< invData.size(); i++)
	{
		invData.erase(invData.begin()+i);
	}
	invData.clear();
}

void ConfigDMData::SetTestList(std::vector<CString> invData)
{
	CString temp;
	for (int i = 0; i < invData.size(); i++)
	{
		temp = invData[i];
		m_vTestName.push_back(temp);
	}
	for (int i= 0; i< invData.size(); i++)
	{
		invData.erase(invData.begin()+i);
	}
	invData.clear();
}

void ConfigDMData::SetTestDirList(std::vector<CString> invData)
{
	CString temp;
	for (int i = 0; i < invData.size(); i++)
	{
		temp = invData[i];
		m_vTestDirPath.push_back(temp);
	}
	for (int i= 0; i< invData.size(); i++)
	{
		invData.erase(invData.begin()+i);
	}
	invData.clear();
}

void ConfigDMData::AddNewTest()
{
	CString strTestName;

	for (int i = 0; i<m_vTestDirPath.size(); i++)
	{
		TestType* cAddData = new TestType;
		int nIndex = m_vTestDirPath[i].ReverseFind('\\');
		CString strDir = m_vTestDirPath[i];
		strDir = strDir.Mid(nIndex+1);
		CString strIndex9th="";

		AfxExtractSubString(strTestName,strDir,5,'_');
		AfxExtractSubString(strIndex9th,strDir,8,'_');

		if(strIndex9th != "" && strTestName != "")
		{
			strTestName = strIndex9th + "\\" + strTestName;
		}

		cAddData->SetTestName(strTestName);
		cAddData->AddNewTest(m_vTestDirPath[i]);
		
		m_pListTestType.AddTail(cAddData);
	}
}

void ConfigDMData::GetFilePathInDir(std::vector<CString> invPath, std::vector<CString>& outvData)
{
	CFileFind finder;

	CString fileName;
	CString tpath;

	for (int i=0; i<invPath.size(); i++)
	{
		tpath = invPath[i];
		tpath+= "\\*.*";

		BOOL bWorking = finder.FindFile(tpath);

		while (bWorking)
		{
			bWorking = finder.FindNextFile();
			//���� �϶�
			if (finder.IsArchived())
			{
				//������ �̸�
				CString _fileName =  finder.GetFileName();

				// �������� �������� ����������� ����
				if( _fileName == _T(".") ||
					_fileName == _T("..")||
					_fileName == _T("Thumbs.db") ) continue;

				fileName =  finder.GetFilePath();
				outvData.push_back(fileName);
			}
		}
	}
	finder.Close();
	for (int i= 0; i< invPath.size(); i++)
	{
		invPath.erase(invPath.begin()+i);
	}
	invPath.clear();
}

void ConfigDMData::SetFilePath(std::vector<CString> invPath)
{
// 	m_vFilePath.clear();
// 	m_vFilePath.assign(invPath.begin(), invPath.end());
// 
// 	for (int i= 0; i< invPath.size(); i++)
// 	{
// 		invPath.erase(invPath.begin()+i);
// 	}
	invPath.clear();
}

void ConfigDMData::GetTestList(std::vector<CString>& outvPath)
{
	outvPath.clear();
	outvPath.assign(m_vTestName.begin(), m_vTestName.end());
}

void ConfigDMData::GetDirPathList(std::vector<CString>& outvPath)
{
	outvPath.clear();
	outvPath.assign(m_vTestDirPath.begin(), m_vTestDirPath.end());
}

void ConfigDMData::SaveDataToFile(std::vector<CString> invBasicFile)
{
    CString strEXEPath;

	strEXEPath = GetEXEDirectoryPath();

 	CString strFilePath = strEXEPath + "\\Data\\" + m_strPrj;

	CreateDirectory(strFilePath,NULL);

	strFilePath += "\\"+ m_strBuildNum + "-" + m_strConfigNum + "-" + m_strDOE +".xml";

	char* strTemp = (LPSTR)strFilePath.GetBuffer(0);

 	tinyxml2::XMLDocument cXMLDocument;
	tinyxml2::XMLDeclaration* dexl = cXMLDocument.NewDeclaration();

	cXMLDocument.LinkEndChild(dexl);

	tinyxml2::XMLElement* pElemenet = cXMLDocument.NewElement("Value");

	cXMLDocument.LinkEndChild(pElemenet);

	POSITION pos = m_pListTestType.GetHeadPosition();

//	AddCommonBaseFile(invBasicFile);		// Ref ���Ͽ� �⺻ ���ϵ� �߰�

	while(pos)
	{
		TestType* pData = m_pListTestType.GetNext(pos);
		pData->SaveDataToFile(cXMLDocument, pElemenet, m_vBaseFiles);
	}
	
	cXMLDocument.SaveFile(strTemp);
	
	SetNewDataFlag(false);
}

void ConfigDMData::SetNewDataFlag(bool inData)
{
	m_bNewData = inData;
}

bool ConfigDMData::GetNewDataFlag()
{
	return m_bNewData;
}

void ConfigDMData::AddCommonBaseFile(std::vector<CString> invFileName)
{
	for(int i=0; i<invFileName.size(); i++)
	{
		m_vBaseFiles.push_back(invFileName[i]); 
	}
}

void ConfigDMData::SetBaseFiles(std::vector<CString> invFileName)
{
	m_vBaseFiles.clear();
	CString strTemp;

	for (int i=0; i<invFileName.size(); i++)
	{
		strTemp.Format("%s%s", invFileName[i], ".ini");
		m_vBaseFiles.push_back(strTemp);
	}
	
}

CString ConfigDMData::GetEXEDirectoryPath()
{
	CString strDirecPath;
	TCHAR path[_MAX_PATH];

	GetModuleFileName(NULL, path, sizeof path);

	strDirecPath = path;

	int i = strDirecPath.ReverseFind('\\');//���� ���� �̸��� ����� ���ؼ� ���ʿ� �ִ� '/'�� ã�´�.

	strDirecPath = strDirecPath.Left(i);//�ڿ� �ִ� ���� ���� ���� �̸��� �����.

	return strDirecPath;
}

void ConfigDMData::LoadDataFiles(CString inStrPath)
{
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError eResult = xmlDoc.LoadFile(inStrPath);

	SearchXMLData(&xmlDoc);
}

void ConfigDMData::SearchXMLData(tinyxml2::XMLNode* pParent, int inIndex)
{
	tinyxml2::XMLNode* pNode;
	tinyxml2::XMLElement* pElent;

	for (pNode = (tinyxml2::XMLNode*)pParent->FirstChild(); pNode != 0; pNode = (tinyxml2::XMLNode*)pNode->NextSibling())
	{
		if(pElent = pNode->ToElement())
		{
			if(inIndex==1)
			{
				TestType* cNewTest = new TestType;

				cNewTest->SetTestName(pElent->Value());

				cNewTest->LoadDataFromXML(pNode);
				m_pListTestType.AddTail(cNewTest);
			}
			else
			{
				SearchXMLData(pNode, ++inIndex);
			}
		}
	}
}

