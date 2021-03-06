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
	void GetDirList(CString instrPath, std::vector<CString>& inVDirList,std::vector<CString>& inVFileList);
	void RemoveRootPathInVector(std::vector<CString> invData, std::vector<CString>& outvData, CString inRootPath);
	void GetConfigInfoFromVector(std::vector<CString> invData, CString inRootPath, CString& outPrj, CString& outBuild, CString& outConfig, CString& outDOE);
	void SetProject(CString inData);
	void SetBuildNum(CString inData);
	void SetConfigNum(CString inData);
	void SetDOE(CString inData);
	void ModifyData(CString inTargetTestName, CString inTargetFileName, BasicData* inTarget);
	bool operator==(const ConfigDMData& inData);
	void GetDirPathList(std::vector<CString>& outvData);
	void GetTestNameFromDirVector(std::vector<CString> invData, std::vector<CString>& outvData);
	void SetTestList(std::vector<CString> invData);
	void GetTestList(std::vector<CString>& outvPath);
	void SetTestDirList(std::vector<CString> invData);
	void AddNewTest(std::vector<CString> inBaseFile, int inNInput = 2);
	void GetFilePathInDir(std::vector<CString> invPath, std::vector<CString>& outvData);
	void INIFileReadLine(std::vector<CString> invPath);
	void SetFilePath(std::vector<CString> invPath);
	void SaveDataToFile(std::vector<CString> invBasicFile);
	void SaveSettingToFile(std::vector<CString> invBasicFile, CList<BasicData*>* inlBaseInfo);
	bool GetNewDataFlag();
	void SetNewDataFlag(bool inData);
	void AddCommonBaseFile(std::vector<CString> invFileName);
	void SetBaseFiles(std::vector<CString> invFileName);
	CString GetEXEDirectoryPath();
	void LoadDataFiles(CString inStrPath);
	void SearchXMLData(tinyxml2::XMLNode* pParent, int inIndex = 0);
	void InitListAndVectors();
	void GetFileNames(std::vector<CString>& outvData);
	bool SearchFileDataInList(CString inTargetTest, CString inTargetFile, FileType& outData);
	TestType* SearchTest(TestType& inoutTarget, bool& bResult);
	void GetBaseInfoList(CList<BasicData*>& outList);
	void SetBaseInfoList(CList<BasicData*>& outList);
	void InitBaseInfoList();
	void ChangeFileName(CString inTestName, CString inNewFileName, CString inTargetFileName);
	void SetRootPath(CString inPath);
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
//	TestType* m_pBaseData;	
	CList<BasicData*> m_lBaseInfo;
	CList<TestType*> m_pListTestType;
	bool m_bNewData;
	
};

