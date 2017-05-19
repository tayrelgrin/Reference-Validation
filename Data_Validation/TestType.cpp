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
		FileType* cNewFile = new FileType();				// 객체 생성
		CString strFilePath;
		strFilePath.Format("%s",vFilePath[i] );
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

	fileName.Format("");
	tpath.Format("");

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
				pNewTest = new FileType;
				
				LoadDataFromXML(pElent,(CString)pNode->Value(), pNewTest);
				m_pFIleList.AddTail(pNewTest);
			}
		}
	}
}


void TestType::GetFileNames(CString inTestName ,std::vector<CString>& outvFileNames)
{
	POSITION pPos = m_pFIleList.GetHeadPosition();
	CString strFileName;
	strFileName.Format("");
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
	strFileName.Format("");
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
	strFileName.Format("");
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
	strFileName.Format("");
	bool bResult=false;

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