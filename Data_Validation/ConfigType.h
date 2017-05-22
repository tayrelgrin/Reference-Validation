#pragma once
#include "BasicData.h"
#include "TestType.h"
#include <afxtempl.h>
#include <vector>
#include "tinyxml2.h"

class ConfigType
{
public:
	ConfigType(void);
	~ConfigType(void);
	void RefNameParsing(static CString instrData);
	void SetProject(CString inData);
	void SetBuildNum(CString inData);
	void SetConfigNum(CString inData);
	void SetDOE(CString inData);
	void AddNewTest(std::vector<CString> invPath,int inNInput = 2);
	void INIFileReadLine(std::vector<CString> invPath);
	CString GetEXEDirectoryPath();
	void LoadDataFiles(CString inStrPath);
	void SearchXMLData(tinyxml2::XMLNode* pParent, int inIndex = 0);
	bool SearchFileDataInList(CString inTargetTest, CString inTargetFile, FileType& outData);
	void InitList();
	void InitListAndVectors();
	BOOL ConfigCompare(ConfigType* inTarget, std::vector<CString>& outFail);
	void GetDataList(CList<TestType*>& outData);
	CString GetProject(){return m_strPrj;};
	CString GetBuildNum(){return m_strBuildNum;};
	CString GetConfigNum(){return m_strConfigNum;};
	CString GetDOE(){return m_strDOE;};
private:
	CString m_strInputDirPath;
	CString m_strPrj;
	CString m_strBuildNum;
	CString m_strConfigNum;
	CString m_strDOE;
	std::vector<CString> m_vTestName;
	std::vector<CString> m_vFilePath;
	std::vector<CString> m_vTestDirPath;
	std::vector<CString> m_vBaseFiles;
	CList<BasicData*> m_pListBaseInfo;
	CList<TestType*> m_pListTestType;
	bool m_bNewData;
};

