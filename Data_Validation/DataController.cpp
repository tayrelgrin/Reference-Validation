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
	CString strError = "";

	std::vector<bool> vResult;

	nDirCount = vTestDirPath.size();

	if (nDirCount > 3)
	{
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
					}
					else if(strFileName == strRegister)
					{
						bRegister = true;
					}
					else if(strFileName == "Spec.ini")
					{
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