#pragma once

#include "ListLogTab.h"

class ListLog
{
public:
	ListLog(CString inData, ListLogTab* inListLogDlg);
	~ListLog(void);
	void CreateLogFile();
	void WriteLogFile(CString strContents);
	void MakeLogDirectory();
private:
	CString m_sModulePath;
	CString m_strLogPath;
	ListLogTab* m_ListLogTab;
};

