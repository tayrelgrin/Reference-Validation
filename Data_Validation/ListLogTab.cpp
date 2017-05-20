// ListLogTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Data_Validation.h"
#include "ListLogTab.h"
#include "afxdialogex.h"


// ListLogTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(ListLogTab, CDialogEx)

ListLogTab::ListLogTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(ListLogTab::IDD, pParent)
{

}

ListLogTab::~ListLogTab()
{
}

void ListLogTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listLogBox);
}


BEGIN_MESSAGE_MAP(ListLogTab, CDialogEx)
END_MESSAGE_MAP()


// ListLogTab 메시지 처리기입니다.


BOOL ListLogTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	AddListLog("Validation SW Start");
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void ListLogTab::AddListLog(CString inData)
{
	CTime cTimer = CTime::GetCurrentTime();
	CString strListLog;
	strListLog.Format("%02d.%02d, %02d:%02d:%02d, %s", cTimer.GetMonth(),cTimer.GetDay(), cTimer.GetHour(), cTimer.GetMinute(), cTimer.GetSecond(), inData);
	m_listLogBox.AddString(strListLog);

	int nCount = m_listLogBox.GetCount();
	m_listLogBox.SetCurSel(nCount-1);
}