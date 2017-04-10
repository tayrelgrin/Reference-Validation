#pragma once
#include "BasicData.h"
#include "TestType.h"
#include <afxtempl.h>
#include <vector>
#include "tinyxml2.h"


class ConfigDMData
{
public:
	ConfigDMData(void);
	~ConfigDMData(void);
	void RefNameParsing(CString instrData);
	void GetDirList(CString instrPath, std::vector<CString>& inVDirList);
	void GetTestDirFromVector(std::vector<CString> invData, std::vector<CString>& outvData, CString inRootPath);
	void GetConfigInfoFromVector(std::vector<CString> invData, CString inRootPath, CString& outPrj, CString& outBuild, CString& outConfig, CString& outDOE);
	void SetProject(CString inData);
	void SetBuildNum(CString inData);
	void SetConfigNum(CString inData);
	void SetDOE(CString inData);
	bool operator==(const ConfigDMData& inData);
	//void operator=(const ConfigDMData& inData);
	CString GetBuildNum();
	void GetDirPathList(std::vector<CString>& outvData);
	void GetTestNameFromDirVector(std::vector<CString> invData, std::vector<CString>& outvData);
	void SetTestList(std::vector<CString> invData);
	void GetTestList(std::vector<CString>& outvPath);
	void SetTestDirList(std::vector<CString> invData);
	void AddNewTest();
	void GetFilePathInDir(std::vector<CString> invPath, std::vector<CString>& outvData);
	void INIFileReadLine(std::vector<CString> invPath);
	void SetFilePath(std::vector<CString> invPath);
	void SaveDataToFile(std::vector<CString> invBasicFile);
	bool GetNewDataFlag();
	void SetNewDataFlag(bool inData);
	void AddCommonBaseFile(std::vector<CString> invFileName);
	void SetBaseFiles(std::vector<CString> invFileName);
	CString GetEXEDirectoryPath();
private:
	CString m_strInputDirPath;
	CString m_strPrj;
	CString m_strBuildNum;
	CString m_strConfigNum;
	CString m_strDOE;
	std::vector<CString> m_vTestName;
//	std::vector<CString> m_vFilePath;
	CList<TestType*> m_pListTestType;
	std::vector<CString> m_vTestDirPath;
	std::vector<CString> m_vBaseFiles;
	bool m_bNewData;
	
};

