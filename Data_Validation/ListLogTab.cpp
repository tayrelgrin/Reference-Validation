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
