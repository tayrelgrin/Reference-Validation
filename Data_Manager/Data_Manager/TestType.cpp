#include "StdAfx.h"
#include "TestType.h"


TestType::TestType(void)
{
	
}


TestType::~TestType(void)
{
	POSITION pTemp = NULL;
	POSITION pPos = m_pListFile.GetHeadPosition();

	while(pPos)
	{
		pTemp = pPos;
		FileType* temp = m_pListFile.GetNext(pPos);
		delete temp;
		m_pListFile.RemoveAt(pTemp);
	}

	m_pListFile.RemoveAll();
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
	m_pListFile.AddTail(newFile);
}

void TestType::AddNewFile(FileType* inData)
{
	m_pListFile.AddTail(inData);
}

void TestType::AddNewTest(CString inPath)
{
	std::vector<CString> vFilePath;

	GetFilePathInDir(inPath, vFilePath);

	for (int i = 0; i< vFilePath.size(); i++)
	{
		FileType* cNewFile = new FileType();				// 객체 생성
		CString strFilePath = vFilePath[i];		
		int nIndex = strFilePath.ReverseFind('\\');			// 파일 이름 인덱스
		
		cNewFile->SetFileName(strFilePath.Mid(nIndex+1));	// 파일 이름 분류
		cNewFile->AddNewData(vFilePath[i]);					// 파일 이름 적용

		if(m_pListFile.IsEmpty())
			m_pListFile.AddHead(cNewFile);
		else
			m_pListFile.AddTail(cNewFile);
	}
	for(int i = 0; i<vFilePath.size(); i++)
	{
		vFilePath.erase(vFilePath.begin()+i);
	}
	vFilePath.clear();
}

void TestType::GetFilePathInDir(CString inPath, std::vector<CString>& outvData)
{
	CFileFind cFinder;

	CString fileName;
	CString tpath;
	BOOL bWorking;

	
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
			m_strTestName.Replace('\\','_');

		Element = cXMLDoc.NewElement(LPSTR(LPCTSTR(m_strTestName)));

		cElement->LinkEndChild(Element);

		POSITION pos = m_pListFile.GetHeadPosition();

		while(pos)
		{
			FileType* pData = m_pListFile.GetNext(pos);

			pData->SaveDataToFile(cXMLDoc, Element);

			// 		for(int i = 0; i<invBasicFile.size(); i++)
			// 		{
			// 			if(invBasicFile[i].Find(pData->GetFileName()) != -1)
			// 			{
			// 				pData->SaveDataToFile(cXMLDoc, Element);
			// 				break;
			// 			}
			// 		}

		}
	}	
}

void TestType::LoadDataFromXML(tinyxml2::XMLNode* pParent, CString inStrFileName)
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
				
				FileType* pNewTest = new FileType;
				pNewTest->SetFileName(inStrFileName);

				pNewTest->LoadDataFromXML((tinyxml2::XMLAttribute*)pAttr);
				m_pListFile.AddTail(pNewTest);
				
			}
			else{
				LoadDataFromXML(pElent,pNode->Value() );
			}
		}
	}
}