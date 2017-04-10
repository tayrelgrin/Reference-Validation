#include "StdAfx.h"
#include "InformationManager.h"



InformationManager::InformationManager(void)
{
	 //SaveRefToFile();
}


InformationManager::~InformationManager(void)
{
	POSITION pPos = m_listConfigs.GetHeadPosition();
	POSITION ptemp = NULL;

	while(pPos)
	{
		ptemp = pPos;
		ConfigDMData* pData = m_listConfigs.GetNext(pPos);
		delete pData;
		m_listConfigs.RemoveAt(ptemp);
	}
	ptemp = m_listConfigs.GetHeadPosition();

	pPos = m_listSetting.GetHeadPosition();
	while(pPos)
	{
		ptemp = pPos;
		ConfigDMData* pData = m_listSetting.GetNext(pPos);
		delete pData;
		m_listSetting.RemoveAt(ptemp);
	}

	m_listSetting.RemoveAll();
	m_listConfigs.RemoveAll();
}

void InformationManager::AddNewConfigData(ConfigDMData* inNewData)
{
	std::vector<CString> vTest;
	inNewData->GetTestList(vTest);
	inNewData->AddNewTest();

	if(m_listConfigs.IsEmpty())
	{
		m_listConfigs.AddHead(inNewData);
	}
	else
	{
		m_listConfigs.AddTail(inNewData);
	}

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

	m_listConfigs.RemoveAt(pDelete);
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

	//pDelete = m_listConfigs.Find(cTargetData);
	m_listConfigs.RemoveAt(pDelete);
	// add file delete
}

void InformationManager::ModifyConfigData(ConfigDMData* inTargetData)
{

}

void InformationManager::SaveRefToFile(CString inFilePath)
{
	ConfigDMData* pTemp;
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
}

void InformationManager::LoadBasicFileList()
{
	TCHAR path[_MAX_PATH];

	GetModuleFileName(NULL, path, sizeof path);

	CString strEXEPath = path;
	CString strFilepath;

	int i = strEXEPath.ReverseFind('\\');//실행 파일 이름을 지우기 위해서 왼쪽에 있는 '/'를 찾는다.

	strEXEPath = strEXEPath.Left(i);//뒤에 있는 현재 실행 파일 이름을 지운다.

	strFilepath = strEXEPath + "\\Data\\BasicFile.xml";

	tinyxml2::XMLDocument cDoc;

	if(tinyxml2::XML_SUCCESS == cDoc.LoadFile(strEXEPath))
	{
		if(tinyxml2::XML_SUCCESS == cDoc.LoadFile(strFilepath))
		{
			tinyxml2::XMLNode* cNode;

			tinyxml2::XMLDeclaration* decl;



		}
	}
	else
	{
		m_vBasicFile.push_back("Spec.ini");
		m_vBasicFile.push_back("ItemVersion.ini");
		m_vBasicFile.push_back("_Register.ini");
		m_vBasicFile.push_back("OS2.spc");
		m_vBasicFile.push_back("OSLeakage.spc");
	}
}