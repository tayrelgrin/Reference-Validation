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
	bool SaveRefToFile();
	void LoadXMLFileListInValue();
	void LoadXMLFileListInSetting();
	void LoadXMLValueFileList(CString inData);
	void LoadXMLSettingFileList(CString inData);
	void SaveSettingToFile();
	void LoadBaseFileList();
	void ParsingBBCD(CString inStr, CString& outStrPrj, CString& outStrBuild, CString& outStrConfig, CString& outStrDOE);
	void GetConfigNameList(std::vector<CString>& outvData);
	void AddSettingFileList(CString inData);
	void InitAllData();
	TestType* SearchSettingData(TestType& inoutTarget, bool& bResult);
	void GetBaseInfo(FileType& inFileData);
	void AddNewBaseInfo(BasicData& inData);
	void InitBaseInfo();
	void SetBaseInfoFromConfig(const CList<BasicData*>& outList);
	bool CheckBaseInfoInAllData(std::vector<CString>& vDifferentTest);

private:
	CList<ConfigDMData*> m_listConfigs;
	CList<ConfigDMData*> m_listSetting;
	CList<BasicData*>	 m_listBaseInfo;
	std::vector<CString> m_vBasicFile;
	std::vector<CString> m_vConfigName;

};

