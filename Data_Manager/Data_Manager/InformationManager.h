#pragma once
#include "ConfigDMData.h"
#include "tinyxml2.h"

class InformationManager
{
public:
	InformationManager(void);
	~InformationManager(void);
	void AddNewConfigData(ConfigDMData* inNewData);
	void AddNewSettingData(ConfigDMData* inNewData);
	void ModifyConfigData(ConfigDMData* inTargetData);
	void DeleteConfigData(ConfigDMData* inTargetData);
	void DeleteConfigData(CString instrPrj, CString instrBuild, CString instrConfig, CString instrDOE);
	bool SaveRefToFile(CString inFilePath);
	void LoadXMLFileListInValue();
	void LoadXMLFileListInSetting();
	void LoadXMLValueFileList(CString inData);
	void LoadXMLSettingFileList(CString inData);
	void SaveSettingToFile();
	void LoadSettingFromFile();
	void LoadBaseFileList();
	void ParsingBBCD(CString inStr, CString& outStrPrj, CString& outStrBuild, CString& outStrConfig, CString& outStrDOE);
	void GetConfigNameList(std::vector<CString>& outvData);
	void AddToPrj(CString inData);
	void AddToBuild(CString inData);
	void AddToConfig(CString inData);
	void AddToDOE(CString inData);
	void InitAllData();
	TestType* SearchSettingData(TestType& inoutTarget, bool& bResult);
private:
	CList<ConfigDMData*> m_listConfigs;
	CList<ConfigDMData*> m_listSetting;
	CList<BasicData*>	 m_listBaseInfo;
	std::vector<CString> m_vBasicFile;
	std::vector<CString> m_vConfigName;

};

