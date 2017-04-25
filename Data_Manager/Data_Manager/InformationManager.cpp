#include "StdAfx.h"
#include "InformationManager.h"



InformationManager::InformationManager(void)
{
}


InformationManager::~InformationManager(void)
{
	InitAllData();
}

void InformationManager::InitAllData()
{
	POSITION pPos = m_listConfigs.GetHeadPosition();
	POSITION ptemp = NULL;

	while(pPos)
	{
		ptemp = pPos;
		ConfigDMData* pData = m_listConfigs.GetNext(pPos);
		try
		{
			delete pData;
			m_listConfigs.RemoveAt(ptemp);
		}
		catch (CMemoryException* e)
		{
		}
	}

	pPos = m_listSetting.GetHeadPosition();
	while(pPos)
	{
		ptemp = pPos;
		ConfigDMData* pData = m_listSetting.GetNext(pPos);
		
		try
		{
			delete pData;
			m_listSetting.RemoveAt(ptemp);
		}
		catch (CMemoryException* e)
		{
			
		}
	}

	m_listSetting.RemoveAll();
	m_listConfigs.RemoveAll();
}

void InformationManager::AddNewConfigData(ConfigDMData* inNewData)
{
	std::vector<CString> vTest;
	inNewData->GetTestList(vTest);
	inNewData->AddNewTest(m_vBasicFile);

	m_listConfigs.AddTail(inNewData);

	vTest.clear();
}

void InformationManager::AddNewSettingData(ConfigDMData* inNewData)
{
	std::vector<CString> vTest;
	inNewData->GetTestList(vTest);
	int nInput = 0;
	inNewData->AddNewTest(m_vBasicFile, nInput);

	m_listSetting.AddTail(inNewData);

	for(int i = 0; i<vTest.size(); i++)
	{
		vTest.erase(vTest.begin()+i);
	}
	vTest.clear();
}

void InformationManager::DeleteConfigData(ConfigDMData* inTargetData)
{
	POSITION pDelete;
	//pDelete = m_listConfigs.Find(inTargetData); index 로 삭제하게 해야할듯

//	m_listConfigs.RemoveAt(pDelete);
	// add file delete
}

void InformationManager::DeleteConfigData(CString instrPrj, CString instrBuild, CString instrConfig, CString instrDOE)
{
	POSITION pDelete;
	ConfigDMData cTargetData;

	cTargetData.SetProject(instrPrj);
	cTargetData.SetBuildNum(instrBuild);
	cTargetData.SetConfigNum(instrConfig);
	cTargetData.SetDOE(instrDOE);
}

void InformationManager::ModifyConfigData(ConfigDMData* inTargetData)
{

}

bool InformationManager::SaveRefToFile(CString inFilePath)
{
	ConfigDMData* pTemp;
	bool bResult = false;
	if(m_listConfigs.GetCount() > 0)
	{
		pTemp = m_listConfigs.GetHead();

		POSITION pos = m_listConfigs.GetHeadPosition();

		while(pos)
		{
			pTemp = m_listConfigs.GetNext(pos);
			if(pTemp->GetNewDataFlag())
			{
				pTemp->SaveDataToFile(m_vBasicFile);
			}
		}

		pTemp = m_listSetting.GetHead();

		pos = m_listSetting.GetHeadPosition();

		while(pos)
		{
			pTemp = m_listSetting.GetNext(pos);
			if(pTemp->GetNewDataFlag())
			{
				pTemp->SaveSettingToFile(m_vBasicFile);
			}
		}
		pTemp->SetNewDataFlag(false);
		bResult = true;
	}

	return bResult;
}

void InformationManager::LoadBaseFileList()
{
	TCHAR path[_MAX_PATH];

	GetModuleFileName(NULL, path, sizeof path);

	CString strEXEPath = path;
	CString strFilepath;

	int nIndex = strEXEPath.ReverseFind('\\');//실행 파일 이름을 지우기 위해서 왼쪽에 있는 '/'를 찾는다.

	strEXEPath = strEXEPath.Left(nIndex);//뒤에 있는 현재 실행 파일 이름을 지운다.

	strFilepath.Format(_T("%s%s"), strEXEPath,"\\Data\\BaseFile.xml" );

	tinyxml2::XMLDocument cDoc;

	
	if(tinyxml2::XML_SUCCESS == cDoc.LoadFile( LPSTR(LPCTSTR(strFilepath))))
	{
		tinyxml2::XMLNode* pNode;
		tinyxml2::XMLNode* pNode2;

		tinyxml2::XMLElement* pElem;
		tinyxml2::XMLElement* pElem2;
	
		for (pNode = (tinyxml2::XMLNode*)cDoc.FirstChild(); pNode != 0; pNode = (tinyxml2::XMLNode*)pNode->NextSibling())
		{
			if(pElem = pNode->ToElement())
			{
 				for (pNode2 = (tinyxml2::XMLNode*)pElem->FirstChild(); pNode2 != 0; pNode2 = (tinyxml2::XMLNode*)pNode2->NextSibling())
 				{
					if(pElem2 = pNode2->ToElement())
					{
						m_vBasicFile.push_back((CString)pElem2->GetText());
					}
				}
			}
		}
	}
	else
	{
		m_vBasicFile.push_back(_T("Spec.ini"));
		m_vBasicFile.push_back(_T("ItemVersion.ini"));
		m_vBasicFile.push_back(_T("OS2.spc"));
		m_vBasicFile.push_back(_T("OSLeakage.spc"));

		tinyxml2::XMLElement* pElem;
		tinyxml2::XMLElement* pElem2;
		tinyxml2::XMLText* text;

		pElem = cDoc.NewElement("BaseFile");
	
		
		CString strTemp;
		for (int i = 0; i<m_vBasicFile.size(); i++)
		{
			pElem2 = cDoc.NewElement("File");
			text = cDoc.NewText( LPSTR(LPCTSTR(m_vBasicFile[i])));

			pElem2->LinkEndChild(text);
			pElem->LinkEndChild(pElem2);
			
		}
		cDoc.LinkEndChild(pElem);		
		cDoc.SaveFile(LPSTR(LPCTSTR(strFilepath)));
	}
}

