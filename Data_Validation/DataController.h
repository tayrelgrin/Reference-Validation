#pragma once
#include "ConfigType.h"
#include "DifferentItem.h"


class DataController
{
public:
	DataController(void);
	~DataController(void);
	void LoadXMLFileListInValue();
	void LoadXMLFileListInSetting();
	void LoadXMLValueFileList(CString inData);
	void LoadXMLSettingFileList(CString inData);
	void LoadSettingFromFile();
	void InitAllData();
	bool CheckBaseInfoInAllData(CString instrPath,std::vector<CString>& vTestDirPath);
	void GetDirList(CString instrPath, std::vector<CString>& outDirVector,  std::vector<CString>& outFileVector);
	void ParsingBBCD(CString inStr, CString& outStrPrj, CString& outStrBuild, CString& outStrConfig, CString& outStrDOE);
	void GetTestNameFromTestDirNameVector(static std::vector<CString> invData, std::vector<CString>& outvData);
	void RemoveRootPathInVector(const std::vector<CString> invData, std::vector<CString>& outvData, CString inRootPath);
	void GetConfigFromTestDirNameVector(std::vector<CString> invData,CString& strConfig);
private:
	std::vector<CString> m_vConfigName;
	CList<ConfigType*> m_pListConfig;
	CList<ConfigType*> m_pListSetting;
	CList<BasicData*>  m_pListBaseInfo;
	CList<DifferentItem*> m_pListDirrentItems;
};