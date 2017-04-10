#pragma once
#include "BasicData.h"
#include <afxtempl.h>
#include <vector>



class FileType
{
public:
	FileType(void);
	~FileType(void);
	void SaveDataToFile(tinyxml2::XMLDocument& cXMLDoc, tinyxml2::XMLElement* cElement);
	void SetFileName(CString inData);
	void AddNewData(CString inData);
	void AddNewData(BasicData* inData);
	void INIFileReadByLine(CString inPath, std::vector<CString>& outData);
	CString GetFileName();
	void LoadDataFromXML(tinyxml2::XMLAttribute* pParent);
private:
	CList<BasicData*> m_pListData;
	CString m_strFileName;
};

