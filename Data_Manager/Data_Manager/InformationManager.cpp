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

	m_listSetting.RemoveAll();
	m_listConfigs.RemoveAll();
	m_listBaseInfo.RemoveAll();
}

void InformationManager::AddNewConfigData(ConfigDMData* inNewData)
{
	inNewData->AddNewTest(m_vBasicFile);

	m_listConfigs.AddTail(inNewData);
}

void InformationManager::AddNewSettingData(ConfigDMData* inNewData)
{
	int nInput = 0;
	inNewData->AddNewTest(m_vBasicFile, nInput);

	m_listSetting.AddTail(inNewData);
}


bool InformationManager::SaveRefToFile()
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
				pTemp->SaveSettingToFile(m_vBasicFile, &m_listBaseInfo);
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
	strFilepath.Format("");

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
		strTemp.Format("");
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
	strEXEDirectory.Format("");

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
		ParsingBBCD(vStrFilePath[i], strPrj, strBuild, strConfig, strDOE);

		CString strComb = strPrj + '_'+ strBuild + '_' + strConfig + '_' + strDOE;

		m_vConfigName.push_back(strComb);
	}
}

void InformationManager::LoadXMLFileListInSetting()
{
	ConfigDMData cTempConfig;

	CString strEXEDirectory;
	strEXEDirectory.Format("");

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
		ParsingBBCD(vStrFilePath[i], strPrj, strBuild, strConfig, strDOE);

		CString strComb = strPrj + '_'+ strBuild + '_' + strConfig + '_' + strDOE;
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

	strPrj.Format("");
	strBuild.Format("");
	strConfig.Format("");
	strDOE.Format("");

	ParsingBBCD(inData, strPrj, strBuild, strConfig, strDOE);

	pAddConfig->SetProject(strPrj);
	pAddConfig->SetBuildNum(strBuild);
	pAddConfig->SetConfigNum(strConfig);
	pAddConfig->SetDOE(strDOE);

	CString strComb = strPrj+'_'+strBuild+'_'+strConfig+'_'+strDOE;

	pAddConfig->GetBaseInfoList(m_listBaseInfo);

	m_listSetting.AddTail(pAddConfig);

	delete pAddConfig;
}

