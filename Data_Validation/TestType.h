#pragma once
#include <afxtempl.h>
#include "FileType.h"
#include <vector>
#include "tinyxml2.h"
#include "ListLog.h"
#include "CompareResult.h"
#include "FailItem.h"

class TestType
{
public:
	TestType(void);
	~TestType(void);
	void InitList();
	void SetTestName(CString inData);
	CString GetTestName();
	void AddNewFile(CString inStrFileName);
	void AddNewFile(FileType* inData);
	void GetFilePathInDir(CString inPath, std::vector<CString>& outvData);
	void AddNewTest(CString inPath,std::vector<CString> invBasicFile, int inNInput = 2);
	void SaveDataToFile(tinyxml2::XMLDocument& cXMLDoc, tinyxml2::XMLElement* cElement, std::vector<CString> invBasicFile);
	void SaveBaseInfoToFile(tinyxml2::XMLDocument& cXMLDoc, tinyxml2::XMLElement* cElement, CList<BasicData*> inData);
	void LoadDataFromXML(tinyxml2::XMLNode* pParent, CString inStrFileName=_T(""), FileType* pNewTest=nullptr);
	void GetFileNames(CString inTestName, std::vector<CString>& outvFileNames);
	bool SearchFileInList(CString inStrTargetFile, FileType& outData);
	void ModifyData(CString inTargetFileName, BasicData* inTarget);
	void ChangeFileName(CString inTargetFileName, CString inNewFileName);
	bool CompareTest(TestType* inTarget, std::vector<CString>& outFail, CList<CompareResult*>& outLogData,CList<CompareResult*>& outResult, bool inBasicCheck);
	void GetDataList(CList<FileType*>& outData);
	void SetFailItemPointer(FailItem* inData);
	void SetListLog(ListLog* inData);
private:
	CList<FileType*> m_pFIleList;
	CString m_strTestName;
	FailItem* m_pFailItems;
	ListLog* m_ListLog;
};

