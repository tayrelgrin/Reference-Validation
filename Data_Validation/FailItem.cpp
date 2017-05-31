// FailItem.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Data_Validation.h"
#include "FailItem.h"
#include "afxdialogex.h"


// FailItem 대화 상자입니다.

IMPLEMENT_DYNAMIC(FailItem, CDialogEx)

FailItem::FailItem(CWnd* pParent /*=NULL*/)
	: CDialogEx(FailItem::IDD, pParent)
{

}

FailItem::~FailItem()
{
}

void FailItem::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_FAILITEM, m_ListCtrl_FailItem);
}


BEGIN_MESSAGE_MAP(FailItem, CDialogEx)
END_MESSAGE_MAP()


// FailItem 메시지 처리기입니다.


BOOL FailItem::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	//////////////////////////////////////////////////////////////////////////
	m_ListCtrl_FailItem.SetExtendedStyle(LVS_EX_GRIDLINES | LVCFMT_CENTER | LVS_EDITLABELS);

	m_ListCtrl_FailItem.InsertColumn(0, _T(""),			LVCFMT_CENTER, 0,  -1);
	m_ListCtrl_FailItem.InsertColumn(1, _T("Detail"),	LVCFMT_CENTER, 220, -1);
	m_ListCtrl_FailItem.InsertColumn(2, _T("Path"),		LVCFMT_CENTER, 490, -1);
	
	////////////////////////////////////////////////////////////////////////// 

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void FailItem::AddFailItem(CString inItem, CString inPath)
{
	int nCount = m_ListCtrl_FailItem.GetItemCount();
	UpdateData(TRUE);
	m_ListCtrl_FailItem.InsertItem(nCount, _T(""));
	m_ListCtrl_FailItem.SetItem(nCount, 1,LVIF_TEXT,  inItem,0,0,0,NULL );
	m_ListCtrl_FailItem.SetItem(nCount, 2,LVIF_TEXT,  inPath,0,0,0,NULL );
	UpdateData(FALSE);
}