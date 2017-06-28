#pragma once
#include "BasicData.h"
#include "TestType.h"
#include <afxtempl.h>
#include <vector>
#include "tinyxml2.h"
#include "ListLog.h"
#include "CompareResult.h"
#include "FailItem.h"

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
	bool SearchTestInList(CString inTargetTest, TestType*& outData);
	void InitList();
	BOOL ConfigCompare(ConfigType* inTarget, std::vector<CString>& outFail, CList<CompareResult*>& outLogData, CList<CompareResult*>& outDifferent, int& inCount, bool inBasicCheck);
	void GetDataList(CList<TestType*>& outData);
	CString GetProject(){return m_strPrj;};
	CString GetBuildNum(){return m_strBuildNum;};
	CString GetConfigNum(){return m_strConfigNum;};
	CString GetDOE(){return m_strDOE;};
	void SetRootPath(CString inPath);
	void SetListLog(ListLog* inData);
	void SetListCtrl(CListCtrl* inData);
	void SetProgressBar(CProgressCtrl* inData);
	void SetFailItemPointer(FailItem* inData);
	void SetTestDir(std::vector<CString> invData);
	CString GetInputDirPath();

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
	CList<TestType*> m_pListTestType;
	bool m_bNewData;
	ListLog* m_ListLog;
	CListCtrl* m_ListCtrl;
	CProgressCtrl* m_ProgressBar;
	FailItem* m_pFailItems;
};

