#include "StdAfx.h"
#include "ConfigDMData.h"


ConfigDMData::ConfigDMData(void)
{
	m_bNewData = false;
	m_strInputDirPath.Format(_T(""));
	m_strPrj.Format(_T(""));
	m_strBuildNum.Format(_T(""));
	m_strConfigNum.Format(_T(""));
	m_strDOE.Format(_T(""));
}


ConfigDMData::~ConfigDMData(void)
{
	InitListAndVectors();
}

void ConfigDMData::InitListAndVectors()
{
	if(!m_vTestDirPath.empty())
		m_vTestDirPath.erase( m_vTestDirPath.begin(), m_vTestDirPath.end() );
	if(!m_vTestName.empty())
		m_vTestName.erase( m_vTestName.begin(), m_vTestName.end() );
	if(!m_vBaseFiles.empty())
		m_vBaseFiles.erase( m_vBaseFiles.begin(), m_vBaseFiles.end() );;

	POSITION pTemp = NULL;
	POSITION pPos = m_pListTestType.GetHeadPosition();
	
	while(pPos && m_pListTestType.GetSize()>0)
	{
		pTemp = pPos;
		
		TestType* temp = m_pListTestType.GetNext(pPos);
		delete temp;
		m_pListTestType.RemoveAt(pTemp);
	}

	pPos = m_lBaseInfo.GetHeadPosition();

	while(pPos && m_lBaseInfo.GetSize()>0)
	{
		pTemp = pPos;

		BasicData* temp = m_lBaseInfo.GetNext(pPos);
		delete temp;
		m_lBaseInfo.RemoveAt(pTemp);
	}
}

void ConfigDMData::RefNameParsing(CString instrData)
{
	CString strProject, strConfig, strDOE, strTest;
	strProject.Format("");
	strConfig.Format("");
	strDOE.Format("");
	strTest.Format("");

	AfxExtractSubString(strProject, instrData, 0, '_');
	AfxExtractSubString(strConfig,  instrData, 4, '_');
	AfxExtractSubString(strTest,	instrData, 5, '_');
	AfxExtractSubString(strDOE,		instrData, 6, '_');
}

