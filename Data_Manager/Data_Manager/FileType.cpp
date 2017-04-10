#include "StdAfx.h"
#include "FileType.h"

FileType::FileType(void)
{
	
}


FileType::~FileType(void)
{
	POSITION pTemp = NULL;
	POSITION pPos = m_pListData.GetHeadPosition();

	while(pPos)
	{
		pTemp = pPos;
		BasicData* temp = m_pListData.GetNext(pPos);
		delete temp;
		m_pListData.RemoveAt(pTemp);
		
	}

	m_pListData.RemoveAll();
}

void FileType::SaveDataToFile( tinyxml2::XMLDocument& cXMLDoc, tinyxml2::XMLElement* cElement)
{
	tinyxml2::XMLElement* Element;
	Element = cXMLDoc.NewElement(LPSTR(LPCTSTR(m_strFileName)));

	cElement->LinkEndChild(Element);

	POSITION pos = m_pListData.GetHeadPosition();
	
	BasicData* pData;

	while(pos)
	{
		pData = m_pListData.GetNext(pos);
		pData->writeDataToFile(cXMLDoc, Element);
	}
}

void FileType::SetFileName(CString inData)
{
	m_strFileName = inData;
}

void FileType::AddNewData(CString inData)
{

	std::vector<CString> vtemp;
	CString strSection, strItem, strValue;
	bool bFlag = false;
	INIFileReadByLine(inData, vtemp);
	BasicData* cNewData=NULL;

	for (int i = 0; i< vtemp.size() ; i++)
	{
		CString strTemp = vtemp[i];
		if(strTemp.Find('[') != -1 && strTemp.Find(']')!= -1 && bFlag == false)
		{
			if (cNewData==NULL)
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
			AfxExtractSubString(strValue,		strTemp, 1, '=');
			cNewData->setSection(strSection);
			cNewData->setItem(strItem);
			cNewData->setValue(strValue);
			bFlag = false;
		}
		if(bFlag == false)
		{
			if(cNewData->getItem() != "" || cNewData->getValue() != "" )
			{
				if(m_pListData.IsEmpty())
					m_pListData.AddHead(cNewData);
				else
					m_pListData.AddTail(cNewData);

				cNewData = NULL;
			}
		}	
	}
}

void FileType::AddNewData(BasicData* inData)
{
	if(m_pListData.IsEmpty())
		m_pListData.AddHead(inData);
	else
		m_pListData.AddTail(inData);
}

void FileType::INIFileReadByLine(CString inPath, std::vector<CString>& outData)
{
	CStdioFile sourceFile;
	CString strLine;

	if(!sourceFile.Open(inPath, CFile::modeRead, NULL)){   
		return;
	}
 
	while(TRUE) {			
		BOOL bIsNotEOL = sourceFile.ReadString(strLine);
		outData.push_back(strLine);
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
		CString strTemp = pAttr->Name();

		if("Section" == strTemp)
			outData->setSection(pAttr->Value());
		else if("Item" == strTemp)
			outData->setItem(pAttr->Value());
		else if("Value" == strTemp)
		{
			outData->setValue(pAttr->Value());
			bFlag = true;
		}
	}

	if(bFlag)
		m_pListData.AddTail(outData);
}