#include "StdAfx.h"
#include "DataController.h"


DataController::DataController()
{
	m_strLogPath.Format("");
}

DataController::~DataController(void)
{
	InitAllData();
}

bool DataController::CheckBaseInfoInAllData(CString instrPath, std::vector<CString>& vTestDirPath)
{
	SetCurrentDirectory(instrPath); //현재 검색할 디렉터리 설정.

	bool bResult = true;

	int nFileCount = 0;
	int nDirCount = 0;
	CFileFind cFinder;
	CString strFileName;
	CString strDirName;
	CString strDirPath;
	int nFindIndex;
	CString strRegister;
	CString strRefFile;
	CString strError;
	CString strListLog;

	strFileName.Format(_T(""));
	strDirName.Format(_T(""));
	strDirPath.Format(_T(""));
	strRegister.Format(_T(""));
	strRefFile.Format(_T(""));
	strError.Format(_T(""));
	strListLog.Format(_T(""));

	std::vector<bool> vResult;

	nDirCount = vTestDirPath.size();
	
	for (int i = 0; i < nDirCount; i++)
	{
		CString strTemp = vTestDirPath[i];
		SetCurrentDirectory(strTemp);

		BOOL bSearching = cFinder.FindFile();
		nFindIndex = strTemp.ReverseFind('\\');
		strDirName = strTemp.Mid(nFindIndex+1);
		bool bRefFile = false;
		bool bRegister = false;
		bool bSpec = false;		
		bool bDirectory = false;

		strRefFile.Format(_T("%s%s"), strDirName, _T(".ini"));
		strRegister.Format(_T("%s%s"), strDirName, _T( "_Register.ini"));
		nFileCount = 0;

		while(bSearching)
		{
			bSearching = cFinder.FindNextFile();
			strFileName = cFinder.GetFileName();

			if(cFinder.IsArchived())
			{
				strFileName = cFinder.GetFileName();

				if( strFileName == _T(".") ||
					strFileName == _T("..")||
					strFileName == _T("Thumbs.db") ) continue;

				if (strFileName == strRefFile)
				{					
					strListLog.Format(_T("%s%s"),strRefFile, _T(": OK"));
					m_ListLog->WriteLogFile(strListLog);
					bRefFile = true;
				}
				else if(strFileName == strRegister)
				{
					strListLog.Format(_T("%s%s"),strRegister, _T(": OK"));
					m_ListLog->WriteLogFile(strListLog);
					bRegister = true;
				}
				else if(strFileName == _T("Spec.ini"))
				{
					strListLog.Format(_T("%s%s"),strFileName, _T(": OK"));
					m_ListLog->WriteLogFile(strListLog);
					bSpec = true;
				}

				if (bRegister && bRefFile && bSpec)
				{
					break;
				}
				nFileCount++;
			}
			else if (cFinder.IsDirectory() && !cFinder.IsDots())	// no-spec and REL
			{
				bDirectory = true;
			}
		}
		if (!bDirectory)
		{
			if (bRegister && bRefFile && bSpec && (nFileCount >4) )
			{
				vResult.push_back(true);
			}
			else
			{
				strListLog.Format(_T("%s%s"),strFileName, _T(": Fail"));
				m_ListLog->WriteLogFile(strListLog);
				vResult.push_back(false);
			}
		}
	}

	for (int i = 0; i < vResult.size() ; i++)
	{
		if(vResult[i] == false)
		{
			bResult = false;
			break;
		}
	}
	
	if(vResult.size()<3)
		bResult = false;

	return bResult;
}


void DataController::GetDirList(CString instrPath, std::vector<CString>& outDirVector,  std::vector<CString>& outFileVector)
{
	SetCurrentDirectory(instrPath); //현재 검색할 디렉터리 설정.

	CFileFind finder;

	BOOL bWorking = finder.FindFile();
	CString DirName;
	CString fileName;

	DirName.Format(_T(""));
	fileName.Format(_T(""));

	while (bWorking)
	{
		//다음 파일or폴더가 존재하면다면 TRUE 반환
		bWorking = finder.FindNextFile();

		//디렉터리 일때
		if (finder.IsDirectory() && !finder.IsDots())
		{
			DirName = finder.GetFilePath();
			GetDirList(DirName, outDirVector, outFileVector);
		}
		if (finder.IsDirectory() && finder.IsDots() == false )
		{
			outDirVector.push_back(DirName);
		}
		if (finder.IsArchived())
		{
			fileName = finder.GetFilePath();
			outFileVector.push_back(fileName);
		}
	}
}


void DataController::LoadXMLFileListInValue()
{
	ConfigType cTempConfig;

	CString strEXEDirectory;
	strEXEDirectory.Format(_T(""));

	m_vValueFileList.clear();

	strEXEDirectory = cTempConfig.GetEXEDirectoryPath();

	strEXEDirectory += _T("\\Data\\Value");

	SetCurrentDirectory(strEXEDirectory); //현재 검색할 디렉터리 설정.

	CFileFind finder;

	std::vector<CString> vStrFilePath;
	std::vector<CString> vDummy;

	GetDirList(strEXEDirectory,vDummy, vStrFilePath);

	CString strPrj, strBuild, strConfig, strDOE;

	for (int i = 0; i < vStrFilePath.size(); i++)
	{
		ParsingBBCD(vStrFilePath[i], strPrj, strBuild, strConfig, strDOE);

		CString strComb = strPrj + '_'+ strBuild + '_' + strConfig + '_' + strDOE;

		m_vValueFileList.push_back(strComb);
	}
}

void DataController::ParsingBBCD(CString inStr, CString& outStrPrj, CString& outStrBuild, CString& outStrConfig, CString& outStrDOE)
{
	if (inStr.Find(_T(".xml"))!= -1)
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
	else
	{
		int nIndex = inStr.ReverseFind('\\');
		CString strFileName = inStr.Mid((nIndex+1));
		CString strTemp = inStr.Left(nIndex);

		AfxExtractSubString(outStrPrj,		strFileName,0,'_');
		AfxExtractSubString(outStrConfig,	strFileName,4,'_');
		outStrBuild.Format(_T("%c%c.%c"),outStrConfig[0],outStrConfig[1],outStrConfig[2]);
		
		AfxExtractSubString(outStrDOE,		strFileName,8,'_');
		if(outStrDOE=="")
			outStrDOE = _T("Main Build");
	}	
}

