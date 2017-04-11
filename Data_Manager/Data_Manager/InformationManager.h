#pragma once
#include "ConfigDMData.h"
#include "tinyxml2.h"

class InformationManager
{
public:
	InformationManager(void);
	~InformationManager(void);
	void AddNewConfigData(ConfigDMData* inNewData);
	void ModifyConfigData(ConfigDMData* inTargetData);
	void DeleteConfigData(ConfigDMData* inTargetData);
	void DeleteConfigData(CString instrPrj, CString instrBuild, CString instrConfig, CString instrDOE);
	void SaveRefToFile(CString inFilePath);
	void LoadXMLFileList();
	void LoadXMLFileList(CString inData);
	void SaveSettingToFile();
	void LoadSettingFromFile();
	void LoadBasicFileList();
	void ParsingBBCD(CString inStr, CString& outStrPrj, CString& outStrBuild, CString& outStrConfig, CString& outStrDOE);
	void GetConfigNameList(std::vector<CString>& outvData);
	void AddToPrj(CString inData);
	void AddToBuild(CString inData);
	void AddToConfig(CString inData);
	void AddToDOE(CString inData);

private:
	CList<ConfigDMData*> m_listConfigs;
	CList<ConfigDMData*> m_listSetting;
	std::vector<CString> m_vBasicFile;
	std::vector<CString> m_vConfigName;

};

