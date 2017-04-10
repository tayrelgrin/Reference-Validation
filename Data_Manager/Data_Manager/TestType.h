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
	void SetTestName(CString inData);
	CString GetTestName();
	void AddNewFile(CString inStrFileName);
	void AddNewFile(FileType* inData);
	void GetFilePathInDir(CString inPath, std::vector<CString>& outvData);
	void AddNewTest(CString inPath);
	void SaveDataToFile(tinyxml2::XMLDocument& cXMLDoc, tinyxml2::XMLElement* cElement, std::vector<CString> invBasicFile);
private:
	CList<FileType*> m_pListFile;
	CString m_strTestName;
};

