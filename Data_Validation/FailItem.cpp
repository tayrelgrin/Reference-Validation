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
	m_strRootPath.Format(_T(""));
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
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_FAILITEM, &FailItem::OnNMDblclkListFailitem)
	ON_NOTIFY(NM_CLICK, IDC_LIST_FAILITEM, &FailItem::OnNMClickListFailitem)
END_MESSAGE_MAP()


// FailItem 메시지 처리기입니다.


BOOL FailItem::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	//////////////////////////////////////////////////////////////////////////
	m_ListCtrl_FailItem.SetExtendedStyle(LVS_EX_GRIDLINES | LVCFMT_LEFT | LVS_EX_FULLROWSELECT );

	m_ListCtrl_FailItem.InsertColumn(0, _T(""),				LVCFMT_CENTER, 0,  -1);
	m_ListCtrl_FailItem.InsertColumn(1, _T("Config"),		LVCFMT_CENTER, 100, -1);
	m_ListCtrl_FailItem.InsertColumn(2, _T("Test"),			LVCFMT_CENTER, 100, -1);
	m_ListCtrl_FailItem.InsertColumn(3, _T("File Name"),	LVCFMT_CENTER, 300, -1);
	m_ListCtrl_FailItem.InsertColumn(4, _T("Item"),			LVCFMT_CENTER, 150, -1);	
	m_ListCtrl_FailItem.InsertColumn(5, _T("Execute"),		LVCFMT_CENTER, 50, -1);
	m_ListCtrl_FailItem.InsertColumn(6, _T("Execute"),		LVCFMT_CENTER,  0, -1);
	
	////////////////////////////////////////////////////////////////////////// 

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void FailItem::AddFailItem(CString inConfig,CString inTest, CString inFileName, CString inItem, CString inPath)
{
	int nCount = m_ListCtrl_FailItem.GetItemCount();
	int nFileIndex = inPath.ReverseFind('\\');
	CString strTemp = inPath.Left(nFileIndex);
	nFileIndex = strTemp.ReverseFind('\\');
	inPath = inPath.Mid(nFileIndex+1);

	UpdateData(TRUE);
	m_ListCtrl_FailItem.InsertItem(nCount, _T(""));
	m_ListCtrl_FailItem.SetItem(nCount, 1,LVIF_TEXT, inConfig,	0,0,0,NULL );
	m_ListCtrl_FailItem.SetItem(nCount, 2,LVIF_TEXT, inTest,	0,0,0,NULL );
	m_ListCtrl_FailItem.SetItem(nCount, 3,LVIF_TEXT, inFileName,0,0,0,NULL );
	m_ListCtrl_FailItem.SetItem(nCount, 4,LVIF_TEXT, inItem,	0,0,0,NULL );	
	m_ListCtrl_FailItem.SetItem(nCount, 5,LVIF_TEXT, "▶",	0,0,0,NULL );
	m_ListCtrl_FailItem.SetItem(nCount, 6,LVIF_TEXT, inPath,	0,0,0,NULL );
	UpdateData(FALSE);
}

void FailItem::OnNMDblclkListFailitem(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 클릭한 위치의 파일 이름 가져오기

	//int nIndex = pNMItemActivate->iItem; // 클릭한 아이템의 인덱스 얻어옴
	NM_LISTVIEW* pNMView = (NM_LISTVIEW*)pNMHDR;
	int nIndex = pNMView->iItem;
	int nSubIndex = pNMItemActivate->iSubItem;
	CString strSelectFilePath;
	CString strTemp;
	strSelectFilePath.Format(_T(""));
	strTemp = m_ListCtrl_FailItem.GetItemText(nIndex, 6);

	strSelectFilePath.Format("%s\\%s",m_strRootPath, strTemp);
	// 해당 파일 열기
	if (strSelectFilePath != _T("") && nSubIndex == 5)
	{
		ShellExecute(NULL, _T("open"), strSelectFilePath, NULL, NULL, SW_SHOW);
	}

	*pResult = 0;
}


void FailItem::OnNMClickListFailitem(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 해당 아이템으로 이동

	
	*pResult = 0;
}


void FailItem::ClearItems()
{
	m_ListCtrl_FailItem.DeleteAllItems();
}

void FailItem::SetRootPath(CString inData)
{
	m_strRootPath = inData;
}

bool FailItem::SearchFailItem(CString inTargetConfig, CString inTargetTest)
{
	bool bResult = false;

	for (int i= 0; i < m_ListCtrl_FailItem.GetItemCount() ; i++)
	{
		if (inTargetConfig.Find(m_ListCtrl_FailItem.GetItemText(i,1)) != -1 && m_ListCtrl_FailItem.GetItemText(i,2) == inTargetTest)
		{
			bResult = true;
			break;
		}
	}

	return bResult;
}