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
	bool CheckBaseInfoInAllData(std::vector<CString>& vDifferentTest);

private:
	std::vector<CString> m_vConfigName;
	CList<ConfigType*> m_pListConfig;
	CList<ConfigType*> m_pListSetting;
	CList<BasicData*>  m_pListBaseInfo;
	CList<DifferentItem*> m_pListDirrentItems;
};

