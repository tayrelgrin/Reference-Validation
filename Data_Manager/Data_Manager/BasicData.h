//////////////////////////////////////////////////////////////////////////
// Author	: Gibbs 
// Data		: 2017.03.14
////////////////////////////////////////////////////////////////////////// 

#pragma once
#include "tinyxml2.h"

//////////////////////////////////////////////////////////////////////////
// BasicData
// Parent class of SettingData class and FileData class
//////////////////////////////////////////////////////////////////////////
class BasicData
{
public:
	BasicData(void);
	~BasicData(void);
	void setItem(CString inData);
	void setSection(CString inData);
	void setValue(CString inData);
	void setFileName(CString inData);
	CString getItem();
	CString getSection();
	CString getValue();
	CString getFileName();
	void setData(BasicData inData);
	void getData(BasicData& outData);
	bool operator==(const BasicData& inData);
	void writeDataToFile(tinyxml2::XMLDocument& cXMLDoc, tinyxml2::XMLElement* cElement);
// 	void writeItemToFile(tinyxml2::XMLDocument& file, CString instrData);
// 	void writeSectionToFile(tinyxml2::XMLDocument& file, CString instrData);	
// 	void writeValueToFile(tinyxml2::XMLDocument& file, CString instrData);
	void readDataFromFile(CString inFilePath);
private:
	CString m_strSection;
	CString m_strItem;
	CString m_strValue;
	//CString m_strFileName;
};

//////////////////////////////////////////////////////////////////////////
// SettingData
// To Save setting values and items
//////////////////////////////////////////////////////////////////////////

class SettingData:public BasicData
{
public:
	SettingData();
	~SettingData();
	void setItem(CString inData);
	void setSection(CString inData);
	void setValue(CString inData);
	void setFileName(CString inData);
	CString getItem();
	CString getSection();
	CString getValue();
	CString getFileName();
	void setData(BasicData inData);
	void getData(BasicData& outData);

private:
	CString m_strTestName;
};


//////////////////////////////////////////////////////////////////////////
// FileData
// To Save items value and description
//////////////////////////////////////////////////////////////////////////
class FileData:public BasicData
{
public:
	FileData();
	~FileData();
	void setItem(CString inData);
	void setSection(CString inData);
	void setValue(CString inData);
	void setFileName(CString inData);
	CString getItem();
	CString getSection();
	CString getValue();
	CString getFileName();
	void setData(BasicData inData);
	void getData(BasicData& outData);

private:
	CString m_strDescription;
	CString m_strBaseInfo;
	
};