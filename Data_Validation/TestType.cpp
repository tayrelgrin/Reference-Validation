#include "StdAfx.h"
#include "TestType.h"


TestType::TestType(void)
{
	m_pFIleList.RemoveAll();
}


TestType::~TestType(void)
{
	InitList();
}

void TestType::InitList()
{
	POSITION pTemp = NULL;
	POSITION pPos = m_pFIleList.GetHeadPosition();

	while(pPos && m_pFIleList.GetSize()>0)
	{
		pTemp = pPos;

		try
		{
			FileType* temp = m_pFIleList.GetNext(pPos);
			delete temp;
			m_pFIleList.RemoveAt(pTemp);
		}
		catch (CMemoryException* e)
		{
			e->Delete();
		}
	}

	if( m_pFIleList.GetSize()>0)
		m_pFIleList.RemoveAll();
}

void TestType::SetTestName(CString inData)
{
	m_strTestName = inData;
}

CString TestType::GetTestName()
{
	return m_strTestName;
}

void TestType::AddNewFile(CString inStrFileName)
{
	FileType* newFile = new FileType;
	
	newFile->SetFileName(inStrFileName);
	m_pFIleList.AddTail(newFile);
}

void TestType::AddNewFile(FileType* inData)
{
	m_pFIleList.AddTail(inData);
}

void TestType::AddNewTest(CString inPath, std::vector<CString> invBasicFile, int inNInput)
{
	std::vector<CString> vFilePath;
	bool bInputResult = false;

	GetFilePathInDir(inPath, vFilePath);

	for (int i = 0; i< vFilePath.size(); i++)
	{
		bInputResult = false;
		FileType* cNewFile = new FileType();				// 객체 생성
		CString strFilePath;
		strFilePath.Format(_T("%s"),vFilePath[i]);
		int nIndex = strFilePath.ReverseFind('\\');			// 파일 이름 인덱스
		
		cNewFile->SetFileName(strFilePath.Mid(nIndex+1));	// 파일 이름 분류
		cNewFile->AddNewData(vFilePath[i], inNInput);		// 파일 이름 적용

		if (invBasicFile.size() > 0 && inNInput!= 2)
		{
			for(int j = 0; j<invBasicFile.size(); j++)
			{
				if(cNewFile->GetFileName().Find(invBasicFile[j]) != -1)
				{
					m_pFIleList.AddTail(cNewFile);
					bInputResult = true;
					break;
				}
			}
		}
		else
		{
			m_pFIleList.AddTail(cNewFile);
			bInputResult = true;
		}
		if (!bInputResult)
		{
			delete cNewFile;
		}
	}
	

	vFilePath.clear();
}

void TestType::GetFilePathInDir(CString inPath, std::vector<CString>& outvData)
{
	CFileFind cFinder;

	CString fileName;
	CString tpath;
	BOOL bWorking;

	fileName.Format(_T(""));
	tpath.Format(_T(""));

	tpath.Format(inPath +"\\*.*");

	bWorking = cFinder.FindFile(tpath);

	while (bWorking)
	{
		bWorking = cFinder.FindNextFile();
		//파일 일때
		if (cFinder.IsArchived())
		{
			//파일의 이름
			CString _fileName =  cFinder.GetFileName();

			// 현재폴더 상위폴더 썸네일파일은 제외
			if( _fileName == _T(".") || 
				_fileName == _T("..")|| 
				_fileName == _T("Thumbs.db") ) continue;

			fileName =  cFinder.GetFilePath();
			outvData.push_back(fileName);
		}
	}

	cFinder.Close();
}

void TestType::SaveDataToFile(tinyxml2::XMLDocument& cXMLDoc, tinyxml2::XMLElement* cElement, std::vector<CString> invBasicFile)
{
	tinyxml2::XMLElement* Element;
	if(m_strTestName != "")
	{
 		if(m_strTestName.Find('\\') != -1)
 			m_strTestName.Replace('\\',':');

		Element = cXMLDoc.NewElement(LPSTR(LPCTSTR(m_strTestName)));

		cElement->LinkEndChild(Element);

		POSITION pos = m_pFIleList.GetHeadPosition();

		while(pos)
		{
			FileType* pData = m_pFIleList.GetNext(pos);
			if (invBasicFile.size() > 0)
			{
				for(int i = 0; i<invBasicFile.size(); i++)
				{
					if(pData->GetFileName().Find(invBasicFile[i]) != -1)
					{
						pData->SaveDataToFile(cXMLDoc, Element);
						break;
					}
				}
			}
			else
				pData->SaveDataToFile(cXMLDoc, Element);
		}
	}	
}

