#pragma once
#include <afxtempl.h>
#include "FileType.h"
#include <vector>
#include "tinyxml2.h"

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
	void GetFilePathInDir(static CString inPath, std::vector<CString>& outvData);
	void AddNewTest(CString inPath,std::vector<CString> invBasicFile, int inNInput = 2);
	void SaveDataToFile(tinyxml2::XMLDocument& cXMLDoc, tinyxml2::XMLElement* cElement, std::vector<CString> invBasicFile);
	void SaveBaseInfoToFile(tinyxml2::XMLDocument& cXMLDoc, tinyxml2::XMLElement* cElement, CList<BasicData*> inData);
	void LoadDataFromXML(tinyxml2::XMLNode* pParent, CString inStrFileName=_T(""), FileType* pNewTest=nullptr);
	void GetFileNames(CString inTestName, std::vector<CString>& outvFileNames);
	bool SearchFileInList(CString inStrTargetFile, FileType& outData);
	void ModifyData(CString inTargetFileName, BasicData* inTarget);
private:
	CList<FileType*> m_pFIleListFile;
	CString m_strTestName;
};

