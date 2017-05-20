// ListLogTab.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Data_Validation.h"
#include "ListLogTab.h"
#include "afxdialogex.h"


// ListLogTab ��ȭ �����Դϴ�.

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


// ListLogTab �޽��� ó�����Դϴ�.


BOOL ListLogTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	AddListLog("Validation SW Start");
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
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