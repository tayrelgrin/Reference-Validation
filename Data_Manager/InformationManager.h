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
	void LoadRefFromFile();
	void SaveSettingToFile();
	void LoadSettingFromFile();
	void LoadBasicFileList();
private:
	CList<ConfigDMData*> m_listConfigs;
	CList<ConfigDMData*> m_listSetting;
	std::vector<CString> m_vBasicFile;
};