void InformationManager::LoadXMLFileListInValue()
{
	ConfigDMData cTempConfig;

	CString strEXEDirectory;

	m_vConfigName.clear();

	strEXEDirectory = cTempConfig.GetEXEDirectoryPath();

	strEXEDirectory += "\\Data\\Value";

	SetCurrentDirectory(strEXEDirectory); //현재 검색할 디렉터리 설정.

	CFileFind finder;

	std::vector<CString> vStrFilePath;
	std::vector<CString> vDummy;

	cTempConfig.GetDirList(strEXEDirectory,vDummy, vStrFilePath);

	CString strPrj, strBuild, strConfig, strDOE;

	for (int i = 0; i < vStrFilePath.size(); i++)
	{
		//ConfigDMData* pAddConfig = new ConfigDMData;

		ParsingBBCD(vStrFilePath[i], strPrj, strBuild, strConfig, strDOE);

// 		pAddConfig->SetProject(strPrj);
// 		pAddConfig->SetBuildNum(strBuild);
// 		pAddConfig->SetConfigNum(strConfig);
// 		pAddConfig->SetDOE(strDOE);

		CString strComb = strPrj + '_'+ strBuild + '_' + strConfig + '_' + strDOE;

		m_vConfigName.push_back(strComb);

		//delete pAddConfig;
	}
}

void InformationManager::LoadXMLFileListInSetting()
{
	ConfigDMData cTempConfig;

	CString strEXEDirectory;

	strEXEDirectory = cTempConfig.GetEXEDirectoryPath();

	strEXEDirectory += "\\Data\\Setting";

	SetCurrentDirectory(strEXEDirectory); //현재 검색할 디렉터리 설정.

	CFileFind finder;

	std::vector<CString> vStrFilePath;
	std::vector<CString> vDummy;

	cTempConfig.GetDirList(strEXEDirectory,vDummy, vStrFilePath);

	CString strPrj, strBuild, strConfig, strDOE;

	for (int i = 0; i < vStrFilePath.size(); i++)
	{
		//ConfigDMData* pAddConfig = new ConfigDMData;

		ParsingBBCD(vStrFilePath[i], strPrj, strBuild, strConfig, strDOE);

// 		pAddConfig->SetProject(strPrj);
// 		pAddConfig->SetBuildNum(strBuild);
// 		pAddConfig->SetConfigNum(strConfig);
// 		pAddConfig->SetDOE(strDOE);

		CString strComb = strPrj + '_'+ strBuild + '_' + strConfig + '_' + strDOE;

		//m_vConfigName.push_back(strComb);

		//delete pAddConfig;
	}
}

void InformationManager::LoadXMLValueFileList(CString inData)
{
	ConfigDMData* pAddConfig = new ConfigDMData;

	pAddConfig->LoadDataFiles(inData);

	CString strPrj, strBuild, strConfig, strDOE;

	ParsingBBCD(inData, strPrj, strBuild, strConfig, strDOE);

	pAddConfig->SetProject(strPrj);
	pAddConfig->SetBuildNum(strBuild);
	pAddConfig->SetConfigNum(strConfig);
	pAddConfig->SetDOE(strDOE);

	CString strComb = strPrj+'_'+strBuild+'_'+strConfig+'_'+strDOE;

	m_vConfigName.push_back(strComb);

	m_listConfigs.AddTail(pAddConfig);

	delete pAddConfig;
}

void InformationManager::LoadXMLSettingFileList(CString inData)
{
	ConfigDMData* pAddConfig = new ConfigDMData;

	pAddConfig->LoadDataFiles(inData);

	CString strPrj, strBuild, strConfig, strDOE;

	ParsingBBCD(inData, strPrj, strBuild, strConfig, strDOE);

	pAddConfig->SetProject(strPrj);
	pAddConfig->SetBuildNum(strBuild);
	pAddConfig->SetConfigNum(strConfig);
	pAddConfig->SetDOE(strDOE);

	CString strComb = strPrj+'_'+strBuild+'_'+strConfig+'_'+strDOE;

	//m_vConfigName.push_back(strComb);

	m_listSetting.AddTail(pAddConfig);

	delete pAddConfig;
}

void InformationManager::ParsingBBCD(CString inStr, CString& outStrPrj, CString& outStrBuild, CString& outStrConfig, CString& outStrDOE)
{
	int nIndex = inStr.ReverseFind('\\');
	CString strFileName = inStr.Mid((nIndex+1));
	CString strTemp = inStr.Left(nIndex);
	
	AfxExtractSubString(outStrBuild,	strFileName,0,'-');
	AfxExtractSubString(outStrConfig,	strFileName,1,'-');
	nIndex = strFileName.Find('-',0);
	nIndex = strFileName.Find('-',nIndex+1);
	outStrDOE = strFileName.Mid(nIndex+1);
	AfxExtractSubString(outStrDOE,		outStrDOE,0,'.');

	nIndex = strTemp.ReverseFind('\\');
	outStrPrj = strTemp.Mid(nIndex+1);
}

void InformationManager::GetConfigNameList(std::vector<CString>& outvData)
{
	outvData.clear();
	outvData = m_vConfigName;
}