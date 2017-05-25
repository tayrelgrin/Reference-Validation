#pragma once
#include "BasicData.h"
#include <afxtempl.h>
#include <vector>
#include "ListLog.h"
#include "CompareResult.h"

class FileType
{
public:
	FileType(void);
	~FileType(void);
	void SetFileName(CString inData);
	void AddNewData(CString inData, int inNInput = 2);
	bool AddNewData(BasicData* inData);
	void INIFileReadByLine(CString inPath, std::vector<CString>& outData);
	CString GetFileName();
	void LoadDataFromXML(tinyxml2::XMLAttribute* pParent);
	void CopyData(FileType& outData);
	void CopyDataToList(CList<BasicData*>& outListData);
	void InitList();
	void SetListCountZero();
	void ModifyData(BasicData* inTarget);
	void SaveDataToFile(tinyxml2::XMLDocument& cXMLDoc, tinyxml2::XMLElement* cElement);
	BOOL CompareFile(FileType* inTarget, std::vector<CString>& outFail, CList<CompareResult*>& outDifferent);
	
private:
	CList<BasicData*> m_pDataList;
	CString m_strFileName;
};