void TestType::SaveBaseInfoToFile(tinyxml2::XMLDocument& cXMLDoc, tinyxml2::XMLElement* cElement, CList<BasicData*> inData)
{
	tinyxml2::XMLElement* Element;
	if(m_strTestName != "")
	{
		if(m_strTestName.Find('\\') != -1)
			m_strTestName.Replace('\\',':');

		Element = cXMLDoc.NewElement(LPSTR(LPCTSTR(m_strTestName)));

		cElement->LinkEndChild(Element);

		POSITION pos = inData.GetHeadPosition();

		while(pos)
		{
			BasicData* pData = inData.GetNext(pos);
		
			break;
		}
	}	
}

void TestType::LoadDataFromXML(tinyxml2::XMLNode* pParent, CString inStrFileName, FileType* pNewTest)
{
	tinyxml2::XMLNode* pNode;
	tinyxml2::XMLElement* pElent;
	tinyxml2::XMLAttribute* pAttr;

	for (pNode = (tinyxml2::XMLNode*)pParent->FirstChild(); pNode != 0; pNode = (tinyxml2::XMLNode*)pNode->NextSibling())
	{
		if(pElent = pNode->ToElement())
		{
			if(pAttr = (tinyxml2::XMLAttribute*)pElent->FirstAttribute())
			{
				if(pNewTest==nullptr)
					pNewTest = new FileType;

				pNewTest->SetFileName(inStrFileName);
				pNewTest->LoadDataFromXML((tinyxml2::XMLAttribute*)pAttr);
			}
			else
			{
				if(pNewTest==nullptr)
					pNewTest = new FileType;
				
				LoadDataFromXML(pElent, (CString)pNode->Value(), pNewTest);
				m_pFIleList.AddTail(pNewTest);
				pNewTest = nullptr;
			}
		}
	}
}


void TestType::GetFileNames(CString inTestName ,std::vector<CString>& outvFileNames)
{
	POSITION pPos = m_pFIleList.GetHeadPosition();
	CString strFileName;
	strFileName.Format(_T(""));
	while(pPos)
	{
		FileType* temp = m_pFIleList.GetNext(pPos);
		strFileName = temp->GetFileName();
		strFileName = inTestName + ":" + strFileName;

		outvFileNames.push_back(strFileName);
	}
}

bool TestType::SearchFileInList(CString inStrTargetFile, FileType& outData)
{
	POSITION pPos = m_pFIleList.GetHeadPosition();
	CString strFileName;
	strFileName.Format(_T(""));
	bool bResult=false;

	while(pPos)
	{
		FileType* temp = m_pFIleList.GetNext(pPos);
		strFileName = temp->GetFileName();

		if (strFileName.Find(inStrTargetFile) != -1)
		{
			temp->CopyData(outData);
			bResult = true;
			break;
		}
	}
	return bResult;
}


void TestType::ModifyData(CString inTargetFileName, BasicData* inTarget)
{
	POSITION pPos = m_pFIleList.GetHeadPosition();
	CString strFileName;
	strFileName.Format(_T(""));
	bool bResult=false;

	while(pPos)
	{
		FileType* temp = m_pFIleList.GetNext(pPos);
		strFileName = temp->GetFileName();

		if (strFileName.Find(inTargetFileName) != -1)
		{
			temp->ModifyData(inTarget);
			break;
		}
	}

}

void TestType::ChangeFileName(CString inTargetFileName, CString inNewFileName)
{
	POSITION pPos = m_pFIleList.GetHeadPosition();
	CString strFileName;
	strFileName.Format(_T(""));

	while(pPos)
	{
		FileType* temp = m_pFIleList.GetNext(pPos);
		strFileName = temp->GetFileName();

		if (strFileName.Find(inTargetFileName) != -1)
		{
			temp->SetFileName(inNewFileName);
		}
	}
}

