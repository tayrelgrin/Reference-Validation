#include "StdAfx.h"
#include "DataController.h"


DataController::DataController(void)
{
}


DataController::~DataController(void)
{
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

	strFileName.Format("");
	strDirName.Format("");
	strDirPath.Format("");
	strRegister.Format("");
	strRefFile.Format("");
	strError.Format("");
	strListLog.Format("");

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

		strRefFile	= strDirName + ".ini";
		strRegister = strDirName + "_Register.ini";
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
					strListLog.Format("%s%s",strRefFile, ": OK");
					//m_ListLogDlg.AddListLog(strListLog);
				}
				else if(strFileName == strRegister)
				{
					strListLog.Format("%s%s",strRegister, ": OK");
					//m_ListLogDlg.AddListLog(strListLog);
					bRegister = true;
				}
				else if(strFileName == "Spec.ini")
				{
					strListLog.Format("%s%s",strFileName, ": OK");
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
				strListLog.Format("%s%s",strFileName, ": Fail");
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
	strEXEDirectory.Format("");

	m_vConfigName.clear();

	strEXEDirectory = cTempConfig.GetEXEDirectoryPath();

	strEXEDirectory += "\\Data\\Value";

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

		m_vConfigName.push_back(strComb);
	}
}

void DataController::ParsingBBCD(CString inStr, CString& outStrPrj, CString& outStrBuild, CString& outStrConfig, CString& outStrDOE)
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

void DataController::GetTestNameFromTestDirNameVector(static std::vector<CString> invData, std::vector<CString>& outvData)
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

	temp.Format("");
	temp1.Format("%s", invData[0]);


	AfxExtractSubString(temp, temp1, 4, '_');
	
	strConfig = temp;
}



void DataController::ReadReference()
{
	CString strDir, strRootPath;
	strDir.Format("");
	strRootPath.Format("");

	std::vector<CString> vConfig;

	int nIndex = 0;
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

	m_pTargetRef->AddNewTest(inData);
	m_pListTargetRefConfig.AddTail(m_pTargetRef);
}

BOOL DataController::Validation()
{
	ReadReference();

	return TRUE;
}

void DataController::AddRootPath(CString inData)
{
	m_vRootDIr.push_back(inData);
}