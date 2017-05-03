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
	void ModifyConfigData(CString inTargetTest, CString inTargetFileName, BasicData* inTarget);
	void ModifySettingData(CString inTargetTestName,CString inTargetFileName, BasicData* inTarget);
	void ModifyBaseInfoData(CString inTargetTestName, CString inTargetFileName, BasicData* inTarget);
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
	void AddSettingFileList(CString inData);
	void InitAllData();
	TestType* SearchSettingData(TestType& inoutTarget, bool& bResult);
	void GetBaseInfo(FileType& inFileData);
	void AddNewBaseInfo(BasicData& inData);
	void InitBaseInfo();
	void SetBaseInfoFromConfig(const CList<BasicData*>& outList);
private:
	CList<ConfigDMData*> m_listConfigs;
	CList<ConfigDMData*> m_listSetting;
	CList<BasicData*>	 m_listBaseInfo;
	std::vector<CString> m_vBasicFile;
	std::vector<CString> m_vConfigName;

};

