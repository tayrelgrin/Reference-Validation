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
	CString getItem();
	CString getSection();
	CString getValue();
	void setData(BasicData inData);
	void getData(BasicData& outData);
	bool operator==(const BasicData& inData);
	void writeDataToFile(tinyxml2::XMLDocument& cXMLDoc, tinyxml2::XMLElement* cElement);
	void readDataFromFile(static CString inFilePath);
private:
	CString m_strSection;
	CString m_strItem;
	CString m_strValue;
};


