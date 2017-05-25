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
					bRefFile = true;					
					strListLog.Format(_T("%s%s"),strRefFile, _T(": OK"));
					//m_ListLogDlg.AddListLog(strListLog);
				}
				else if(strFileName == strRegister)
				{
					strListLog.Format(_T("%s%s"),strRegister, _T(": OK"));
					//m_ListLogDlg.AddListLog(strListLog);
					bRegister = true;
				}
				else if(strFileName == _T("Spec.ini"))
				{
					strListLog.Format(_T("%s%s"),strFileName, _T(": OK"));
					//m_ListLogDlg.AddListLog(strListLog);
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
				//m_ListLogDlg.AddListLog(strListLog);
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

void DataController::DeleteFilPath(CString inTarget)
{
	int nDelCount = 0;
	int nIndex = m_vFileVector.size();

	for (int i= 0; i< nIndex ; i++)
	{
		if (m_vFileVector[nDelCount].Find(inTarget))
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
		if (m_vDirVector[nDelCount].Find(inTarget))
		{
			m_vDirVector.erase(m_vDirVector.begin()+nDelCount);
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

	// Read Target Reference 
	m_ListLog->WriteLogFile(_T("Read Target Reference Start"));
	ReadReference();
	m_ListLog->WriteLogFile(_T("Read Target Reference End"));

	// Read Base Reference
	m_ListLog->WriteLogFile(_T("Read Base Reference Start"));
	LoadXMLDataFiles(inData);
	m_ListLog->WriteLogFile(_T("Read Base Reference End"));

	std::vector<CString> vTemp;
	// Compare
	m_ListLog->WriteLogFile(_T("======================Compare Reference Start======================"));
	CompareReference(vTemp, m_pListCompareResult);
	m_ListLog->WriteLogFile(_T("======================Compare Reference End======================"));

	// Ref Naming rule checking
	
	// CRC 계산
	
	// 공동 데이터 확인

	// Result Log 쓰기
	WriteResultLog();

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
	pAddValue->LoadDataFiles(strValuePath);

	m_ListLog->WriteLogFile(_T("LoadDataFiles") + strSettingPath);
	pAddSetting->SetListLog(m_ListLog);
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
	pPos = m_pListCompareResult.GetHeadPosition();

	while(pPos && m_pListCompareResult.GetSize()>0)
	{
		pTemp = pPos;

		CompareResult* temp = m_pListCompareResult.GetNext(pPos);
		delete temp;
		m_pListCompareResult.RemoveAt(pTemp);
	}
}


void DataController::GetValueXMLFileList(std::vector<CString>& outData)
{
	outData.clear();

	outData.assign(m_vValueFileList.begin(), m_vValueFileList.end());
}


BOOL DataController::CompareReference(std::vector<CString> outResult, CList<CompareResult*>& outDifferent)
{
	BOOL bResult = FALSE;
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
			
			outDifferent.AddTail(cNewConfig);

			pTargetRef->ConfigCompare(pBaseRef, vFailList, outDifferent);
		}
	}

	for (int i =0; i < vFailList.size(); i++)
	{
		m_ListLog->WriteLogFile(vFailList[i]);
	}

	return bResult;
}

void DataController::SetListLog(ListLog* inData)
{
	m_ListLog = inData;
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
	pPos = m_pListCompareResult.GetHeadPosition();
	while(pPos && outData.GetSize()>0)
	{
		pTemp = pPos;

		CompareResult* temp = m_pListCompareResult.GetNext(pPos);
		outData.AddTail(temp);
	}
}

void DataController::WriteResultLog()
{
	CString strExePath = GetEXEDirectoryPath();
	CString strLogDirPath;
	strLogDirPath.Format("%s%s", strExePath,_T("\\ResultLog"));
	CString strLogPath;
	FILE* file;

	m_ListLog->WriteLogFile(_T("===============Start Writing Log==============="));

	CreateDirectory(strLogDirPath,NULL);
	do 
	{
		COleDateTime currentTime;
		currentTime = COleDateTime::GetCurrentTime();
		
		strLogPath.Format(_T("%s\\Result_%04d%02d%02d_%02d%02d%02d.csv"),strLogDirPath, currentTime.GetYear(), currentTime.GetMonth(), currentTime.GetDay(), currentTime.GetHour(), currentTime.GetMinute(), currentTime.GetSecond() );
		
		m_ListLog->WriteLogFile(strLogPath);

		file = fopen(strLogPath,"w+");

		POSITION pTemp = NULL;
		POSITION pPos = m_pListCompareResult.GetHeadPosition();
		CString strComma,strReturn;
		strComma.Format(",");
		strReturn.Format("\n");
		CString strLogData;
		strLogData.Format("");

		std::vector<CString> vHeader;
		std::vector<CString> vBase;
		std::vector<CString> vCurrent;
		std::vector<CString> vResult;

		while(pPos && m_pListCompareResult.GetSize()>0)
		{
			pTemp = pPos;
			CompareResult* temp = m_pListCompareResult.GetNext(pPos);

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

				CString strValue;
				strValue.Format(_T(""));
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
				}
			}
					

			if(bHeaderEnd && bBaseEnd && bCurrentEnd && bResultEnd)
			{
				bWorking = false;
			}
		}while(bWorking);

		fclose(file);
	} while (FALSE);

	m_ListLog->WriteLogFile(_T("===============End Writing Log==============="));
}