void TestType::SetListLog(ListLog* inData)
{
	m_ListLog = inData;
}

bool TestType::CompareTest(TestType* inTarget, std::vector<CString>& outFail, CList<CompareResult*>& outLogData,CList<CompareResult*>& outResult, bool inBasicCheck)
{
	bool bResult = false;
	bool bFileCount = false;

	//////////////////////////////////////////////////////////////////////////
	// file name 가져오기
	//////////////////////////////////////////////////////////////////////////
	std::vector<CString> vTargetFileName;
	std::vector<CString> vBaseFileName;
	CString strTargetRef, strTargetRegister;
	CString strBaseRef, strBaseRegister;
	strTargetRef.Format(_T(""));
	strTargetRegister.Format(_T(""));
	strBaseRef.Format(_T(""));
	strBaseRegister.Format(_T(""));

	inTarget->GetFileNames(m_strTestName,vTargetFileName);
	this->GetFileNames(m_strTestName,vBaseFileName);

	//////////////////////////////////////////////////////////////////////////
	// Ref, Register 파일
	//////////////////////////////////////////////////////////////////////////
	for(int i=0; i<vTargetFileName.size(); i++)
	{
		if (vTargetFileName[i].Find(_T("_Register")) != -1)
		{
			CString strRefFile;
			strRefFile.Format(_T(""));
			strRefFile = vTargetFileName[i];
			strRefFile.Replace(_T("_Register"),_T(""));

			strTargetRef = strRefFile;
			strTargetRegister = vTargetFileName[i];
			break;
		}
	}
	for(int i=0; i<vBaseFileName.size(); i++)
	{
		if (vBaseFileName[i].Find(_T("_Register")) != -1)
		{
			CString strRefFile;
			strRefFile.Format(_T(""));
			strRefFile = vBaseFileName[i];
			strRefFile.Replace(_T("_Register"),_T(""));

			strBaseRef = strRefFile;
			strBaseRegister = vBaseFileName[i];
			break;
		}
	}

	int nFilecount = 0;
	CString strBaseRefFile, strTargetRefFile;
	strBaseRefFile.Format(_T(""));
	strTargetRefFile.Format(_T(""));

	for(int i = 0; i < vBaseFileName.size(); i++)
	{
		if (vBaseFileName[i].Find(_T("_Register")) != -1)
		{
			strBaseRefFile = vBaseFileName[i];
			strBaseRefFile.Replace(_T("_Register"),_T(""));
		}
	}

	for(int i = 0; i < vTargetFileName.size(); i++)
	{
		if (vTargetFileName[i].Find(_T("_Register")) != -1)
		{
			strTargetRefFile = vTargetFileName[i];
			strTargetRefFile.Replace(_T("_Register"),_T(""));
		}
	}

	for(int i = 0; i < vBaseFileName.size(); i++)
	{
		for(int j = 0; j < vTargetFileName.size(); j++)
		{
			if(vBaseFileName[i] == vTargetFileName[j])
			{
				nFilecount++;
				break;
			}
			else if(vBaseFileName[i].Find(_T("_Register")) != -1 && vTargetFileName[j].Find(_T("_Register")) != -1)
			{
				nFilecount++;
				break;
			}
			else if(vBaseFileName[i] == strBaseRefFile && vTargetFileName[j] == strTargetRefFile)
			{
				nFilecount++;
				break;
			}
		}
	}

	if (nFilecount == vBaseFileName.size() &&
		nFilecount == vTargetFileName.size())
	{
		// File 개수 체크 패스
		bFileCount = true;
	}
	else
	{
		std::vector<CString> vTempData1;
		std::vector<CString> vTempData2;
		std::vector<CString> vTempData3;
		std::vector<CString> vTempData4;
		// adding file
		if (vTargetFileName.size() > vBaseFileName.size())
		{
			vTempData1.assign(vTargetFileName.begin(),vTargetFileName.end());
			vTempData2.assign(vBaseFileName.begin(),vBaseFileName.end());
		}
		else	// missing file or Name Mismatching
		{
			vTempData1.assign(vBaseFileName.begin(),vBaseFileName.end());
			vTempData2.assign(vTargetFileName.begin(),vTargetFileName.end());	
			vTempData3.assign(vBaseFileName.begin(),vBaseFileName.end());
			vTempData4.assign(vTargetFileName.begin(),vTargetFileName.end());
		}
		

		for (int i = 0; i < vTempData2.size(); i++)
		{
			for (int j = 0; j < vTempData1.size(); j++)
			{
				if(vTempData2[i] == vTempData1[j])
				{
					vTempData1.erase(vTempData1.begin()+j);
					break;
				}
				else if(vTempData2[i].Find(_T("_Register")) != -1 && vTempData1[j].Find(_T("_Register")) != -1)
				{
					vTempData1.erase(vTempData1.begin()+j);
					break;
				}
				else if(vTempData2[i] == strBaseRefFile && vTempData1[j] == strTargetRefFile)
				{
					vTempData1.erase(vTempData1.begin()+j);
					break;
				}
			}
		}

		for (int i = 0; i < vTempData3.size(); i++)
		{
			for (int j = 0; j < vTempData4.size(); j++)
			{
				if(vTempData3[i] == vTempData4[j])
				{
					vTempData4.erase(vTempData4.begin()+j);
					break;
				}
				else if(vTempData3[i].Find(_T("_Register")) != -1 && vTempData4[j].Find(_T("_Register")) != -1)
				{
					vTempData4.erase(vTempData4.begin()+j);
					break;
				}
				else if(vTempData3[i] == strBaseRefFile && vTempData4[j] == strTargetRefFile)
				{
					vTempData4.erase(vTempData4.begin()+j);
					break;
				}
			}
		}

		CString strFailLog;
		// add to fail object
 		if (vTargetFileName.size() > vBaseFileName.size())
		{
			for (int i = 0; i < vTempData1.size() ; i++)
			{
				CompareResult* cNewConfig = new CompareResult;
				cNewConfig->SetFileName(vTempData1[i]);
				outLogData.AddTail(cNewConfig);
				outResult.AddTail(cNewConfig);

				CompareResult* cNewConfig1 = new CompareResult;
				cNewConfig1->SetCompareResult(FALSE);
				cNewConfig1->SetItemName(_T("File Missing"));
				cNewConfig1->SetBaseInfoValue(_T("X"));
				cNewConfig1->SetCurrentInfoValue(vTempData1[i]);
				
				strFailLog.Format(_T("File Missing : %s"), vTempData1[i]);
				outLogData.AddTail(cNewConfig1);
				outResult.AddTail(cNewConfig1);
				outFail.push_back(strFailLog);
				m_pFailItems->AddFailItem("","","",strFailLog,_T(""));
			}
		}
		else if(vTargetFileName.size() < vBaseFileName.size())
		{
			for (int i = 0; i < vTempData1.size() ; i++)
			{
				CompareResult* cNewConfig = new CompareResult;
				cNewConfig->SetFileName(vTempData1[i]);
				outLogData.AddTail(cNewConfig);
				outResult.AddTail(cNewConfig);

				CompareResult* cNewConfig1 = new CompareResult;
				cNewConfig1->SetCompareResult(FALSE);
				cNewConfig1->SetItemName(_T("File Adding"));
				cNewConfig1->SetCurrentInfoValue(_T("X"));
				cNewConfig1->SetBaseInfoValue(vTempData1[i]);

				strFailLog.Format(_T("File Adding : %s"), vTempData1[i]);
				outLogData.AddTail(cNewConfig1);
				outResult.AddTail(cNewConfig1);
				outFail.push_back(strFailLog);
				m_pFailItems->AddFailItem("","",strFailLog,vTempData1[i],_T(""));
			}
		}
		else
		{
			for (int i = 0; i < vTempData1.size() ; i++)
			{
				CompareResult* cNewConfig = new CompareResult;
				cNewConfig->SetFileName(vTempData1[i]);
				outLogData.AddTail(cNewConfig);
				outResult.AddTail(cNewConfig);

				CompareResult* cNewConfig1 = new CompareResult;
				cNewConfig1->SetCompareResult(FALSE);
				cNewConfig1->SetItemName(_T("File Name Mismatch"));
				cNewConfig1->SetBaseInfoValue(vTempData4[i]);
				cNewConfig1->SetCurrentInfoValue(vTempData1[i]);

				strFailLog.Format(_T("File Name Mismatch : %s : %s"),vTempData4[i], vTempData1[i]);
				outLogData.AddTail(cNewConfig1);
				outResult.AddTail(cNewConfig1);
				outFail.push_back(strFailLog);
				m_pFailItems->AddFailItem("","",strFailLog,vTempData1[i],_T(""));
			}
		}
		bFileCount = false;
	}
	//////////////////////////////////////////////////////////////////////////
	// list copy and compare
	//////////////////////////////////////////////////////////////////////////
	
	CList<FileType*> pListTargetFile;

	inTarget->GetDataList(pListTargetFile);

	POSITION pThisListPos = m_pFIleList.GetHeadPosition();
	POSITION pTargetListPos = pListTargetFile.GetHeadPosition();
	FileType* pThis;
	FileType* pTarget;
	bool bFailFlag = false;
	bool bCompareRusult = false;
	int nIndex = 0;

	while(pThisListPos)
	{
		pThis = m_pFIleList.GetNext(pThisListPos);
		pTargetListPos = pListTargetFile.GetHeadPosition();
		nIndex = 0;

		while (pTargetListPos)
		{
			pTarget = pListTargetFile.GetNext(pTargetListPos);

			if(strTargetRef.Find(pTarget->GetFileName()) != -1 &&  strBaseRef.Find(pThis->GetFileName()) != -1 && inBasicCheck == false)
			{
				CompareResult* cNewConfig = new CompareResult;
				cNewConfig->SetFileName(pTarget->GetFileName());
				outLogData.AddTail(cNewConfig);
				outResult.AddTail(cNewConfig);
				outFail.push_back(pThis->GetFileName());
				bCompareRusult = pThis->CompareFile(pTarget, outFail,outLogData, outResult);
				if (!bCompareRusult)
				{
					bFailFlag = true;
				}
				break;
			}
			else if (strTargetRegister.Find(pTarget->GetFileName()) != -1 &&  strBaseRegister.Find(pThis->GetFileName()) != -1 )
			{
				CompareResult* cNewConfig = new CompareResult;
				cNewConfig->SetFileName(pTarget->GetFileName());
				outLogData.AddTail(cNewConfig);
				outResult.AddTail(cNewConfig);
				outFail.push_back(pThis->GetFileName());
				bCompareRusult = pThis->CompareFile(pTarget, outFail, outLogData, outResult);
				if (!bCompareRusult)
				{
					bFailFlag = true;
				}
				break;
			}
			else if(pThis->GetFileName()==pTarget->GetFileName())
			{
				if(inBasicCheck == true && (pTarget->GetFileName().Find("ItemVersion.ini") != -1 || strTargetRef.Find(pTarget->GetFileName()) != -1))
				{
					bCompareRusult = true;
					break;
				}
				else
				{
					CompareResult* cNewConfig = new CompareResult;
					cNewConfig->SetFileName(pTarget->GetFileName());
					outLogData.AddTail(cNewConfig);
					outResult.AddTail(cNewConfig);
					outFail.push_back(pThis->GetFileName());
					bCompareRusult = pThis->CompareFile(pTarget, outFail, outLogData, outResult);
					if (!bCompareRusult)
					{
						bFailFlag = true;
					}
					break;
				}
			}
			nIndex++;
		}
	}

	if (bFileCount && !bFailFlag)
	{
		bResult = true;
	}

	return bResult;
}


void TestType::GetDataList(CList<FileType*>& outData)
{
	outData.RemoveAll();
	POSITION pPos = m_pFIleList.GetHeadPosition();

	FileType* pTemp;

	while(pPos)
	{
		pTemp = m_pFIleList.GetNext(pPos);
		outData.AddTail(pTemp);
	}
}

void TestType:: SetFailItemPointer(FailItem* inData)
{
	m_pFailItems = inData;
}