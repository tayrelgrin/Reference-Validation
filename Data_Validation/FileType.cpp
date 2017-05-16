#include "StdAfx.h"
#include "FileType.h"

FileType::FileType(void)
{
}

FileType::~FileType(void)
{
	InitList();
}

void FileType::InitList()
{
	POSITION pTemp = NULL;
	POSITION pPos = m_pDataList.GetHeadPosition();

	while(pPos && m_pDataList.GetSize() > 0)
	{
		pTemp = pPos;

		BasicData* temp = m_pDataList.GetNext(pPos);
		delete temp;
		m_pDataList.RemoveAt(pTemp);
	}
}


void FileType::SetListCountZero()
{
	m_pDataList.RemoveAll();
}


void FileType::SaveDataToFile( tinyxml2::XMLDocument& cXMLDoc, tinyxml2::XMLElement* cElement)
{
	tinyxml2::XMLElement* Element;
	Element = cXMLDoc.NewElement(LPSTR(LPCTSTR(m_strFileName)));

	cElement->LinkEndChild(Element);

	POSITION pos = m_pDataList.GetHeadPosition();
	
	BasicData* pData;

	while(pos)
	{
		pData = m_pDataList.GetNext(pos);
		pData->writeDataToFile(cXMLDoc, Element);
	}
}


void FileType::SetFileName(CString inData)
{
	m_strFileName = inData;
}


void FileType::AddNewData(CString inData, int inNInput)
{
	std::vector<CString> vtemp;
	CString strSection, strItem, strValue;
	bool bFlag = false;
	INIFileReadByLine(inData, vtemp);
	BasicData* cNewData = NULL;
	strSection.Format("");
	strItem.Format("");
	strValue.Format("");

	for (int i = 0; i< vtemp.size() ; i++)
	{
		CString strTemp = vtemp[i];
		if(strTemp.Find('[') != -1 && strTemp.Find(']')!= -1 && bFlag == false)
		{
			if(cNewData==NULL)
				cNewData = new BasicData();
			strSection = strTemp;
			cNewData->setSection(strTemp);
			bFlag = true;
		}
		else
		{
			if (cNewData==NULL)
				cNewData = new BasicData();
			AfxExtractSubString(strItem,		strTemp, 0, '=');

			if(inNInput!=2)
			{
				strValue.Format(_T("%d"), inNInput);
			}
			else
				AfxExtractSubString(strValue,	strTemp, 1, '=');

			cNewData->setSection(strSection);
			cNewData->setItem(strItem);
			cNewData->setValue(strValue);
			
			bFlag = false;
		}

		if(bFlag == false)
		{
			if(cNewData->getItem() != "" || cNewData->getValue() != "" )
			{
				m_pDataList.AddTail(cNewData);
				cNewData = NULL;
			}
			else
			{
				if (cNewData != NULL)
				{
					delete cNewData;
					cNewData = NULL;
				}
			}
		}	
	}

	vtemp.clear();
}


bool FileType::AddNewData(BasicData* inData)
{
	bool bReulst = false;
	POSITION pTemp = NULL;
	POSITION pPos = m_pDataList.GetHeadPosition();
	bool bSearchResult = false;
	BasicData* temp = NULL;

	while(pPos && m_pDataList.GetSize() > 0)
	{
		pTemp = pPos;
		
		temp = m_pDataList.GetNext(pPos);
		if(temp==inData)
		{
			bSearchResult = true;
			break;
		}
	}
	if(!bSearchResult)
	{
		m_pDataList.AddTail(inData);
		bReulst = true;
	}
	return bReulst;
}


void FileType::INIFileReadByLine(static CString inPath, std::vector<CString>& outData)
{
	CStdioFile sourceFile;
	CString strLine;
	strLine.Format("");

	if(!sourceFile.Open(inPath, CFile::modeRead, NULL)){   
		return;
	}
 
	while(TRUE) {			
		BOOL bIsNotEOL = sourceFile.ReadString(strLine);
		if(strLine!="")	// 공란 제거
			outData.push_back(strLine);
		if (strLine.GetLength()>127)
		{
			bIsNotEOL = FALSE;
		}
		if(!bIsNotEOL) break;
	}

	sourceFile.Close();
}


CString FileType::GetFileName()
{
	return m_strFileName;
}


void FileType::LoadDataFromXML(tinyxml2::XMLAttribute* pParent)
{
	tinyxml2::XMLAttribute* pAttr;
	BasicData* outData = new BasicData;
	bool bFlag = false;

	for (pAttr = pParent; pAttr != 0; pAttr = (tinyxml2::XMLAttribute*)pAttr->Next() )
	{
		CString strTemp = (CString)pAttr->Name();

		if("Section" == strTemp)
			outData->setSection((CString)pAttr->Value());
		else if("Item" == strTemp)
			outData->setItem((CString)pAttr->Value());
		else if("Value" == strTemp)
		{
			outData->setValue((CString)pAttr->Value());
			bFlag = true;
		}
	}

	if(bFlag)
		m_pDataList.AddTail(outData);
}

//////////////////////////////////////////////////////////////////////////
// Name     : CopyDataInList
// Function : Copy this object to outData
// pre		: none
// return	: none
//////////////////////////////////////////////////////////////////////////
void FileType::CopyData(FileType& outData)
{
	outData.InitList();

	POSITION pPos = m_pDataList.GetHeadPosition();

	while(pPos)
	{
		BasicData* temp = m_pDataList.GetNext(pPos);
		BasicData* cNewData = new BasicData;

		cNewData->setData(*temp);

		if(outData.AddNewData(cNewData) == false)
		{
			delete cNewData;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Name     : CopyDataToList
// Function : Copy this object list to outListData
// pre		: none
// return	: none
//////////////////////////////////////////////////////////////////////////
void FileType::CopyDataToList(CList<BasicData*>& outListData)
{
	outListData.RemoveAll();

	if(!m_pDataList.IsEmpty())
	{
		POSITION pPos = m_pDataList.GetHeadPosition();

		while(pPos)
		{
			BasicData* temp = m_pDataList.GetNext(pPos);
			BasicData* cNewData = new BasicData;

			cNewData->setData(*temp);

			outListData.AddTail(cNewData);
		}
	}	
}

//////////////////////////////////////////////////////////////////////////
// Name     : ModifyData
// Function : Search data and Modify it in m_pDataList
// pre		: Data in m_pDataList
// return	: none
//////////////////////////////////////////////////////////////////////////
void FileType::ModifyData(BasicData* inTarget)
{
	POSITION pPos = m_pDataList.GetHeadPosition();

	while(pPos)
	{
		BasicData* temp = m_pDataList.GetNext(pPos);

		if (temp->getSection() == inTarget->getSection() && temp->getItem() == inTarget->getItem())
		{
			temp->setValue(inTarget->getValue());
			break;
		}
	}
}