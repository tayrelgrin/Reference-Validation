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
	void SaveSettingToFile();
	void LoadSettingFromFile();
	void LoadBasicFileList();
	void ParsingBBCD(CString inStr, CString& outStrPrj, CString& outStrBuild, CString& outStrConfig, CString& outStrDOE);
	void GetPrjVList(std::vector<CString>& outvData);
	void GetBuildVList(std::vector<CString>& outvData);
	void GetConfigVList(std::vector<CString>& outvData);
	void GetDOEVList(std::vector<CString>& outvData);
private:
	CList<ConfigDMData*> m_listConfigs;
	CList<ConfigDMData*> m_listSetting;
	std::vector<CString> m_vBasicFile;
	std::vector<CString> m_vPrj;
	std::vector<CString> m_vBuild;
	std::vector<CString> m_vConfig;
	std::vector<CString> m_vDOE;
};

