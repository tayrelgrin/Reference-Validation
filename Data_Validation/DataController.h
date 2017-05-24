#pragma once
#include "ConfigType.h"
#include "DifferentItem.h"
#include "resource.h"
#include "ListLog.h"


class DataController
{
public:
	DataController();
	~DataController(void);
	void SetListLog(ListLog* inData);
	void LoadXMLFileListInValue();
	void LoadXMLFileListInSetting();
	void LoadXMLValueFile(CString inData);
	void LoadXMLSettingFile(CString inData);
	void LoadSettingFromFile();
	void InitAllData();
	bool CheckBaseInfoInAllData(CString instrPath,std::vector<CString>& vTestDirPath);
	void GetDirList(CString instrPath, std::vector<CString>& outDirVector,  std::vector<CString>& outFileVector);
	void ParsingBBCD(CString inStr, CString& outStrPrj, CString& outStrBuild, CString& outStrConfig, CString& outStrDOE);
	void GetTestNameFromTestDirNameVector(static std::vector<CString> invData, std::vector<CString>& outvData);
	void RemoveRootPathInVector(const std::vector<CString> invData, std::vector<CString>& outvData, CString inRootPath);
	void GetConfigFromTestDirNameVector(std::vector<CString> invData,CString& strConfig);
	void ReadReference();
	void AddTestDirectoryPath(std::vector<CString> invData);
	void AddFilePath(std::vector<CString> invData);
	void DeleteTestDirectoryPath(CString inTarget);
	void DeleteFilPath(CString inTarget);
	void GetTestDirectoryPath(std::vector<CString>& outvData);
	void GetFilePath(std::vector<CString>& outvData);
	void AddNewConfigData(std::vector<CString> inData);
	BOOL Validation(CString inData);
	void AddRootPath(CString inData);
	void GetValueXMLFileList(std::vector<CString>& outData);
	void LoadXMLDataFiles(CString inData);
	CString GetEXEDirectoryPath();
	BOOL CompareReference(std::vector<CString> outResult);

private:
	std::vector<CString> m_vValueFileList;
	CList<ConfigType*> m_pListConfig;
	CList<ConfigType*> m_pListSetting;
	CList<ConfigType*> m_pListTargetRefConfig;
	CList<DifferentItem*> m_pListDirrentItems;
	std::vector<CString> m_vFileVector;
	std::vector<CString> m_vDirVector;
	std::vector<CString> m_vRootDIr;
	ListLog* m_ListLog;
};