//////////////////////////////////////////////////////////////////////////
// Author	: Gibbs 
// Data		: 2017.03.14
////////////////////////////////////////////////////////////////////////// 

#include "StdAfx.h"
#include "BasicData.h"

//////////////////////////////////////////////////////////////////////////
// BasicData Member Functions
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// BasicData default constructor
//////////////////////////////////////////////////////////////////////////
BasicData::BasicData(void)
{
	m_strSection = "";
	m_strItem = "";
	m_strValue = "";
}

//////////////////////////////////////////////////////////////////////////
// BasicData default Destructor
//////////////////////////////////////////////////////////////////////////
BasicData::~BasicData(void)
{
}

//////////////////////////////////////////////////////////////////////////
// Name     : setItem
// Function : input item to m_strItem
// pre		: none
// return	: none
//////////////////////////////////////////////////////////////////////////
void BasicData::setItem(CString inData)
{
	inData = inData.Trim();
	m_strItem = inData;
}

//////////////////////////////////////////////////////////////////////////
// Name     : setSection
// Function : input section to m_strSection..
// pre		: none
// return	: none
//////////////////////////////////////////////////////////////////////////
void BasicData::setSection(CString inData)
{
	inData = inData.Trim();
	m_strSection = inData;
}

//////////////////////////////////////////////////////////////////////////
// Name     : setValue
// Function : input value to m_strValue
// pre		: none
// return	: none
//////////////////////////////////////////////////////////////////////////
void BasicData::setValue(CString inData)
{
	inData = inData.Trim();
	m_strValue = inData;
}

//////////////////////////////////////////////////////////////////////////
// Name     : setData
// Function : input setData(Item, value, section)
// pre		: none
// return	: none
//////////////////////////////////////////////////////////////////////////
void BasicData::setData(BasicData inData)
{
	setItem(inData.getItem());
	setSection(inData.getSection());
	setValue(inData.getValue());
}

//////////////////////////////////////////////////////////////////////////
// Name     : getItem
// Function : get Item
// pre		: none
// return	: Cstring m_strItem
//////////////////////////////////////////////////////////////////////////
CString BasicData::getItem()
{
	return m_strItem;
}

//////////////////////////////////////////////////////////////////////////
// Name     : getSection
// Function : get Section
// pre		: none
// return	: Cstring m_strSection
//////////////////////////////////////////////////////////////////////////
CString BasicData::getSection()
{
	return m_strSection;
}

//////////////////////////////////////////////////////////////////////////
// Name     : getValue
// Function : get Value
// pre		: none
// return	: Cstring m_strValue
//////////////////////////////////////////////////////////////////////////
CString BasicData::getValue()
{
	return m_strValue;
}

//////////////////////////////////////////////////////////////////////////
// Name     : getData
// Function : get Value
// pre		: none
// return	: none
//////////////////////////////////////////////////////////////////////////
void BasicData::getData(BasicData& outData)
{
	outData.setItem(this->getItem());
	outData.setSection(this->getSection());
	outData.setValue(this->getValue());
}

//////////////////////////////////////////////////////////////////////////
// Name     : operator==
// Function : compare inData and this data
// pre		: none
// return	: if same data true or false
//////////////////////////////////////////////////////////////////////////
bool BasicData::operator==(const BasicData& inData)
{
	bool bResult =  false;

	if(inData.m_strItem == this->m_strItem && inData.m_strSection == this->m_strSection && inData.m_strValue== this->m_strValue)
		bResult = true;

	return bResult;
}


//////////////////////////////////////////////////////////////////////////
// Name     : writeDataToFile
// Function : Write Item to File
// pre		: none
// return	: none
//////////////////////////////////////////////////////////////////////////
void BasicData::writeDataToFile(tinyxml2::XMLDocument& cXMLDoc, tinyxml2::XMLElement* cElement)
{
	tinyxml2::XMLElement* Element;
	Element = cXMLDoc.NewElement("Element");

	cElement->LinkEndChild(Element);
	Element->SetAttribute("Section",	m_strSection);
	Element->SetAttribute("Item",		m_strItem);
	Element->SetAttribute("Value",		m_strValue);
}

//////////////////////////////////////////////////////////////////////////
// Name     : writeDataToFile
// Function : Write Item to File
// pre		: none
// return	: none
//////////////////////////////////////////////////////////////////////////
void BasicData::readDataFromFile(static CString inFilePath)
{
	CStdioFile file;
	file.Open(inFilePath, CFile::modeRead | CFile::typeText);

	CString temp;
	temp.Format("");
	file.ReadString(temp);

	file.Close();
}