void ConfigDMData::GetDirList(CString instrPath, std::vector<CString>& inVDirList,  std::vector<CString>& inVFileList)
{
	SetCurrentDirectory(instrPath); //현재 검색할 디렉터리 설정.

	CFileFind finder;

	BOOL bWorking = finder.FindFile();
	CString DirName;
	CString fileName;

	DirName.Format("");
	fileName.Format("");

	while (bWorking)
	{
		//다음 파일or폴더가 존재하면다면 TRUE 반환
		bWorking = finder.FindNextFile();

		//디렉터리 일때
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

	temp.Format("");

	for(int i = 0; i<(signed)invData.size(); i++)
	{
		invData[i].Replace(inRootPath,_T(""));

		if(invData[i].FindOneOf(_T("\\")) == -1 && invData[i].FindOneOf(_T("Dark")) != -1)
		{
			AfxExtractSubString(outPrj,		invData[i], 0, '_');
			AfxExtractSubString(outConfig,	invData[i], 4, '_');
			/*AfxExtractSubString(outBuild,	invData[i], 4, '_');*/
			AfxExtractSubString(outDOE,		invData[i], 6, '_');
			AfxExtractSubString(temp,		invData[i], 7, '_');

			outBuild = outConfig;

			if(temp=="")
			{
				temp = outDOE;
				outDOE = "Main Build";
			}
			outDOE = outDOE+"-"+temp;
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
	m_strBuildNum.Format("%s",inData);
}

void ConfigDMData::SetConfigNum(CString inData)
{
	m_strConfigNum.Format("%s", inData);
}

void ConfigDMData::SetProject(CString inData)
{
	m_strPrj.Format("%s", inData);
}

void ConfigDMData::SetDOE(CString inData)
{
	m_strDOE.Format("%s",inData);
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


void ConfigDMData::RemoveRootPathInVector(const std::vector<CString> invData, std::vector<CString>& outvData, CString inRootPath)
{
	inRootPath+="\\";
	
	for (INT i= 0 ; i<invData.size(); i++)
	{
		CString temp = invData[i];
		
		temp.Replace(inRootPath,_T(""));
		outvData.push_back(temp);
	}
}

void ConfigDMData::GetTestNameFromDirVector(std::vector<CString> invData, std::vector<CString>& outvData)
{
	for (INT i= 0 ; i<invData.size(); i++)
	{
		CString temp;
		CString temp1;
		CString temp2;
		temp.Format("");
		temp1.Format("%s", invData[i]);
		temp2.Format("");

		if(temp1.Find('\\') == -1)
		{
			AfxExtractSubString(temp,		temp1, 5, '_');
			AfxExtractSubString(temp2,		temp1, 8, '_');
			if (temp2 != "")
			{
				temp = temp2 +":"+ temp;
			}
		}
		else
		{
			AfxExtractSubString(temp2,		temp1, 0, '\\');
			AfxExtractSubString(temp,		temp1, 1, '\\');
			AfxExtractSubString(temp,		temp, 5, '_');
			temp = temp2 +"\\"+ temp;
		}
		if(temp!="")
			outvData.push_back(temp);
	}
}

void ConfigDMData::SetTestList(std::vector<CString> invData)
{
	CString temp;
	temp.Format("");
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
	temp.Format("");
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

void ConfigDMData::AddNewTest(std::vector<CString> inBaseFile, int inNInput)
{
	CString strTestName;
	CString strIndex8th;
	strIndex8th.Format("");
	strTestName.Format("");
	CString m_strBasicLoadTxt;
	m_strBasicLoadTxt.Format("Load Reference Setting :");

	AddCommonBaseFile(inBaseFile);
	for (int i = 0; i<m_vTestDirPath.size(); i++)
	{
		TestType* cAddData = new TestType;

		CString strDir = m_vTestDirPath[i];
		CString strTemp;
		strTemp.Format("%s%c",m_strInputDirPath,'\\');
		strDir.Replace(strTemp, "");

		CString strSubDir;
		strSubDir.Format("");

		AfxExtractSubString(strTestName,strDir,5,'_');

		if(strTestName == m_strBasicLoadTxt)
			strTestName.Format("");

		if (strDir.Find('\\') != -1)
		{
			int nIndex = strDir.Find('\\');
			strSubDir = strDir.Left(nIndex);
			CString strTemp = strTestName;
			strTestName.Format("%s\\%s",strSubDir, strTemp);
		}

		if(strTestName!="")
		{
			cAddData->SetTestName(strTestName);
			cAddData->AddNewTest(m_vTestDirPath[i],m_vBaseFiles, inNInput);

			m_pListTestType.AddTail(cAddData);
		}
		else
			delete cAddData;
	}	
}

void ConfigDMData::GetFilePathInDir(std::vector<CString> invPath, std::vector<CString>& outvData)
{
	CFileFind finder;

	CString fileName;
	CString tpath;

	fileName.Format("");
	tpath.Format("");

	for (int i=0; i<invPath.size(); i++)
	{
		tpath = invPath[i];
		tpath+= "\\*.*";

		BOOL bWorking = finder.FindFile(tpath);

		while (bWorking)
		{
			bWorking = finder.FindNextFile();
			//파일 일때
			if (finder.IsArchived())
			{
				//파일의 이름
				CString _fileName =  finder.GetFileName();

				// 현재폴더 상위폴더 썸네일파일은 제외
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
	invPath.clear();
}

void ConfigDMData::GetTestList(std::vector<CString>& outvPath)
{
	outvPath.clear();
	if (m_vTestName.size() > 0)
	{
		outvPath.assign(m_vTestName.begin(), m_vTestName.end());
	}
	else
	{
		POSITION pPos = m_pListTestType.GetHeadPosition();

		while(pPos)
		{
			TestType* temp = m_pListTestType.GetNext(pPos);
			CString strTemp = temp->GetTestName();
			m_vTestName.push_back(strTemp);
			outvPath.push_back(strTemp);
		}
	}
}

void ConfigDMData::GetDirPathList(std::vector<CString>& outvPath)
{
	outvPath.clear();
	outvPath.assign(m_vTestDirPath.begin(), m_vTestDirPath.end());
}

void ConfigDMData::SaveDataToFile(std::vector<CString> invBasicFile)
{
    CString strEXEPath;

	strEXEPath.Format("%s", GetEXEDirectoryPath());

 	CString strFilePath;
	CString strCTemp;

	strFilePath.Format("");
	strCTemp.Format("");

	strCTemp.Format(_T("%s%s%s"),strEXEPath ,"\\Data\\Value\\" , m_strPrj);

	CreateDirectory(strCTemp,NULL);

	strFilePath.Format(_T("%s%s%s%s%s%s%s%s"), strCTemp,"\\", m_strBuildNum ,"-" , m_strConfigNum , "-" , m_strDOE ,".xml");

	char* strTemp = (LPSTR)strFilePath.GetBuffer(0);

 	tinyxml2::XMLDocument cXMLDocument;
	tinyxml2::XMLDeclaration* dexl = cXMLDocument.NewDeclaration();

	cXMLDocument.LinkEndChild(dexl);

	tinyxml2::XMLElement* pElemenet = cXMLDocument.NewElement("Value");

	cXMLDocument.LinkEndChild(pElemenet);

	POSITION pos = m_pListTestType.GetHeadPosition();

//	AddCommonBaseFile(invBasicFile);		// Ref 파일에 기본 파일들 추가

	std::vector<CString> vTemp;

	while(pos)
	{
		TestType* pData = m_pListTestType.GetNext(pos);
		pData->SaveDataToFile(cXMLDocument, pElemenet, vTemp);
	}
	
	cXMLDocument.SaveFile(strTemp);
	
	//SetNewDataFlag(false);
}

void ConfigDMData::SaveSettingToFile(std::vector<CString> invBasicFile, CList<BasicData*>* inlBaseInfo)
{
	CString strEXEPath;

	strEXEPath.Format("%s", GetEXEDirectoryPath());

	CString strTempFilePath;
	strTempFilePath.Format("%s%s", strEXEPath , "\\Data\\Setting");
	CString strFilePath;
	CreateDirectory(strTempFilePath,NULL);

	strFilePath.Format(_T("%s%s%s%s%s%s%s%s%s%s"), strTempFilePath , "\\Setting-" , m_strPrj , "-" , m_strBuildNum , "-" , m_strConfigNum , "-" , m_strDOE , ".xml");

	char* strTemp = (LPSTR)strFilePath.GetBuffer(0);

	tinyxml2::XMLDocument cXMLDocument;
	tinyxml2::XMLDeclaration* dexl = cXMLDocument.NewDeclaration();

	cXMLDocument.LinkEndChild(dexl);

	
	AddCommonBaseFile(invBasicFile);		// Ref 파일에 기본 파일들 추가
	
	//////////////////////////////////////////////////////////////////////////
	tinyxml2::XMLElement* pElem;
	tinyxml2::XMLElement* pElem2;
	tinyxml2::XMLText* text;
	pElem = cXMLDocument.NewElement("BaseFile");
	
	for (int i = 0; i<m_vBaseFiles.size(); i++)
	{
		pElem2 = cXMLDocument.NewElement("File");
		text = cXMLDocument.NewText( LPSTR(LPCTSTR(m_vBaseFiles[i])) );

		pElem2->LinkEndChild(text);
		pElem->LinkEndChild(pElem2);
	}
	cXMLDocument.LinkEndChild(pElem);
	//////////////////////////////////////////////////////////////////////////
	
	//////////////////////////////////////////////////////////////////////////
	{
		tinyxml2::XMLElement* pBaseElemenet = cXMLDocument.NewElement("BaseInfo");

		std::vector<CString> vStrDummy;
		cXMLDocument.LinkEndChild(pBaseElemenet);
		// 여기서 직접 저장
		POSITION pPos = inlBaseInfo->GetHeadPosition();
		tinyxml2::XMLElement* RootElement;
		
		if (pPos == NULL)
		{
			tinyxml2::XMLElement* Element;

			Element = cXMLDocument.NewElement("Element");
			pBaseElemenet->LinkEndChild(Element);
		}
		while(pPos)
		{
			tinyxml2::XMLElement* Element;
			
			Element = cXMLDocument.NewElement("Element");
			BasicData* temp = inlBaseInfo->GetNext(pPos);

			pBaseElemenet->LinkEndChild(Element);
			Element->SetAttribute("Section",	temp->getSection());
			Element->SetAttribute("Item",		temp->getItem());
			Element->SetAttribute("Value",		temp->getValue());
			
		}
	}
	//////////////////////////////////////////////////////////////////////////
	tinyxml2::XMLElement* pElemenet = cXMLDocument.NewElement("Setting");

	cXMLDocument.LinkEndChild(pElemenet);

	POSITION pos = m_pListTestType.GetHeadPosition();

	while(pos)
	{
		TestType* pData = m_pListTestType.GetNext(pos);
		pData->SaveDataToFile(cXMLDocument, pElemenet, m_vBaseFiles);
	}

	cXMLDocument.SaveFile(strTemp);
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
	bool bResult;
	for(int i=0; i<invFileName.size(); i++)
	{
		bResult = false;
		for (int j= 0 ; j< m_vBaseFiles.size(); j++)
		{
			if (m_vBaseFiles[j]== invFileName[i])
			{
				bResult = true;
			}
		}
		if(bResult == false)
			m_vBaseFiles.push_back(invFileName[i]); 
	}
}

void ConfigDMData::SetBaseFiles(std::vector<CString> invFileName)
{
	m_vBaseFiles.clear();
	CString strTemp, strFileName;
	strFileName.Format("");
	strTemp.Format("");

	for (int i=0; i<invFileName.size(); i++)
	{
		strFileName = invFileName[i];

		if (strFileName.Find('\\') != -1)
		{
			AfxExtractSubString(strTemp, strFileName, 1, '\\');
			strFileName = strTemp;
		}

		if(strFileName.GetLength() >7)
		{
			strTemp.Format(_T("%s%s"), strFileName, ".ini");

			m_vBaseFiles.push_back(strTemp);

			strTemp.Format(_T("%s%s"), strFileName, "_Register.ini");

			m_vBaseFiles.push_back(strTemp);
		}
	}
}

CString ConfigDMData::GetEXEDirectoryPath()
{
	CString strDirecPath;
	TCHAR path[_MAX_PATH];

	GetModuleFileName(NULL, path, sizeof path);

	strDirecPath.Format("%s",path);

	int i = strDirecPath.ReverseFind('\\');//실행 파일 이름을 지우기 위해서 왼쪽에 있는 '/'를 찾는다.

	strDirecPath = strDirecPath.Left(i);//뒤에 있는 현재 실행 파일 이름을 지운다.

	return strDirecPath;
}

void ConfigDMData::LoadDataFiles(CString inStrPath)
{
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError eResult = xmlDoc.LoadFile( LPSTR(LPCTSTR(inStrPath)));

	InitListAndVectors();

	SearchXMLData(&xmlDoc);
}

void ConfigDMData::SearchXMLData(tinyxml2::XMLNode* pParent, int inIndex)
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
		if (strTemp == "BaseInfo")
		{
			tinyxml2::XMLAttribute* pAttr;
			/*tinyxml2::XMLAttribute* pAttrTemp;*/
			tinyxml2::XMLNode* pChild;
			pChild = pNode->FirstChild();
			if(pElent = pChild->ToElement())
			{
				for (pElent; pElent!= 0 ; pElent = pElent->NextSiblingElement())
				{
					BasicData* outData = new BasicData;
					for (pAttr = (tinyxml2::XMLAttribute*)pElent->FirstAttribute(); pAttr != 0; pAttr = (tinyxml2::XMLAttribute*)pAttr->Next() )
					{
						CString strTempValue;
						strTempValue.Format(_T("%s"),pAttr->Name());

						if(_T("Section") == strTempValue)
							outData->setSection((CString)pAttr->Value());
						else if(_T("Item") == strTempValue)
							outData->setItem((CString)pAttr->Value());
						else if(_T("Value") == strTempValue)
						{
							outData->setValue((CString)pAttr->Value());
						}
					}
					m_lBaseInfo.AddTail(outData);
				}
			}
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

						strFile.Format(_T(""));
						strDir.Format(_T(""));

						AfxExtractSubString(strDir, vTemp[i], 2,':');
						if (strDir=="")
						{
							AfxExtractSubString(strFile, vTemp[i], 1,':');
						}
						else
							strFile.Format("%s", strDir);

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


//////////////////////////////////////////////////////////////////////////
// Name     : GetFileNames
// Function : input Test names to outvData in this class
// pre		: none
// return	: none
//////////////////////////////////////////////////////////////////////////
void ConfigDMData::GetFileNames(std::vector<CString>& outvData)
{
	CString strTemp;
	strTemp.Format("");

	POSITION pTemp = NULL;
	POSITION pPos = m_pListTestType.GetHeadPosition();

	while(pPos)
	{
		TestType* temp = m_pListTestType.GetNext(pPos);
		strTemp.Format("%s", temp->GetTestName());
		if (strTemp[0]=='\\')
		{
			//CString strTemp1 = strTemp.Replace('\\',"");
		}
		temp->GetFileNames(strTemp, outvData);
	}
}

bool ConfigDMData::SearchFileDataInList(CString inTargetTest, CString inTargetFile , FileType& outData)
{
	bool bResult = false;
	POSITION pPos = m_pListTestType.GetHeadPosition();

	while(pPos)
	{
		TestType* temp = m_pListTestType.GetNext(pPos);
 		CString strTemp = temp->GetTestName();

		if(strTemp == inTargetTest)
		{
			bResult = temp->SearchFileInList(inTargetFile, outData);
		}
	}

	return bResult;
}

TestType* ConfigDMData::SearchTest(TestType& inoutTarget, bool& bResult)
{
	bResult = false;
	POSITION pPos = m_pListTestType.GetHeadPosition();

	TestType* temp = NULL;

	while(pPos)
	{
		temp = m_pListTestType.GetNext(pPos);
		CString strTemp = temp->GetTestName();

		if(strTemp == inoutTarget.GetTestName())
		{
			TestType* pTemp = &inoutTarget;
			delete pTemp;
			bResult = true;
			break;
		}
	}

	return temp;
}


void ConfigDMData::GetBaseInfoList(CList<BasicData*>& outList)
{
	if(outList.GetCount() > 0)
	{
		POSITION pPos = outList.GetHeadPosition();
		POSITION pTemp = NULL;

		while(pPos)
		{
			pTemp = pPos;
			BasicData* cTemp = outList.GetNext(pPos);
			delete cTemp;
			m_pListTestType.RemoveAt(pTemp);
		}
		outList.RemoveAll();
	}

	POSITION pPos = m_lBaseInfo.GetHeadPosition();

	while(pPos)
	{
		BasicData* cTemp = m_lBaseInfo.GetNext(pPos);
		outList.AddTail(cTemp);
	}
}

void ConfigDMData::SetBaseInfoList(CList<BasicData*>& inList)
{
	POSITION pPos = inList.GetHeadPosition();
	POSITION pTemp = NULL;

	if(inList.GetCount() > 0)
	{
		pPos = inList.GetHeadPosition();
		pTemp = NULL;

		while(pPos)
		{
			BasicData* cTemp = inList.GetNext(pPos);
			BasicData* cNewData = new BasicData;
			cNewData->setData(*cTemp);
			m_lBaseInfo.AddTail(cNewData);
		}
	}
}

void ConfigDMData::InitBaseInfoList()
{
	POSITION pPos = m_lBaseInfo.GetHeadPosition();
	POSITION pTemp = NULL;

	m_lBaseInfo.RemoveAll();
}


void ConfigDMData::ModifyData(CString inTargetTestName, CString inTargetFileName, BasicData* inTarget)
{
	POSITION pPos = m_pListTestType.GetHeadPosition();
	POSITION pTemp = NULL;

	while(pPos)
	{
		pTemp = pPos;
		TestType* cTemp = m_pListTestType.GetNext(pPos);
		if(cTemp->GetTestName() == inTargetTestName)
		{
			cTemp->ModifyData(inTargetFileName, inTarget);
			SetNewDataFlag(true);
			break;
		}
	}
}


void ConfigDMData::ChangeFileName(CString inTestName, CString inNewFileName, CString inTargetFileName)
{
	POSITION pPos = m_pListTestType.GetHeadPosition();
	POSITION pTemp = NULL;

	while(pPos)
	{
		pTemp = pPos;
		TestType* cTemp = m_pListTestType.GetNext(pPos);
		if(cTemp->GetTestName() == inTestName)
		{
			cTemp->ChangeFileName(inTargetFileName, inNewFileName);
			SetNewDataFlag(true);
			break;
		}
	}
}

void ConfigDMData::SetRootPath(CString inPath)
{
	m_strInputDirPath.Format("%s", inPath);
}