void InformationManager::SetBaseInfoFromConfig(const CList<BasicData*>& outList)
{
	if(m_listBaseInfo.GetCount() > 0)
	{
		m_listBaseInfo.RemoveAll();
	}

	POSITION pPos = outList.GetHeadPosition();

	while(pPos)
	{
		BasicData* cTemp = outList.GetNext(pPos);
		m_listBaseInfo.AddTail(cTemp);
	}
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

TestType* InformationManager::SearchSettingData(TestType& inoutTarget, bool& bResult)
{
	bResult = false;
	POSITION pPos = m_listSetting.GetTailPosition();
	POSITION ptemp = NULL;
	TestType* temp = &inoutTarget;
	while(pPos)
	{
		ptemp = pPos;
		ConfigDMData* pData = m_listSetting.GetNext(pPos);
		temp = pData->SearchTest(*temp, bResult);
	}

	return temp;
}

void InformationManager::GetBaseInfo(FileType& inFileData)
{
	inFileData.InitList();

	POSITION pPos = m_listBaseInfo.GetHeadPosition();
	POSITION ptemp = NULL;
	
	while(pPos)
	{
		BasicData* pData = m_listBaseInfo.GetNext(pPos);
		inFileData.AddNewData(pData);
	}
}

void InformationManager::AddNewBaseInfo(BasicData& inData)
{
	m_listBaseInfo.AddTail(&inData);
}

void InformationManager::InitBaseInfo()
{
	m_listBaseInfo.RemoveAll();
}

void InformationManager::ModifyConfigData(CString inTargetTest,CString inTargetFileName, BasicData* inTarget)
{
	POSITION pPos = m_listConfigs.GetHeadPosition();

	while(pPos)
	{
		ConfigDMData* temp = m_listConfigs.GetNext(pPos);

		temp->ModifyData(inTargetTest, inTargetFileName, inTarget);
	}
}

void InformationManager::ModifySettingData(CString inTargetTestName, CString inTargetFileName, BasicData* inTarget)
{
	POSITION pPos = m_listSetting.GetHeadPosition();

	while(pPos)
	{
		ConfigDMData* temp = m_listSetting.GetNext(pPos);

		temp->ModifyData(inTargetTestName,inTargetFileName, inTarget);
	}
}

void InformationManager::ModifyBaseInfoData(CString inTargetTestName, CString inTargetFileName, BasicData* inTarget)
{
	POSITION pPos = m_listBaseInfo.GetHeadPosition();

	while(pPos)
	{
		BasicData* temp = m_listBaseInfo.GetNext(pPos);

		if(temp->getSection() == inTarget->getSection() && temp->getItem()== inTarget->getItem())
		{
			CString strBaseValue;
			strBaseValue.Format(_T(""));
			CString strTemp;
			strTemp.Format(_T(""));

			if(temp->getValue().Find('/') != -1)
			{
				AfxExtractSubString(strTemp, temp->getValue(), 0, '/');
				strBaseValue = strTemp +"/" +inTarget->getValue();
			}
			else
			{
				strBaseValue = temp->getValue() +"/" +inTarget->getValue();
			}
			
			temp->setValue(strBaseValue);
			break;
		}
	}
}

bool InformationManager::CheckBaseInfoInAllData(std::vector<CString>& vDifferentTest)
{
	bool bResult = false;
	FileType cTempFile;
	BasicData* cBaseInfoItem;
	BasicData* cTempItem;
	BasicData* cBaseInfoValue;
	std::vector<CString> vTestName;
	ConfigDMData* temp;
	POSITION pPos=NULL;
	POSITION pBase=NULL;
	POSITION pValue=NULL;
	CList<BasicData*> BaseInfoItemContentsList;
	CList<BasicData*> listTemp;
	CList<BasicData*> BaseInfoItemValueList;
	std::vector<CString> vBaseInfoValues;
	CString strPreFileName;
	strPreFileName.Format("");
	CString strFileName;
	strFileName.Format("");
	pPos = m_listSetting.GetHeadPosition();
	temp = m_listSetting.GetNext(pPos);
	temp->GetBaseInfoList(BaseInfoItemContentsList);

	if(BaseInfoItemContentsList.GetCount() != m_listBaseInfo.GetCount())
	{
		temp->SetBaseInfoList(m_listBaseInfo);
		temp->GetBaseInfoList(BaseInfoItemContentsList);
	}
	pPos = m_listConfigs.GetHeadPosition();
	temp = m_listConfigs.GetNext(pPos);
	temp->GetTestList(vTestName);

	pBase = m_listBaseInfo.GetHeadPosition();

	for (int j = 0; j<m_listBaseInfo.GetCount(); j++)
	{
		cBaseInfoItem = m_listBaseInfo.GetNext(pBase);
		strFileName = cBaseInfoItem->getValue();

		if(strFileName.Find('/') != -1)
		{
			CString strTemp;
			strTemp.Format("");
			AfxExtractSubString(strTemp, strFileName, 0,'/');
			strFileName = strTemp;
		}

		if (strPreFileName != strFileName)
		{
			temp->SearchFileDataInList(vTestName[0], strFileName, cTempFile);
			cTempFile.CopyDataToList(listTemp);
			strPreFileName = strFileName;
		}

		pPos = listTemp.GetHeadPosition();

		for (int k=0; k< listTemp.GetCount(); k++)
		{
			cTempItem = listTemp.GetNext(pPos);

			if(cTempItem->getSection() == cBaseInfoItem->getSection() &&
				cTempItem->getItem() == cBaseInfoItem->getItem())
			{
				BaseInfoItemValueList.AddTail(cTempItem);
			}
		}
	}

	for (int i = 0; i<vTestName.size(); i++)
	{
		strPreFileName = "";
		pBase = BaseInfoItemContentsList.GetHeadPosition();
		pValue = BaseInfoItemValueList.GetHeadPosition();

		for (int j = 0; j<BaseInfoItemContentsList.GetCount(); j++)
		{
			cBaseInfoItem = BaseInfoItemContentsList.GetNext(pBase);
			cBaseInfoValue = BaseInfoItemValueList.GetNext(pValue);

			strFileName = cBaseInfoItem->getValue();

			if (strFileName.Find('_') != -1)
			{			
				for (int i = 0; i < 6; i++)
				{
					int nIndex = strFileName.Find('_');
					strFileName = strFileName.Mid(nIndex+1);
				}
				strFileName = vTestName[i] + "_" + strFileName;
			}

			if (strPreFileName != strFileName)
			{
				temp->SearchFileDataInList(vTestName[i], strFileName, cTempFile);
				cTempFile.CopyDataToList(listTemp);
				strPreFileName = strFileName;
			}

			pPos = listTemp.GetHeadPosition();

			for (int k=0; k < listTemp.GetCount(); k++)
			{
				cTempItem = listTemp.GetNext(pPos);

				if(cTempItem->getSection() == cBaseInfoValue->getSection() &&
					cTempItem->getItem() == cBaseInfoValue->getItem())
				{
					if (cTempItem->getValue() != cBaseInfoValue->getValue())
					{
						CString strDifferent = vTestName[i] + "\\" + cTempItem->getItem();
						vDifferentTest.push_back(strDifferent);
					}
				}
			}
		}
	}

	return bResult;
}