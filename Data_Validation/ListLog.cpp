#include "StdAfx.h"
#include "ListLog.h"


ListLog::ListLog(CString inData, ListLogTab* inListLogDlg)
{
	
	m_sModulePath = inData;
	m_ListLogTab = inListLogDlg;
	COleDateTime currentTime;
	currentTime = COleDateTime::GetCurrentTime();
	m_strLogPath.Format(_T("%s\\ListLog\\ListLog_%04d_%02d_%02d.txt"), inData, currentTime.GetYear(), currentTime.GetMonth(), currentTime.GetDay());
}


ListLog::~ListLog(void)
{
}


void ListLog::CreateLogFile()
{
	//CFile file;
	CStdioFile file;	
	CStringA strTemp;
	MakeLogDirectory();

	if (file.Open(m_strLogPath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeText) != FALSE){
		strTemp.Format("\r\n============ Log Start ============\r\n");
		file.SeekToEnd();
		file.Write(strTemp, strTemp.GetLength());
		file.Close();
	}
}


void ListLog::WriteLogFile(CString strContents)
{
	//CFile file;
	CStdioFile file;
	CString strTemp;
	if (file.Open(m_strLogPath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeText) != FALSE){
		COleDateTime currentTime;
		currentTime = COleDateTime::GetCurrentTime();
		file.SeekToEnd();
		strTemp.Format(_T("[%04d/%02d/%02d %02d:%02d:%02d] %s\r"), currentTime.GetYear(), currentTime.GetMonth(), currentTime.GetDay(), currentTime.GetHour(), currentTime.GetMinute(), currentTime.GetSecond(), strContents);
		m_ListLogTab->AddListLog(strTemp);

		file.Write(strTemp, strTemp.GetLength());
		file.Close();
	}
}




void ListLog::MakeLogDirectory()
{
	TCHAR path[_MAX_PATH];

	GetModuleFileName(NULL, path, sizeof path);

	CString strEXEPath = path;

	int i = strEXEPath.ReverseFind('\\');//실행 파일 이름을 지우기 위해서 왼쪽에 있는 '/'를 찾는다.

	CString strTemp = strEXEPath.Left(i);//뒤에 있는 현재 실행 파일 이름을 지운다.

	strEXEPath.Format(_T("%s%s"),strTemp,"\\ListLog");
	CreateDirectory(strEXEPath,NULL);
}