void DataController::GetTestNameFromTestDirNameVector(static std::vector<CString> invData, std::vector<CString>& outvData)
{
	for (INT i= 0 ; i<invData.size(); i++)
	{
		CString temp;
		CString temp1;
		CString temp2;
		temp.Format(_T(""));
		temp1.Format(_T("%s"), invData[i]);
		temp2.Format(_T(""));

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

void DataController::RemoveRootPathInVector(const std::vector<CString> invData, std::vector<CString>& outvData, CString inRootPath)
{
	inRootPath+="\\";

	for (INT i= 0 ; i<invData.size(); i++)
	{
		CString temp = invData[i];

		temp.Replace(inRootPath,_T(""));

		outvData.push_back(temp);
	}
}

void DataController::GetConfigFromTestDirNameVector(std::vector<CString> invData, CString& strConfig)
{
	CString temp;
	CString temp1;

	temp.Format(_T(""));
	temp1.Format(_T("%s"), invData[0]);


	AfxExtractSubString(temp, temp1, 4, '_');
	
	strConfig = temp;
}



void DataController::ReadReference()
{
	CString strDir, strRootPath;
	strDir.Format(_T(""));
	strRootPath.Format(_T(""));

	std::vector<CString> vConfig;

	int nRootIndex = 0;

	// m_vTestDir에서 컨피그 별로 분류
	for (int i=0; i < m_vDirVector.size(); i++)
	{
		strRootPath = m_vRootDIr[nRootIndex];

		if (m_vDirVector[i].Find(strRootPath) != -1)
		{
			vConfig.push_back(m_vDirVector[i]);
		}
		else
		{
			// config 별로 추가
			AddNewConfigData(vConfig);
			vConfig.clear();
			i--;
			strRootPath = m_vRootDIr[++nRootIndex];
		}

		if ( i == m_vDirVector.size() -1)
		{
			// config 별로 추가
			AddNewConfigData(vConfig);
		}
	}
}

void DataController::AddTestDirectoryPath(std::vector<CString> invData)
{
	for (int i = 0; i < invData.size(); i++)
	{
		m_vDirVector.push_back(invData[i]);
	}
}

void DataController::AddFilePath(std::vector<CString> invData)
{
	for (int i = 0; i < invData.size(); i++)
	{
		m_vFileVector.push_back(invData[i]);
	}
}

void DataController::DeleteFilePath(CString inTarget)
{
	int nDelCount = 0;
	int nIndex = m_vFileVector.size();

	for (int i= 0; i< nIndex ; i++)
	{
		if (m_vFileVector[nDelCount].Find(inTarget) != -1)
		{
			m_vFileVector.erase(m_vFileVector.begin()+nDelCount);
		}
		else
			nDelCount++;
	}
}


void DataController::DeleteTestDirectoryPath(CString inTarget)
{
	int nDelCount = 0;
	int nIndex = m_vDirVector.size();

	for (int i= 0; i < nIndex; i++)
	{
		if (m_vDirVector[nDelCount].Find(inTarget) != -1)
		{
			m_vDirVector.erase(m_vDirVector.begin()+nDelCount);
		}
		else
			nDelCount++;
	}

	nDelCount = 0;
	nIndex = m_vRootDIr.size();
	for (int i= 0; i < nIndex; i++)
	{
		if (m_vRootDIr[nDelCount].Find(inTarget) != -1)
		{
			m_vRootDIr.erase(m_vRootDIr.begin()+nDelCount);
		}
		else
			nDelCount++;
	}
}

void DataController::GetTestDirectoryPath(std::vector<CString>& outvData)
{
	outvData.clear();

	outvData.assign(m_vDirVector.begin(), m_vDirVector.end());
}

void DataController::GetFilePath(std::vector<CString>& outvData)
{
	outvData.clear();

	outvData.assign(m_vFileVector.begin(), m_vFileVector.end());
}

void DataController::AddNewConfigData(std::vector<CString> inData)
{
	ConfigType* m_pTargetRef = new ConfigType;
	CString strPrj,strBuild,strConfig,strDOE;
	CString strDirRootPath;
	strDirRootPath.Format(_T(""));
	
	for (int i = 0; i < m_vRootDIr.size(); i++)
	{
		if(inData[0].Find(m_vRootDIr[i]) != -1)
		{
			strDirRootPath = m_vRootDIr[i];
			break;
		}
	}

	ParsingBBCD(inData[0],strPrj,strBuild,strConfig,strDOE);
	m_pTargetRef->SetProject(strPrj);
	m_pTargetRef->SetBuildNum(strBuild);
	m_pTargetRef->SetConfigNum(strConfig);
	m_pTargetRef->SetDOE(strDOE);
	m_pTargetRef->SetRootPath(strDirRootPath);

	m_pTargetRef->AddNewTest(inData);

	m_pListTargetRefConfig.AddTail(m_pTargetRef);
}

BOOL DataController::Validation(CString inData)
{
	m_ListLog->WriteLogFile(_T("Init All Lists"));
	InitAllData();
	int nCount = 1;

	// Read Target Reference 
	m_ListLog->WriteLogFile(_T("====================== Read Target Reference Start ======================"));
	ReadReference();
	m_ListLog->WriteLogFile(_T("====================== Read Target Reference End ======================"));
	m_ProgressBar->SetStep(3);
	m_ProgressBar->StepIt();

	// Read Base Reference
	m_ListLog->WriteLogFile(_T("====================== Read Base Reference Start ======================"));
	LoadXMLDataFiles(inData);
	m_ListLog->WriteLogFile(_T("====================== Read Base Reference End ======================"));
	m_ProgressBar->StepIt();

	// 공동 데이터 확인
	m_ListLog->WriteLogFile(_T("====================== Check Common Information Start ======================"));
	CheckCommonInformation();
	m_ProgressBar->StepIt();
	m_ListLog->WriteLogFile(_T("====================== Check Common Information End ======================"));

	// Ref Naming rule checking
	m_ListLog->WriteLogFile(_T("====================== Check Check Naming Rule Start ======================"));
	CheckNamingRule();
	m_ProgressBar->StepIt();
	m_ListLog->WriteLogFile(_T("====================== Check Check Naming Rule End ======================"));

	std::vector<CString> vTemp;
	// Compare
	m_ListLog->WriteLogFile(_T("======================Compare Reference Start======================"));
	CompareReference(vTemp, m_pListLogData,m_pListDifferentResult, 3);
	m_ListLog->WriteLogFile(_T("======================Compare Reference End======================"));

	// CRC 계산
	m_ListLog->WriteLogFile(_T("====================== Calculate CRC Start ======================"));
	CheckCRC(vTemp);
	m_ProgressBar->StepIt();
	m_ListLog->WriteLogFile(_T("====================== Calculate CRC End ======================"));

	// Result Log 쓰기
	m_ListLog->WriteLogFile(_T("====================== Start Writing Log ======================"));
	WriteResultLog(vTemp);
	int nProgressValue = m_ProgressBar->GetPos();
	m_ProgressBar->SetStep(100-nProgressValue);
	m_ProgressBar->StepIt();
	m_ListLog->WriteLogFile(_T("====================== End Writing Log ======================"));
	return TRUE;
}

void DataController::LoadXMLDataFiles(CString inData)
{
	ConfigType* pAddValue	= new ConfigType;
	ConfigType* pAddSetting = new ConfigType;

	CString strValuePath;
	CString strSettingPath;
	CString strEXEDirectory;
	
	CString strPrj, strBuild, strConfig, strDOE;

	m_ListLog->WriteLogFile(_T("ParsingBBCD"));
	ParsingBBCD(inData, strPrj, strBuild, strConfig, strDOE);

	strEXEDirectory = GetEXEDirectoryPath();
	strValuePath.Format(_T("%s%s%s%s%s%s%s%s%s%s"), strEXEDirectory, _T("\\Data\\Value\\"), strPrj, _T("\\"), strBuild,_T("-"), strConfig, _T("-"), strDOE,_T(".xml"));
	strSettingPath.Format(_T("%s%s%s%s%s%s%s%s%s%s"),strEXEDirectory,_T("\\Data\\Setting\\Setting-"), strPrj, _T("-"), strBuild, _T("-"), strConfig, _T("-"), strDOE,_T(".xml"));
	
	m_ListLog->WriteLogFile(_T("Load Data Files"));
	pAddValue->SetListLog(m_ListLog);
	pAddValue->SetListCtrl(m_ListCtrl);
	pAddValue->LoadDataFiles(strValuePath);

	m_ListLog->WriteLogFile(_T("LoadDataFiles") + strSettingPath);
	pAddSetting->SetListLog(m_ListLog);
	pAddSetting->SetListCtrl(m_ListCtrl);
	pAddSetting->LoadDataFiles(strSettingPath);

	pAddValue->SetProject(strPrj);
	pAddValue->SetBuildNum(strBuild);
	pAddValue->SetConfigNum(strConfig);
	pAddValue->SetDOE(strDOE);

	pAddSetting->SetProject(strPrj);
	pAddSetting->SetBuildNum(strBuild);
	pAddSetting->SetConfigNum(strConfig);
	pAddSetting->SetDOE(strDOE);

	m_pListConfig.AddTail(pAddValue);
	m_pListSetting.AddTail(pAddSetting);
}

CString DataController::GetEXEDirectoryPath()
{
	CString strDirecPath;
	TCHAR path[_MAX_PATH];

	GetModuleFileName(NULL, path, sizeof path);

	strDirecPath = path;

	int i = strDirecPath.ReverseFind('\\');//실행 파일 이름을 지우기 위해서 왼쪽에 있는 '/'를 찾는다.

	strDirecPath = strDirecPath.Left(i);//뒤에 있는 현재 실행 파일 이름을 지운다.

	return strDirecPath;
}

void DataController::AddRootPath(CString inData)
{
	m_vRootDIr.push_back(inData);
}

void DataController::InitAllData()
{
	POSITION pTemp = NULL;
	POSITION pPos = m_pListConfig.GetHeadPosition();

	while(pPos && m_pListConfig.GetSize()>0)
	{
		pTemp = pPos;

		ConfigType* temp = m_pListConfig.GetNext(pPos);
		delete temp;
		m_pListConfig.RemoveAt(pTemp);
	}

	pTemp = NULL;
	pPos = m_pListSetting.GetHeadPosition();

	while(pPos && m_pListSetting.GetSize()>0)
	{
		pTemp = pPos;

		ConfigType* temp = m_pListSetting.GetNext(pPos);
		delete temp;
		m_pListSetting.RemoveAt(pTemp);
	}

	pTemp = NULL;
	pPos = m_pListTargetRefConfig.GetHeadPosition();

	while(pPos && m_pListTargetRefConfig.GetSize()>0)
	{
		pTemp = pPos;

		ConfigType* temp = m_pListTargetRefConfig.GetNext(pPos);
		delete temp;
		m_pListTargetRefConfig.RemoveAt(pTemp);
	}

	
	pTemp = NULL;
	pPos = m_pListLogData.GetHeadPosition();

	while(pPos && m_pListLogData.GetSize()>0)
	{
		pTemp = pPos;

		CompareResult* temp = m_pListLogData.GetNext(pPos);
		delete temp;
		m_pListLogData.RemoveAt(pTemp);
	}
}


void DataController::GetValueXMLFileList(std::vector<CString>& outData)
{
	outData.clear();

	outData.assign(m_vValueFileList.begin(), m_vValueFileList.end());
}


int DataController::CompareReference(std::vector<CString> outResult, CList<CompareResult*>& outLogData, CList<CompareResult*>& outDifferent,int inCount)
{
	//BOOL bResult = FALSE;
	POSITION pBaseRefPos = m_pListConfig.GetHeadPosition();
	POSITION pTargetRefPos = m_pListTargetRefConfig.GetHeadPosition();
	CString strTarget, strBase;
	std::vector<CString> vFailList;

	while(pBaseRefPos)
	{
		ConfigType* pBaseRef = m_pListConfig.GetNext(pBaseRefPos);
		strBase.Format(_T("%s : %s_%s_%s_%s"),_T("Base Ref"), pBaseRef->GetProject(),pBaseRef->GetBuildNum(),pBaseRef->GetConfigNum(),pBaseRef->GetDOE());
		
		while(pTargetRefPos)
		{
			ConfigType* pTargetRef = m_pListTargetRefConfig.GetNext(pTargetRefPos);
			strTarget.Format(_T("%s : %s_%s_%s_%s"),_T("Target Ref"), pTargetRef->GetProject(),pTargetRef->GetBuildNum(),pTargetRef->GetConfigNum(),pTargetRef->GetDOE());
			vFailList.push_back(_T("==================================================================="));
			vFailList.push_back(strBase);
			vFailList.push_back(strTarget);
			vFailList.push_back(_T("==================================================================="));
			
			CompareResult* cNewConfig = new CompareResult;
			cNewConfig->SetConfigInfo(_T("Base Config"));
			cNewConfig->SetTestName(strBase);
			cNewConfig->SetFileName(_T("Target Config"));
			cNewConfig->SetItemName(strTarget);
			pTargetRef->SetListCtrl(m_ListCtrl);
			pTargetRef->SetProgressBar(m_ProgressBar);
			pTargetRef->SetFailItemPointer(m_pFailItems);
			pTargetRef->SetTestDir(m_vDirVector);
			outLogData.AddTail(cNewConfig);
			outDifferent.AddTail(cNewConfig);

			pTargetRef->ConfigCompare(pBaseRef, vFailList, outLogData, outDifferent, inCount);
			inCount += 3;
		}
	}

	for (int i =0; i < vFailList.size(); i++)
	{
		m_ListLog->WriteLogFile(vFailList[i]);
	}
	return inCount;

}

void DataController::SetListLog(ListLog* inData)
{
	m_ListLog = inData;
}

void DataController::SetListCtrl(CListCtrl* inData)
{
	m_ListCtrl = inData;
}


void DataController::GetResultList(CList<CompareResult*>& outData)
{
	POSITION pTemp = NULL;
	POSITION pPos = outData.GetHeadPosition();

	while(pPos && outData.GetSize()>0)
	{
		pTemp = pPos;

		CompareResult* temp = outData.GetNext(pPos);
		delete temp;
		outData.RemoveAt(pTemp);
	}

	pTemp = NULL;
	pPos = m_pListLogData.GetHeadPosition();
	while(pPos && outData.GetSize()>0)
	{
		pTemp = pPos;

		CompareResult* temp = m_pListLogData.GetNext(pPos);
		outData.AddTail(temp);
	}
}

void DataController::WriteResultLog(std::vector<CString> inData)
{
	CString strExePath = GetEXEDirectoryPath();
	CString strLogDirPath;
	strLogDirPath.Format("%s%s", strExePath,_T("\\ResultLog"));
	CString strLogPath;
	FILE* file;

	CreateDirectory(strLogDirPath,NULL);
	do 
	{
		COleDateTime currentTime;
		currentTime = COleDateTime::GetCurrentTime();
		
		strLogPath.Format(_T("%s\\Result_%04d%02d%02d_%02d%02d%02d.csv"),strLogDirPath, currentTime.GetYear(), currentTime.GetMonth(), currentTime.GetDay(), currentTime.GetHour(), currentTime.GetMinute(), currentTime.GetSecond() );
		
		m_ListLog->WriteLogFile(strLogPath);

		file = fopen(strLogPath,"w+");

		POSITION pTemp = NULL;
		POSITION pPos = m_pListLogData.GetHeadPosition();
		CString strComma,strReturn;
		strComma.Format(",");
		strReturn.Format("\n");
		CString strLogData;
		strLogData.Format("");

		std::vector<CString> vHeader;
		std::vector<CString> vBase;
		std::vector<CString> vCurrent;
		std::vector<CString> vResult;

		while(pPos && m_pListLogData.GetSize()>0)
		{
			pTemp = pPos;
			CompareResult* temp = m_pListLogData.GetNext(pPos);

			if (temp->GetConfigInfo() != _T(""))
			{
				strLogData = temp->GetConfigInfo();
				vHeader.push_back(strLogData);

				strLogData = temp->GetTestName();
				vBase.push_back(strLogData);

				strLogData = temp->GetFileName();
				vCurrent.push_back(strLogData);

				strLogData = temp->GetItemName();
				vResult.push_back(strLogData);
			}
			else if (temp->GetTestName() != _T(""))
			{
				vHeader.push_back(strReturn);
				vBase.push_back(strReturn);
				vCurrent.push_back(strReturn);
				vResult.push_back(strReturn);

				strLogData.Format("%s,",temp->GetTestName());
				vHeader.push_back(strLogData);
				vBase.push_back(strLogData);
				vCurrent.push_back(strLogData);
				vResult.push_back(strLogData);
			}
			else if (temp->GetFileName() != _T(""))
			{
				strLogData.Format("%s,",temp->GetFileName());
				
				vHeader.push_back(strLogData);
				vBase.push_back(strLogData);
				vCurrent.push_back(strLogData);
				vResult.push_back(strLogData);
			}
			else if (temp->GetItemName() != _T(""))
			{
				int nCountComma = 0;

				CString strValue,strTemp;
				strValue.Format(_T(""));
				strTemp.Format(_T(""));
				strValue = temp->GetBaseInfoValue();

				if (strValue.Find(',') != -1)
				{
					nCountComma = strValue.Remove(',');
				}
				for (int i = 0; i<= nCountComma; i++)
				{
					strLogData.Format(_T("%s,"),temp->GetItemName());
					vHeader.push_back(strLogData);
				}

// 				for (int i = 0; i<= nCountComma; i++)
// 				{
// 					strTemp = temp->GetBaseInfoValue();
// 					AfxExtractSubString(strValue, strTemp, i,',');
// 					strLogData.Format(_T("%s,"),strValue);
// 					vBase.push_back(strLogData);
// 				}  
// 				for (int i = 0; i<= nCountComma; i++)
// 				{
// 					strTemp = temp->GetCurrentInfoValue();
// 					AfxExtractSubString(strValue, strTemp, i,',');
// 					strLogData.Format(_T("%s,"),strValue);
// 					vCurrent.push_back(strLogData);
// 				}

				strLogData.Format(_T("%s,"),temp->GetBaseInfoValue());
				vBase.push_back(strLogData);

				strLogData.Format(_T("%s,"),temp->GetCurrentInfoValue());
				vCurrent.push_back(strLogData);

				CString strResult;
				if (temp->GetCompareResult())
				{
					strResult.Format(_T("PASS"));
				}
				else
				{
					strResult.Format(_T("FAIL"));
				}
				for (int i = 0; i<= nCountComma; i++)
				{
					strLogData.Format(_T("%s,"),strResult);
					vResult.push_back(strLogData);
				}				
			}
		}

		int nHeaderCount	= 1;
		int nBaseCount		= 1;
		int nCurrentCount	= 1;
		int nResultCount	= 1;

		bool bHeaderEnd, bBaseEnd, bCurrentEnd, bResultEnd, bWorking;
		bHeaderEnd = false;
		bBaseEnd = false;
		bCurrentEnd = false;
		bResultEnd = false;
		bWorking = true;

		fprintf_s(file,vHeader[0]);
		fprintf_s(file,strReturn);
		fprintf_s(file,vBase[0]);
		fprintf_s(file,strReturn);
		fprintf_s(file,vCurrent[0]);
		fprintf_s(file,strReturn);
		fprintf_s(file,vResult[0]);
		
		do{
			for (int i = nHeaderCount; i < vHeader.size(); i++)
			{
				fprintf_s(file,vHeader[i]);
				if (vHeader[i].Find("\n") != -1)
				{
					nHeaderCount = ++i;
					break;
				}
				if (i == vHeader.size()-1)
				{
					bHeaderEnd = true;
					fprintf_s(file,strReturn);
				}
			}

			for (int i = nBaseCount; i < vBase.size(); i++)
			{
				fprintf_s(file,vBase[i]);
				if (vBase[i].Find("\n") != -1)
				{
					nBaseCount = ++i;
					break;
				}
				if (i == vBase.size()-1)
				{
					bBaseEnd = true;
					fprintf_s(file,strReturn);
				}
			}

			for (int i = nCurrentCount; i < vCurrent.size(); i++)
			{
				fprintf_s(file,vCurrent[i]);
				if (vCurrent[i].Find("\n") != -1)
				{
					nCurrentCount = ++i;
					break;
				}
				if (i == vCurrent.size()-1)
				{
					bCurrentEnd = true;
					fprintf_s(file,strReturn);
				}
			}

			for (int i = nResultCount; i < vResult.size(); i++)
			{
				fprintf_s(file,vResult[i]);
				if (vResult[i].Find("\n") != -1)
				{
					fprintf_s(file,vResult[i]);
					nResultCount = ++i;
					break;
				}
				if (i == vResult.size()-1)
				{
					bResultEnd = true;
					fprintf_s(file,strReturn);
				}
			}
			
			if(bHeaderEnd && bBaseEnd && bCurrentEnd && bResultEnd)
			{
				bWorking = false;
			}
		}while(bWorking);

		for (int i = 0; i < inData.size(); i++)
		{
			fprintf_s(file,inData[i]);
		}

		fclose(file);
	} while (FALSE);
}


BOOL DataController::CheckCRC(std::vector<CString>& outData)
{
	BOOL bResult = FALSE;
	CString strIniFIle;
	CString strTestDir;
	CString strTestName;
	strTestName.Format(_T(""));
	int nCRCResult = 0;
	int nCRCValue = 0;
	int nDirStartIndex = 0;
	int nDirEndIndex = 0;
	for (int i=0; i<m_vFileVector.size(); i++)
	{
		strIniFIle.Format("%s",m_vFileVector[i]);
		nDirEndIndex = strIniFIle.ReverseFind('\\');
		nDirStartIndex = strIniFIle.Left(nDirEndIndex).ReverseFind('\\');

		strTestDir = strIniFIle.Left(nDirEndIndex);
		strTestDir = strTestDir.Mid(nDirStartIndex+1);

		AfxExtractSubString(strTestName, strTestDir, 5,'_');

		if (strIniFIle.Find("ItemVersion.ini") != -1)
		{
			TCHAR sDir[MAX_PATH];		
			nCRCValue = GetPrivateProfileInt(_T("SPEC"), _T("CRC"),  0, strIniFIle);

			strIniFIle.Replace("ItemVersion.ini","Spec.ini");
			m_cCRC.GetFileCRC32(strIniFIle,nCRCResult);
			
			CString strFailListLog;
			
			if (nCRCResult != nCRCValue)
			{
				CompareResult* cFailItem = new CompareResult;
				CString strCRCValue, strCRCResult;
				strCRCValue.Format(_T("%d"),nCRCValue);
				strCRCResult.Format(_T("%d"),nCRCResult);
				cFailItem->SetTestName(strTestName);
				m_pListLogData.AddTail(cFailItem);
				m_pListDifferentResult.AddTail(cFailItem);

				CompareResult* cFailItem1 = new CompareResult;
				cFailItem1->SetFileName(_T("ItemVersion.ini"));
				m_pListLogData.AddTail(cFailItem1);
				m_pListDifferentResult.AddTail(cFailItem1);

				CompareResult* cFailItem2 = new CompareResult;
				cFailItem2->SetBaseInfoValue(strCRCValue);
				cFailItem2->SetCurrentInfoValue(strCRCResult);
				cFailItem2->SetCompareResult(FALSE);
				m_pListLogData.AddTail(cFailItem2);
				m_pListDifferentResult.AddTail(cFailItem2);

				strFailListLog.Format("%s%s\n\t Itemversion: %d :Calculated: %d\n", strIniFIle, _T(" : CRC Dismatched"), nCRCValue, nCRCResult);
				outData.push_back(strFailListLog);
				

				bResult = FALSE;
			}
			else
			{
				strFailListLog.Format("%s\n\t Itemversion: %d :Calculated: %d\n", strIniFIle,nCRCValue, nCRCResult);
				outData.push_back(strFailListLog);
				
				bResult = TRUE;
			}
			m_ListLog->WriteLogFile(strFailListLog);
		}
	}

	return bResult;
}


void DataController::CheckCommonInformation()
{
	BOOL bResult = FALSE;
	BOOL bTotalResult = TRUE;

	CString strIniFIle;
	CString strVERSION;
	CString strers_ver;
	CString strvsr_ver;
	CString strbuild_num;
	CString strBuild_Config;	
	CString strFlex_Config;
	CString strLens_Config;
	CString strSubstrate_Config;
	CString strIRCF_Config;
	CString strStiffener_Config;
	CString strAA_Machine;
	CString strTemp;

	strIniFIle.Format(_T(""));
	strVERSION.Format(_T(""));
	strers_ver.Format(_T(""));
	strvsr_ver.Format(_T(""));
	strbuild_num.Format(_T(""));
	strBuild_Config.Format(_T(""));	
	strFlex_Config.Format(_T(""));
	strLens_Config.Format(_T(""));
	strSubstrate_Config.Format(_T(""));
	strIRCF_Config.Format(_T(""));
	strStiffener_Config.Format(_T(""));
	strAA_Machine.Format(_T(""));
	strTemp.Format(_T(""));

	CString strNVM;
	CString	strProjectID;
	CString strProject_Version;
	CString	strIntegrator;
	CString	strCameraBuild;
	CString	strConfig;
	CString	strIRCF;
	CString	strSubstrate;
	CString	strSensorType;
	CString	strLens;
	CString	strFlex;
	CString	strStiffener;
	CString strCarrier;
	CString strSotfware;
	CString strLensComponent_Revision_Major;
	CString strLensComponent_Revision_Minor;
	CString strColorShading_Revision;
	CString strCISMaskID;
	CString strLAST_STRING;
	strNVM.Format(_T(""));
	strProjectID.Format(_T(""));
	strProject_Version.Format(_T(""));
	strIntegrator.Format(_T(""));
	strCameraBuild.Format(_T(""));
	strConfig.Format(_T(""));
	strIRCF.Format(_T(""));
	strSubstrate.Format(_T(""));
	strSensorType.Format(_T(""));
	strLens.Format(_T(""));
	strFlex.Format(_T(""));
	strStiffener.Format(_T(""));
	strCarrier.Format(_T(""));
	strSotfware.Format(_T(""));
	strLensComponent_Revision_Major.Format(_T(""));
	strLensComponent_Revision_Minor.Format(_T(""));
	strColorShading_Revision.Format(_T(""));
	strCISMaskID.Format(_T(""));
	strLAST_STRING.Format(_T(""));

	CString strListLog;

	TCHAR szBuf[MAX_PATH] = {0,};

	int nCount = 0;
	std::vector<int> vCounts;
	std::vector<int> vDirCount;

	vCounts.push_back(0);

	int nDirCount = 0;
	int nRealDir = 0;

	CFileFind pFinder;	

	for (int nConfigFileCount = 0; nConfigFileCount < m_vRootDIr.size(); nConfigFileCount++)
	{
		CFileFind pFinder;

		for (int i = 0; i < m_vDirVector.size(); i++)
		{
			if (m_vDirVector[i].Find(m_vRootDIr[nConfigFileCount]) != -1)
			{
				CString	strRefDirName = m_vDirVector[i];
				int nCount = strRefDirName.ReverseFind('\\');
				strRefDirName = strRefDirName.Mid(nCount+1);

				CString strTempFilePath;
				strTempFilePath.Format(_T("%s\\%s%s"),m_vDirVector[i],strRefDirName,_T(".ini"));
				if(pFinder.FindFile(strTempFilePath))
				{
					nRealDir++;
				}
				nDirCount++;
			}
		}
		vDirCount.push_back(nRealDir);
	}
	int nPre = 0;
	for (int i = 0; i < m_vRootDIr.size(); i++)
	{
		for (int j=0; j<m_vFileVector.size(); j++)
		{
			if (m_vFileVector[j].Find(m_vRootDIr[i]) != -1)
			{
				nCount++;
			}
			else if(nCount != nPre)
			{
				vCounts.push_back(nCount);
				nPre = nCount;
				break;
			}
		}
	}

	vCounts.push_back(m_vFileVector.size());

	int nAddListCtrl = 0;
	
	for (int j = 0 ; j < vCounts.size() - 1; j++)
	{
		strIniFIle.Format(_T(""));
		strVERSION.Format(_T(""));
		strers_ver.Format(_T(""));
		strvsr_ver.Format(_T(""));
		strbuild_num.Format(_T(""));
		strBuild_Config.Format(_T(""));	
		strFlex_Config.Format(_T(""));
		strLens_Config.Format(_T(""));
		strSubstrate_Config.Format(_T(""));
		strIRCF_Config.Format(_T(""));
		strStiffener_Config.Format(_T(""));
		strAA_Machine.Format(_T(""));
		strTemp.Format(_T(""));
		strNVM.Format(_T(""));
		strProjectID.Format(_T(""));
		strProject_Version.Format(_T(""));
		strIntegrator.Format(_T(""));
		strCameraBuild.Format(_T(""));
		strConfig.Format(_T(""));
		strIRCF.Format(_T(""));
		strSubstrate.Format(_T(""));
		strSensorType.Format(_T(""));
		strLens.Format(_T(""));
		strFlex.Format(_T(""));
		strStiffener.Format(_T(""));
		strCarrier.Format(_T(""));
		strSotfware.Format(_T(""));
		strLensComponent_Revision_Major.Format(_T(""));
		strLensComponent_Revision_Minor.Format(_T(""));
		strColorShading_Revision.Format(_T(""));
		strCISMaskID.Format(_T(""));
		strLAST_STRING.Format(_T(""));

		for (int i = vCounts[j]; i < vCounts[j+1]; i++)
		{
			if (m_vFileVector[i].Find("ItemVersion.ini") != -1)
			{
				strIniFIle = m_vFileVector[i];

				GetPrivateProfileString(_T("LOG"), _T("VERSION"),			_T(""), szBuf,	MAX_PATH, strIniFIle);
				strTemp.Format(_T("%s"), szBuf);
				if (strVERSION ==_T(""))
				{
					strVERSION.Format(_T("%s"), szBuf);
				}
				bResult = ComparePreAndNew(strIniFIle, strVERSION, strTemp, _T("VERSION"));
				if (!bResult)
				{
					strListLog.Format(_T("%s Base Data Fail"), szBuf);
					m_ListLog->WriteLogFile(strListLog);
					bTotalResult = FALSE;
				}

// 				if (bResult)
// 				{
					GetPrivateProfileString(_T("LOG"), _T("ers_ver"),			_T(""), szBuf,	MAX_PATH, strIniFIle);
					strTemp.Format(_T("%s"), szBuf);
					if (strers_ver == _T(""))
					{
						strers_ver.Format(_T("%s"), szBuf);
					}
					bResult = ComparePreAndNew(strIniFIle, strers_ver, strTemp, _T("ers_ver"));
					if (!bResult)
					{
						strListLog.Format(_T("%s Base Data Fail"), szBuf);
						m_ListLog->WriteLogFile(strListLog);
						bTotalResult = FALSE;
					}
				//}

// 				if (bResult)
// 				{
					GetPrivateProfileString(_T("LOG"), _T("vsr_ver"),			_T(""), szBuf,	MAX_PATH, strIniFIle);
					strTemp.Format(_T("%s"), szBuf);
					if (strvsr_ver == _T(""))
					{
						strvsr_ver.Format(_T("%s"), szBuf);
					}
					bResult = ComparePreAndNew(strIniFIle, strvsr_ver, strTemp, _T("vsr_ver"));
					if (!bResult)
					{
						strListLog.Format(_T("%s Base Data Fail"), szBuf);
						m_ListLog->WriteLogFile(strListLog);
						bTotalResult = FALSE;
					}
// 				}
// 
// 
// 				if (bResult)
// 				{
					GetPrivateProfileString(_T("LOG"), _T("build_num"),			_T(""), szBuf,	MAX_PATH, strIniFIle);
					strTemp.Format(_T("%s"), szBuf);
					if (strbuild_num == _T(""))
					{
						strbuild_num.Format(_T("%s"), szBuf);
					}
					bResult = ComparePreAndNew(strIniFIle, strbuild_num, strTemp, _T("build_num"));
					if (!bResult)
					{
						strListLog.Format(_T("%s Base Data Fail"), szBuf);
						m_ListLog->WriteLogFile(strListLog);
						bTotalResult = FALSE;
					}
// 				}
// 
// 
// 				if (bResult)
// 				{
					GetPrivateProfileString(_T("LOG"), _T("Build_Config"),		_T(""), szBuf,	MAX_PATH, strIniFIle);
					strTemp.Format(_T("%s"), szBuf);
					if (strBuild_Config == _T(""))
					{
						strBuild_Config.Format(_T("%s"), szBuf);
					}
					bResult = ComparePreAndNew(strIniFIle, strBuild_Config, strTemp, _T("Build_Config"));
					if (!bResult)
					{
						strListLog.Format(_T("%s Base Data Fail"), szBuf);
						m_ListLog->WriteLogFile(strListLog);
						bTotalResult = FALSE;
					}
// 				}
// 
// 				if (bResult)
// 				{
					GetPrivateProfileString(_T("LOG"), _T("Flex_Config"),		_T(""), szBuf,	MAX_PATH, strIniFIle);
					strTemp.Format(_T("%s"), szBuf);
					if (strFlex_Config == _T(""))
					{
						strFlex_Config.Format(_T("%s"), szBuf);
					}
					bResult = ComparePreAndNew(strIniFIle, strFlex_Config, strTemp, _T("Flex_Config"));
					if (!bResult)
					{
						strListLog.Format(_T("%s Base Data Fail"), szBuf);
						m_ListLog->WriteLogFile(strListLog);
						bTotalResult = FALSE;
					}
// 				}
// 
// 
// 				if (bResult)
// 				{
					GetPrivateProfileString(_T("LOG"), _T("Lens_Config"),	_T(""), szBuf,	MAX_PATH, strIniFIle);
					strTemp.Format(_T("%s"), szBuf);
					if (strLens_Config == _T(""))
					{
						strLens_Config.Format(_T("%s"), szBuf);
					}
					bResult = ComparePreAndNew(strIniFIle, strLens_Config, strTemp, _T("Lens_Config"));
					if (!bResult)
					{
						strListLog.Format(_T("%s Base Data Fail"), szBuf);
						m_ListLog->WriteLogFile(strListLog);
						bTotalResult = FALSE;
					}
// 				}
// 
// 
// 				if (bResult)
// 				{
					GetPrivateProfileString(_T("LOG"), _T("Substrate_Config"),	_T(""), szBuf,	MAX_PATH, strIniFIle);
					strTemp.Format(_T("%s"), szBuf);
					if (strSubstrate_Config == _T(""))
					{
						strSubstrate_Config.Format(_T("%s"), szBuf);
					}
					bResult = ComparePreAndNew(strIniFIle, strSubstrate_Config, strTemp, _T("Substrate_Config"));
					if (!bResult)
					{
						strListLog.Format(_T("%s Base Data Fail"), szBuf);
						m_ListLog->WriteLogFile(strListLog);
						bTotalResult = FALSE;
					}
// 				}
// 
// 				if (bResult)
// 				{
					GetPrivateProfileString(_T("LOG"), _T("IRCF_Config"),	_T(""), szBuf,	MAX_PATH, strIniFIle);
					strTemp.Format(_T("%s"), szBuf);
					if (strIRCF_Config == _T(""))
					{
						strIRCF_Config.Format(_T("%s"), szBuf);
					}
					bResult = ComparePreAndNew(strIniFIle, strIRCF_Config, strTemp, _T("IRCF_Config"));
					if (!bResult)
					{
						strListLog.Format(_T("%s Base Data Fail"), szBuf);
						m_ListLog->WriteLogFile(strListLog);
						bTotalResult = FALSE;
					}
// 				}
// 
// 
// 				if (bResult)
// 				{
					GetPrivateProfileString(_T("LOG"), _T("Stiffener_Config"),	_T(""), szBuf,	MAX_PATH, strIniFIle);
					strTemp.Format(_T("%s"), szBuf);
					if (strStiffener_Config == _T(""))
					{
						strStiffener_Config.Format(_T("%s"), szBuf);
					}
					bResult = ComparePreAndNew(strIniFIle, strStiffener_Config, strTemp, _T("Stiffener_Config"));
					if (!bResult)
					{
						strListLog.Format(_T("%s Base Data Fail"), szBuf);
						m_ListLog->WriteLogFile(strListLog);
						bTotalResult = FALSE;
					}
// 				}
// 
// 				if (bResult)
// 				{
					GetPrivateProfileString(_T("LOG"), _T("AA_Machine"),	_T(""), szBuf,	MAX_PATH, strIniFIle);
					strTemp.Format(_T("%s"), szBuf);
					if (strAA_Machine == _T(""))
					{
						strAA_Machine.Format(_T("%s"), szBuf);
					}
					bResult = ComparePreAndNew(strIniFIle, strAA_Machine, strTemp, _T("AA_Machine"));
					if (!bResult)
					{
						strListLog.Format(_T("%s Base Data Fail"), szBuf);
						m_ListLog->WriteLogFile(strListLog);
						bTotalResult = FALSE;
					}
				//}
			}
			else if (m_vFileVector[i].Find("_Register.ini") != -1)
			{
				strIniFIle = m_vFileVector[i];
				strIniFIle.Replace("_Register","");

				GetPrivateProfileString(_T("OTP_WRITE"), _T("NVM"),	_T(""), szBuf,	MAX_PATH, strIniFIle);
				strTemp.Format(_T("%s"), szBuf);
				if (strNVM == _T(""))
				{
					strNVM.Format(_T("%s"), szBuf);
				}
				bResult = ComparePreAndNew(strIniFIle, strNVM, strTemp, _T("NVM"));
				if (!bResult)
				{
					strListLog.Format(_T("%s Base Data Fail"), szBuf);
					m_ListLog->WriteLogFile(strListLog);
					bTotalResult = FALSE;
				}

// 				if(bResult)
// 				{
					GetPrivateProfileString(_T("OTP_WRITE"), _T("ProjectID"),	_T(""), szBuf,	MAX_PATH, strIniFIle);
					strTemp.Format(_T("%s"), szBuf);
					if (strProjectID == _T(""))
					{
						strProjectID.Format(_T("%s"), szBuf);
					}
					bResult = ComparePreAndNew(strIniFIle, strProjectID, strTemp, _T("ProjectID"));
					if (!bResult)
					{
						strListLog.Format(_T("%s Base Data Fail"), szBuf);
						m_ListLog->WriteLogFile(strListLog);
						bTotalResult = FALSE;
					}
// 				}
// 
// 				if (bResult)
// 				{
					GetPrivateProfileString(_T("OTP_WRITE"), _T("Project_Version"),	_T(""), szBuf,	MAX_PATH, strIniFIle);
					strTemp.Format(_T("%s"), szBuf);
					if (strProject_Version == _T(""))
					{
						strProject_Version.Format(_T("%s"), szBuf);
					}
					bResult = ComparePreAndNew(strIniFIle, strProject_Version, strTemp, _T("Project_Version"));
					if (!bResult)
					{
						strListLog.Format(_T("%s Base Data Fail"), szBuf);
						m_ListLog->WriteLogFile(strListLog);
						bTotalResult = FALSE;
					}
// 				}
// 
// 				if(bResult)
// 				{
					GetPrivateProfileString(_T("OTP_WRITE"), _T("Integrator"),		_T(""), szBuf,	MAX_PATH, strIniFIle);
					strTemp.Format(_T("%s"), szBuf);
					if (strIntegrator == _T(""))
					{
						strIntegrator.Format(_T("%s"), szBuf);
					}
					bResult = ComparePreAndNew(strIniFIle, strIntegrator, strTemp, _T("Integrator"));
					if (!bResult)
					{
						strListLog.Format(_T("%s Base Data Fail"), szBuf);
						m_ListLog->WriteLogFile(strListLog);
						bTotalResult = FALSE;
					}
// 				}
// 
// 				if(bResult)
// 				{
					GetPrivateProfileString(_T("OTP_WRITE"), _T("CameraBuild"),		_T(""), szBuf,	MAX_PATH, strIniFIle);
					strTemp.Format(_T("%s"), szBuf);
					if (strCameraBuild == _T(""))
					{
						strCameraBuild.Format(_T("%s"), szBuf);
					}
					bResult = ComparePreAndNew(strIniFIle, strCameraBuild, strTemp, _T("CameraBuild"));
					if (!bResult)
					{
						strListLog.Format(_T("%s Base Data Fail"), szBuf);
						m_ListLog->WriteLogFile(strListLog);
						bTotalResult = FALSE;
					}
// 				}
// 
// 				if (bResult)
// 				{
					GetPrivateProfileString(_T("OTP_WRITE"), _T("Config"),		_T(""), szBuf,	MAX_PATH, strIniFIle);
					strTemp.Format(_T("%s"), szBuf);
					if (strConfig == _T(""))
					{
						strConfig.Format(_T("%s"), szBuf);
					}
					bResult = ComparePreAndNew(strIniFIle, strConfig, strTemp, _T("Config"));
					if (!bResult)
					{
						strListLog.Format(_T("%s Base Data Fail"), szBuf);
						m_ListLog->WriteLogFile(strListLog);
						bTotalResult = FALSE;
					}
// 				}
// 
// 				if (bResult)
// 				{
					GetPrivateProfileString(_T("OTP_WRITE"), _T("IRCF"),		_T(""), szBuf,	MAX_PATH, strIniFIle);
					strTemp.Format(_T("%s"), szBuf);
					if (strIRCF == _T(""))
					{
						strIRCF.Format(_T("%s"), szBuf);
					}
					bResult = ComparePreAndNew(strIniFIle, strIRCF, strTemp, _T("IRCF"));
					if (!bResult)
					{
						strListLog.Format(_T("%s Base Data Fail"), szBuf);
						m_ListLog->WriteLogFile(strListLog);
						bTotalResult = FALSE;
					}
// 				}			
// 
// 				if (bResult)
// 				{
					GetPrivateProfileString(_T("OTP_WRITE"), _T("Substrate"),		_T(""), szBuf,	MAX_PATH, strIniFIle);
					strTemp.Format(_T("%s"), szBuf);
					if (strSubstrate == _T(""))
					{
						strSubstrate.Format(_T("%s"), szBuf);
					}
					bResult = ComparePreAndNew(strIniFIle, strSubstrate, strTemp, _T("Substrate"));
					if (!bResult)
					{
						strListLog.Format(_T("%s Base Data Fail"), szBuf);
						m_ListLog->WriteLogFile(strListLog);
						bTotalResult = FALSE;
					}
// 				}
// 
// 				//////////////////////////////////////////////////////////////////////////
// 				if (bResult)
// 				{
					GetPrivateProfileString(_T("OTP_WRITE"), _T("SensorType"),		_T(""), szBuf,	MAX_PATH, strIniFIle);
					strTemp.Format(_T("%s"), szBuf);
					if (strSensorType == _T(""))
					{
						strSensorType.Format(_T("%s"), szBuf);
					}
					bResult = ComparePreAndNew(strIniFIle, strSensorType, strTemp, _T("SensorType"));
					if (!bResult)
					{
						strListLog.Format(_T("%s Base Data Fail"), szBuf);
						m_ListLog->WriteLogFile(strListLog);
						bTotalResult = FALSE;
					}
// 				}			
// 
// 				if (bResult)
// 				{
					GetPrivateProfileString(_T("OTP_WRITE"), _T("Lens"),		_T(""), szBuf,	MAX_PATH, strIniFIle);
					strTemp.Format(_T("%s"), szBuf);
					if (strLens == _T(""))
					{
						strLens.Format(_T("%s"), szBuf);
					}
					bResult = ComparePreAndNew(strIniFIle, strLens, strTemp, _T("Lens"));
					if (!bResult)
					{
						strListLog.Format(_T("%s Base Data Fail"), szBuf);
						m_ListLog->WriteLogFile(strListLog);
						bTotalResult = FALSE;
					}
// 				}			
// 
// 				if (bResult)
// 				{
					GetPrivateProfileString(_T("OTP_WRITE"), _T("Flex"),		_T(""), szBuf,	MAX_PATH, strIniFIle);
					strTemp.Format(_T("%s"), szBuf);
					if (strFlex == _T(""))
					{
						strFlex.Format(_T("%s"), szBuf);
					}
					bResult = ComparePreAndNew(strIniFIle, strFlex, strTemp, _T("Flex"));
					if (!bResult)
					{
						strListLog.Format(_T("%s Base Data Fail"), szBuf);
						m_ListLog->WriteLogFile(strListLog);
						bTotalResult = FALSE;
					}
// 				}
// 
// 				if (bResult)
// 				{
					GetPrivateProfileString(_T("OTP_WRITE"), _T("Stiffener"),		_T(""), szBuf,	MAX_PATH, strIniFIle);
					strTemp.Format(_T("%s"), szBuf);
					if (strStiffener == _T(""))
					{
						strStiffener.Format(_T("%s"), szBuf);
					}
					bResult = ComparePreAndNew(strIniFIle, strStiffener, strTemp, _T("Stiffener"));
					if (!bResult)
					{
						strListLog.Format(_T("%s Base Data Fail"), szBuf);
						m_ListLog->WriteLogFile(strListLog);
						bTotalResult = FALSE;
					}
// 				}
// 
// 				if (bResult)
// 				{
					GetPrivateProfileString(_T("OTP_WRITE"), _T("Carrier"),		_T(""), szBuf,	MAX_PATH, strIniFIle);
					strTemp.Format(_T("%s"), szBuf);
					if (strCarrier == _T(""))
					{
						strCarrier.Format(_T("%s"), szBuf);
					}
					bResult = ComparePreAndNew(strIniFIle, strCarrier, strTemp, _T("Carrier"));
					if (!bResult)
					{
						strListLog.Format(_T("%s Base Data Fail"), szBuf);
						m_ListLog->WriteLogFile(strListLog);
						bTotalResult = FALSE;
					}
// 				}	
// 
// 				if (bResult)
// 				{
					GetPrivateProfileString(_T("OTP_WRITE"), _T("LensComponent_Revision_Major"),		_T(""), szBuf,	MAX_PATH, strIniFIle);
					strTemp.Format(_T("%s"), szBuf);
					if (strLensComponent_Revision_Major == _T(""))
					{
						strLensComponent_Revision_Major.Format(_T("%s"), szBuf);
					}
					bResult = ComparePreAndNew(strIniFIle, strLensComponent_Revision_Major, strTemp, _T("LensComponent_Revision_Major"));
					if (!bResult)
					{
						strListLog.Format(_T("%s Base Data Fail"), szBuf);
						m_ListLog->WriteLogFile(strListLog);
						bTotalResult = FALSE;
					}
// 				}
// 
// 				if (bResult)
// 				{
					GetPrivateProfileString(_T("OTP_WRITE"), _T("LensComponent_Revision_Minor"),		_T(""), szBuf,	MAX_PATH, strIniFIle);
					strTemp.Format(_T("%s"), szBuf);
					if (strLensComponent_Revision_Minor == _T(""))
					{
						strLensComponent_Revision_Minor.Format(_T("%s"), szBuf);
					}
					bResult = ComparePreAndNew(strIniFIle, strLensComponent_Revision_Minor, strTemp, _T("LensComponent_Revision_Minor"));
					if (!bResult)
					{
						strListLog.Format(_T("%s Base Data Fail"), szBuf);
						m_ListLog->WriteLogFile(strListLog);
						bTotalResult = FALSE;
					}
// 				}
// 
// 				if (bResult)
// 				{
					GetPrivateProfileString(_T("OTP_WRITE"), _T("ColorShading_Revision"),		_T(""), szBuf,	MAX_PATH, strIniFIle);
					strTemp.Format(_T("%s"), szBuf);
					if (strColorShading_Revision == _T(""))
					{
						strColorShading_Revision.Format(_T("%s"), szBuf);
					}
					bResult = ComparePreAndNew(strIniFIle, strColorShading_Revision, strTemp, _T("ColorShading_Revision"));
					if (!bResult)
					{
						strListLog.Format(_T("%s Base Data Fail"), szBuf);
						m_ListLog->WriteLogFile(strListLog);
						bTotalResult = FALSE;
					}
// 				}
// 
// 				if (bResult)
// 				{
					int nTemp = GetPrivateProfileInt(_T("OTP_WRITE"), _T("CISMaskID"),	0, strIniFIle);
					strTemp.Format(_T("%d"), nTemp);
					if (strCISMaskID == _T(""))
					{
						strCISMaskID.Format(_T("%d"), nTemp);
					}

					bResult = ComparePreAndNew(strIniFIle, strCISMaskID, strTemp, _T("CISMaskID"));
					if (!bResult)
					{
						strListLog.Format(_T("%s Base Data Fail"), szBuf);
						m_ListLog->WriteLogFile(strListLog);
						bTotalResult = FALSE;
					}
				//}
			}
		}

		if (j == 0)
		{
			nAddListCtrl = 1;
		}
		else
		{
			nAddListCtrl = nAddListCtrl + vDirCount[j-1] + 3;
		}

		if (bTotalResult)
			m_ListCtrl->SetItem(nAddListCtrl,2,LVIF_TEXT,  _T("PASS"),0,0,0,NULL);
		else
			m_ListCtrl->SetItem(nAddListCtrl,2,LVIF_TEXT,  _T("FAIL"),0,0,0,NULL);
		m_ListCtrl->SetItem(nAddListCtrl,3,LVIF_TEXT,  _T("100%"),0,0,0,NULL);
		m_ListCtrl->EnsureVisible(nAddListCtrl,TRUE);
		m_ListCtrl->Update(nAddListCtrl);
		bTotalResult = TRUE;
	}
}

BOOL DataController::ComparePreAndNew(CString inFilePath, CString inPre, CString inNew, CString inType)
{
	BOOL bResult = TRUE;
	CString strListLog;

	if (inNew.Find(inPre) == -1)
	{
		int nFileName = inFilePath.ReverseFind('\\');

		CompareResult* cFailItem = new CompareResult;
		cFailItem->SetFileName(inFilePath.Mid(nFileName+1));

		int nDirName = inFilePath.Left(nFileName).ReverseFind('\\');
		CString strDir = inFilePath.Left(nFileName).Mid(nDirName+1);
		CString strTestName;
		strTestName.Format(_T(""));

		AfxExtractSubString(strTestName, strDir, 5, '_');

		CompareResult* cFailItem1 = new CompareResult;
		cFailItem1->SetTestName(strTestName);
		m_pListDifferentResult.AddTail(cFailItem1);
		m_pListLogData.AddTail(cFailItem1);

		m_pListDifferentResult.AddTail(cFailItem);
		m_pListLogData.AddTail(cFailItem);

		CompareResult* cFailItem2 = new CompareResult;
		cFailItem2->SetItemName(inType);
		cFailItem2->SetCompareResult(FALSE);
		cFailItem2->SetBaseInfoValue(inPre);
		cFailItem2->SetCurrentInfoValue(inNew);
		m_pListDifferentResult.AddTail(cFailItem2);
		m_pListLogData.AddTail(cFailItem2);

		strListLog.Format("%s : %s, %s Mismatch!",inFilePath, inPre, inNew);
		m_ListLog->WriteLogFile(strListLog);
		m_pFailItems->AddFailItem(inNew, inFilePath);
		bResult = FALSE;
	}
	return bResult;
}

bool DataController::CheckNamingRule()
{
	bool bResult = FALSE;
	CString strIniFIle;
	CString strIniFlex;
	CString strIniLens;
	CString strIniSubstrate;
	CString strIniIRCF;
	CString strIniStiffener;
	CString strIniCarrier;

	strIniFlex.Format(_T(""));
	strIniLens.Format(_T(""));	
	strIniSubstrate.Format(_T(""));
	strIniIRCF.Format(_T(""));	
	strIniStiffener.Format(_T(""));	
	strIniCarrier.Format(_T(""));
	
	TCHAR szBuf[MAX_PATH] = {0,};

	std::vector<bool> vResult;

	for (int nConfigFileCount = 0; nConfigFileCount < m_vRootDIr.size(); nConfigFileCount++)
	{
		int nDirCount = 0;
		int nRealDir = 0;
		int nFileCount = 0;
		int nStartIndex = -1;
		int nEndIndex = -1;
		int nStartFileIndex = -1;
		int nEndFileIndex = -1;

		CFileFind pFinder;

		for (int i = 0; i < m_vDirVector.size(); i++)
		{
			if (m_vDirVector[i].Find(m_vRootDIr[nConfigFileCount]) != -1)
			{
				if (nStartIndex == -1)
				{
					nStartIndex = i;
				}

				CString	strRefDirName = m_vDirVector[i];
				int nCount = strRefDirName.ReverseFind('\\');
				strRefDirName = strRefDirName.Mid(nCount+1);

				CString strTempFilePath;
				strTempFilePath.Format(_T("%s\\%s%s"),m_vDirVector[i],strRefDirName,_T(".ini"));
				if(pFinder.FindFile(strTempFilePath))
				{
					nRealDir++;
				}
				nDirCount++;
			}
		}

		for (int i = 0; i < m_vFileVector.size(); i++)
		{
			if (m_vFileVector[i].Find(m_vRootDIr[nConfigFileCount]) != -1)
			{
				if (nStartFileIndex == -1)
				{
					nStartFileIndex = i;
				}
				nFileCount++;
			}
		}

		nEndIndex = nStartIndex + nDirCount - 1;
		nEndFileIndex = nStartFileIndex + nFileCount - 1;

		for (int i = nStartFileIndex; i < nEndFileIndex; i++)
		{
			strIniFIle.Format("%s",m_vFileVector[i]);

			if (strIniFIle.Find("ItemVersion.ini") != -1)
			{	
				GetPrivateProfileString(_T("LOG"), _T("Flex_Config"),		_T(""), szBuf,	MAX_PATH, strIniFIle);
				strIniFlex.Format(_T("%s"), szBuf);
				GetPrivateProfileString(_T("LOG"), _T("Lens_Config"),		_T(""), szBuf,	MAX_PATH, strIniFIle);
				strIniLens.Format(_T("%s"), szBuf);
				GetPrivateProfileString(_T("LOG"), _T("Substrate_Config"),	_T(""), szBuf,	MAX_PATH, strIniFIle);
				strIniSubstrate.Format(_T("%s"), szBuf);
				GetPrivateProfileString(_T("LOG"), _T("IRCF_Config"),		_T(""), szBuf,	MAX_PATH, strIniFIle);
				strIniIRCF.Format(_T("%s"), szBuf);
				GetPrivateProfileString(_T("LOG"), _T("Stiffener_Config"),	_T(""), szBuf,	MAX_PATH, strIniFIle);
				strIniStiffener.Format(_T("%s"), szBuf);
				GetPrivateProfileString(_T("LOG"), _T("Carrier_Config"),	_T(""), szBuf,	MAX_PATH, strIniFIle);
				strIniCarrier.Format(_T("%s"), szBuf);
				break;
			}
		}
		CString strListLog;
		strListLog.Format(_T("Flex : %s"), strIniFlex);
		m_ListLog->WriteLogFile(strListLog);

		strListLog.Format(_T("Lens : %s"), strIniLens);
		m_ListLog->WriteLogFile(strListLog);

		strListLog.Format(_T("Substrate : %s"), strIniSubstrate);
		m_ListLog->WriteLogFile(strListLog);

		strListLog.Format(_T("IRCF : %s"), strIniIRCF);
		m_ListLog->WriteLogFile(strListLog);

		strListLog.Format(_T("Stiffener : %s"), strIniStiffener);
		m_ListLog->WriteLogFile(strListLog);

		strListLog.Format(_T("Carrier : %s"), strIniCarrier);
		m_ListLog->WriteLogFile(strListLog);

		// 현재 디렉토리 가져오기
		CString strEXEPath;
		strEXEPath.Format("");
		CString strINIPath;
		strINIPath.Format("");

		strEXEPath = GetEXEDirectoryPath();

		strINIPath.Format(_T("%s%s"), strEXEPath,_T("\\Data\\NamingRule.ini"));

		CString strFlexInitial;
		CString strLensInitial;
		CString strSubstrateInitial;
		CString strIRCFInitial;
		CString strStiffnerInitial;
		CString strCarrierInitial;

		strFlexInitial.Format(_T(""));
		strLensInitial.Format(_T(""));
		strSubstrateInitial.Format(_T(""));
		strIRCFInitial.Format(_T(""));
		strStiffnerInitial.Format(_T(""));
		strCarrierInitial.Format(_T(""));

		// ini 파일에 적힌 이니셜 읽어오기

		GetPrivateProfileString(_T("Flex_Config"),		LPSTR(LPCTSTR(strIniFlex)),		_T(""), szBuf,	MAX_PATH, strINIPath);
		strFlexInitial.Format(_T("%s"), szBuf);

		GetPrivateProfileString(_T("Lens_Config"),		LPSTR(LPCTSTR(strIniLens)),		_T(""), szBuf,	MAX_PATH, strINIPath);
		strLensInitial.Format(_T("%s"), szBuf);

		GetPrivateProfileString(_T("Substrate_Config"),	LPSTR(LPCTSTR(strIniSubstrate)),_T(""), szBuf,	MAX_PATH, strINIPath);
		strSubstrateInitial.Format(_T("%s"), szBuf);

		GetPrivateProfileString(_T("IRCF_Config"),		LPSTR(LPCTSTR(strIniIRCF)),		_T(""), szBuf,	MAX_PATH, strINIPath);
		strIRCFInitial.Format(_T("%s"), szBuf);

		GetPrivateProfileString(_T("Stiffener_Config"),	LPSTR(LPCTSTR(strIniStiffener)),_T(""), szBuf,	MAX_PATH, strINIPath);
		strStiffnerInitial.Format(_T("%s"), szBuf);

		GetPrivateProfileString(_T("Carrier_Config"),	LPSTR(LPCTSTR(strIniCarrier)),	_T(""), szBuf,	MAX_PATH, strINIPath);
		strCarrierInitial.Format(_T("%s"), szBuf);


		strListLog.Format(_T("%s : %s"), strIniFlex , strFlexInitial);
		m_ListLog->WriteLogFile(strListLog);

		strListLog.Format(_T("%s : %s"), strIniLens, 	strLensInitial);
		m_ListLog->WriteLogFile(strListLog);

		strListLog.Format(_T("%s : %s"), strIniSubstrate, strSubstrateInitial);
		m_ListLog->WriteLogFile(strListLog);

		strListLog.Format(_T("%s : %s"), strIniIRCF, strIRCFInitial	);
		m_ListLog->WriteLogFile(strListLog);

		strListLog.Format(_T("%s : %s"), strIniStiffener, strStiffnerInitial);
		m_ListLog->WriteLogFile(strListLog);

		strListLog.Format(_T("%s : %s"), strIniCarrier, strCarrierInitial);
		m_ListLog->WriteLogFile(strListLog);


		// Ref Name combination
		CString strReferenceName;
		strReferenceName.Format("%s%s%s_%s%s%s",strFlexInitial, strLensInitial, strSubstrateInitial, strCarrierInitial, strIRCFInitial, strStiffnerInitial);
		CString strRefDirName;
		strRefDirName.Format(_T(""));

		CString strRefTemp;

		int nCount = 0;

		CFileFind pFind;

		bool bFailFlag = false;

		for(int i = nStartIndex; i < nEndIndex; i++)
		{
			strRefDirName = m_vDirVector[i];
			nCount = strRefDirName.ReverseFind('\\');
			strRefDirName = strRefDirName.Mid(nCount+1);

			if(strRefDirName.Find(strReferenceName) != -1)
			{
				strListLog.Format(_T("Naming Rule Check PASS %s : %s"), strRefDirName, strReferenceName);
				m_ListLog->WriteLogFile(strListLog);
			}
			else
			{
				CString strTempFilePath;
				strTempFilePath.Format(_T("%s\\%s%s"),m_vDirVector[i],strRefDirName,_T(".ini"));
				if(pFind.FindFile(strTempFilePath))
				{
					strListLog.Format(_T("Naming Rule Check FAIL %s : %s"), strRefDirName, strReferenceName);
					m_ListLog->WriteLogFile(strListLog);
					m_pFailItems->AddFailItem(strReferenceName,strRefDirName);
					bFailFlag = true;
				}			
			}
		}

		int nAddListCtrl = 0;

		if (nConfigFileCount == 0)
		{
			nAddListCtrl = 2;
		}
		else
		{
			nAddListCtrl = nDirCount - nRealDir + 1;
		}

		if (bFailFlag)
		{
			m_ListCtrl->SetItem(nStartIndex + nAddListCtrl,2,LVIF_TEXT,  _T("FAIL"),0,0,0,NULL);
			m_ListCtrl->SetItem(nStartIndex + nAddListCtrl,3,LVIF_TEXT,  _T("100%"),0,0,0,NULL);
			m_ListCtrl->EnsureVisible(nStartIndex + nAddListCtrl,TRUE);
			vResult.push_back(false);
		}
		else
		{
			m_ListCtrl->SetItem(nStartIndex + nAddListCtrl,2,LVIF_TEXT,  _T("PASS"),0,0,0,NULL);
			m_ListCtrl->SetItem(nStartIndex + nAddListCtrl,3,LVIF_TEXT,  _T("100%"),0,0,0,NULL);
			m_ListCtrl->EnsureVisible(nStartIndex + nAddListCtrl,TRUE);
			vResult.push_back(true);
		}
		m_ListCtrl->Update(nStartIndex + nAddListCtrl + 2);
	}

	return bResult;
}

void DataController::SetProgressBar(CProgressCtrl* inData)
{
	m_ProgressBar = inData;
}

void DataController::SetFailItemPointer(FailItem* inData)
{
	m_pFailItems = inData;
}

bool DataController::SearchTestInTarget(CString inTargetConfig, CString inTest,TestType*& outTarget)
{
	bool bResult = false;
	
	POSITION pTemp = NULL;
	POSITION pPos = m_pListTargetRefConfig.GetHeadPosition();

	while(pPos && m_pListTargetRefConfig.GetSize()>0)
	{
		pTemp = pPos;
		ConfigType* temp = m_pListTargetRefConfig.GetNext(pPos);

		if(temp->GetInputDirPath().Find(inTargetConfig) != -1)
		{
			temp->SearchTestInList(inTest, outTarget);
		}
	}

	return bResult;
}


bool DataController::SearchTestInBase(CString inTargetConfig, CString inTest,TestType*& outTarget)
{
	bool bResult = false;

	POSITION pTemp = NULL;
	POSITION pPos = m_pListConfig.GetHeadPosition();

	while(pPos && m_pListConfig.GetSize()>0)
	{
		pTemp = pPos;
		ConfigType* temp = m_pListConfig.GetNext(pPos);

		bResult = temp->SearchTestInList(inTest, outTarget);
	}

	return bResult;
}


bool DataController::SearchTestInSetting(CString inTargetConfig, CString inTest,TestType*& outTarget)
{
	bool bResult = false;

	POSITION pTemp = NULL;
	POSITION pPos = m_pListSetting.GetHeadPosition();

	while(pPos && m_pListSetting.GetSize()>0)
	{
		pTemp = pPos;
		ConfigType* temp = m_pListSetting.GetNext(pPos);

		bResult = temp->SearchTestInList(inTest, outTarget);
	}

	return bResult;
}

void DataController::GetDefferentResult(CList<CompareResult*>& outDifferent)
{
	POSITION pPos;

	pPos = m_pListDifferentResult.GetHeadPosition();

	while(pPos)
	{
		CompareResult* cTemp = m_pListDifferentResult.GetNext(pPos);
		outDifferent.AddTail(cTemp);
	}
}

void DataController::InitDifferentResultList()
{
	m_pListDifferentResult.RemoveAll();
}