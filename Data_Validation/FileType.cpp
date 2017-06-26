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
	CString strTemp;
	strSection.Format(_T(""));
	strItem.Format(_T(""));
	strValue.Format(_T(""));
	strTemp.Format(_T(""));
	CString m_strBasicLoadTxt = _T("Load Reference Setting :");

	for (int i = 0; i< vtemp.size() ; i++)
	{
		strTemp = vtemp[i];
		if (strTemp.Find('/') != -1)
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

			if(strSection == m_strBasicLoadTxt)
				strSection.Format(_T(""));
			if (strValue == m_strBasicLoadTxt)
				strValue.Format(_T(""));
			if (strItem == m_strBasicLoadTxt)
				strItem.Format(_T(""));

			cNewData->setSection(strSection);
			cNewData->setItem(strItem);
			cNewData->setValue(strValue);
			bFlag = false;
		}
		else if(strTemp.Find('[') != -1 && strTemp.Find(']')!= -1 && bFlag == false)
		{
			if(cNewData==NULL)
				cNewData = new BasicData();
			strSection = strTemp;
			cNewData->setSection(strTemp);
			bFlag = true;
		}
		else if (strTemp.Find('[') != -1 && strTemp.Find(']')!= -1 && bFlag == true)
		{
			m_pDataList.AddTail(cNewData);
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

			if(strSection == m_strBasicLoadTxt)
				strSection.Format(_T(""));
			if (strValue == m_strBasicLoadTxt)
				strValue.Format(_T(""));
			if (strItem == m_strBasicLoadTxt)
				strItem.Format(_T(""));

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
	if(cNewData != NULL)
		m_pDataList.AddTail(cNewData);

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


void FileType::INIFileReadByLine(CString inPath, std::vector<CString>& outData)
{
	CStdioFile sourceFile;
	CString strLine;
	strLine.Format(_T(""));

	if(!sourceFile.Open(inPath, CFile::modeRead, NULL)){   
		return;
	}
 
	while(TRUE) {
		BOOL bIsNotEOL = sourceFile.ReadString(strLine);
		if (strLine.GetLength() > 127)
		{
			bIsNotEOL = FALSE;
		}
		if(!bIsNotEOL) break;

		if(strLine!="")	// 공란 제거
			outData.push_back(strLine);		
	}

	sourceFile.Close();
}

//////////////////////////////////////////////////////////////////////////
// Name     : GetFileName
// Function : Return File Name
// pre		: None
// return	: CString m_strFileName
//////////////////////////////////////////////////////////////////////////
CString FileType::GetFileName()
{
	return m_strFileName;
}


//////////////////////////////////////////////////////////////////////////
// Name     : LoadDataFromXML
// Function : Load Basic item info from XML structure
// pre		: Loaded xml file
// return	: none
//////////////////////////////////////////////////////////////////////////
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
	else
		delete outData;
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


BOOL FileType::CompareFile(FileType* inTarget, std::vector<CString>& outFail, CList<CompareResult*>& outLogData, CList<CompareResult*>& outDefferent)
{
	CList<BasicData*> pListTargetData;

	inTarget->CopyDataToList(pListTargetData);

	POSITION pThisListPos = m_pDataList.GetHeadPosition();
	POSITION pTargetListPos = pListTargetData.GetHeadPosition();
	BasicData* pThis;
	BasicData* pTarget;
	bool bFlagSection = false;
	bool bFlagItem = false;
	BOOL bCompareResult = TRUE;
	while(pThisListPos)
	{
		pThis = m_pDataList.GetNext(pThisListPos);		
		pTargetListPos = pListTargetData.GetHeadPosition();
		CString strFail;
		CString strPreSection;
		CString strTemp;
		CString strItemName,strBaseInfo,strCurrentInfo;
		bFlagSection = false;
		bFlagItem = false;
		strItemName.Format(_T(""));
		strBaseInfo.Format(_T(""));
		strCurrentInfo.Format(_T(""));

		while(pTargetListPos)
		{
			pTarget = pListTargetData.GetNext(pTargetListPos);

			if (pThis->getSection()==pTarget->getSection())
			{
				strPreSection = pThis->getSection();
				if (pThis->getItem()==pTarget->getItem())
				{
					CompareResult* cNewResult = new CompareResult;

					strTemp.Format("");
					strTemp = pThis->getItem();

					if (strTemp.Find('/') != -1)
					{
						AfxExtractSubString(strItemName, strTemp,0,'/');
					}
					else
						strItemName = strTemp;

					cNewResult->SetItemName(strItemName);

					strTemp = pThis->getValue();

					if (strTemp.Find('/') != -1)
					{
						AfxExtractSubString(strBaseInfo, strTemp,0,'/');
					}
					else
						strBaseInfo = strTemp;
					cNewResult->SetBaseInfoValue(strBaseInfo);

					strTemp = pTarget->getValue();

					if (strTemp.Find('/') != -1)
					{
						AfxExtractSubString(strCurrentInfo, strTemp,0,'/');
					}
					else
						strCurrentInfo = strTemp;
					cNewResult->SetCurrentInfoValue(strCurrentInfo);

					if (pThis->getValue()!=pTarget->getValue())
					{
						strFail.Format(_T("Fail Item : (%s %s %s) %s : %s"), m_strFileName, pThis->getSection(), pThis->getItem(), pThis->getValue(), pTarget->getValue());
						outFail.push_back(strFail);
						cNewResult->SetCompareResult(FALSE);
						outLogData.AddTail(cNewResult);
						outDefferent.AddTail(cNewResult);
						bCompareResult = FALSE;
					}
 					else if (pThis->getValue()==pTarget->getValue())
 					{
						cNewResult->SetCompareResult(TRUE);
 						outLogData.AddTail(cNewResult);
 					}
					bFlagItem = true;
					break;
				}
				bFlagSection = true;
			}
		}
		if (bFlagSection && !bFlagItem)
		{
			strFail.Format(_T("Fail Item : %s %s : Not Exist Item "), m_strFileName, pThis->getSection());
			outFail.push_back(strFail);
			strFail.Format(_T("Fail Item : %s %s : Not Exist Value"), m_strFileName, pThis->getItem());
			outFail.push_back(strFail);
			break;
			bCompareResult = FALSE;
		}
	}

	return bCompareResult;
}