// CheckingFileList.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Data_Manager.h"
#include "CheckingFileList.h"
#include "afxdialogex.h"


// CheckingFileList 대화 상자입니다.

IMPLEMENT_DYNAMIC(CheckingFileList, CDialogEx)

CheckingFileList::CheckingFileList(CWnd* pParent /*=NULL*/)
	: CDialogEx(CheckingFileList::IDD, pParent)
{

}

CheckingFileList::~CheckingFileList()
{
}

void CheckingFileList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_LSFL, m_cButton_LoadSetting);
	DDX_Control(pDX, IDC_BUTTON_RLFL, m_cButton_Reload);
	DDX_Control(pDX, IDC_BUTTON_ADDITEM, m_cButton_Add);
	DDX_Control(pDX, IDC_BUTTON_DELETEITEM, m_cButton_Remove);
	DDX_Control(pDX, IDC_TREE2, m_treectrlFileList);
	DDX_Control(pDX, IDC_LIST6, m_ListctrlFileList);
}


BEGIN_MESSAGE_MAP(CheckingFileList, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_LSFL, &CheckingFileList::OnBnClickedButtonLsfl)
	ON_BN_CLICKED(IDC_BUTTON_ADDITEM, &CheckingFileList::OnBnClickedButtonAdditem)
	ON_BN_CLICKED(IDC_BUTTON_DELETEITEM, &CheckingFileList::OnBnClickedButtonDeleteitem)
END_MESSAGE_MAP()


// CheckingFileList 메시지 처리기입니다.


BOOL CheckingFileList::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_cButton_Reload.LoadBitmaps(IDB_BITMAP_RELOAD,IDB_BITMAP_RELOADPUSH,NULL,NULL);
	m_cButton_Reload.SizeToContent();

	m_cButton_LoadSetting.LoadBitmaps(IDB_BITMAP_LOADSETTING,IDB_BITMAP_LOADSETTINGPUSH,NULL,NULL);
	m_cButton_LoadSetting.SizeToContent();

	AddFileNameToTreeView(m_treectrlFileList);
	

	m_cButton_LoadSetting.LoadBitmaps(IDB_BITMAP_LOADSETTING,IDB_BITMAP_LOADSETTINGPUSH,NULL,NULL);
	m_cButton_LoadSetting.SizeToContent();
	
	m_cButton_Add.LoadBitmaps(IDB_BITMAP_RIGHT,IDB_BITMAP_RIGHTPUSH,NULL,NULL);
	m_cButton_Add.SizeToContent();
	m_cButton_Remove.LoadBitmaps(IDB_BITMAP_LEFT,IDB_BITMAP_LEFTPUSH,NULL,NULL);
	m_cButton_Remove.SizeToContent();


	m_ListctrlFileList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES | LVCFMT_CENTER | LVS_EDITLABELS);

	m_ListctrlFileList.InsertColumn(0, _T("Test"), LVCFMT_CENTER, 110,  -1);
	m_ListctrlFileList.InsertColumn(1, _T("File"), LVCFMT_CENTER, 170, -1);
	AddFileNameToListview();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CheckingFileList::AddFileNameToTreeView(CTreeCtrl& incTarget)
{
	CString strTEMPs;
	strTEMPs.Empty();

	HTREEITEM h_Root;
	HTREEITEM h_Child;
	HTREEITEM h_2Child;

	for(int i = 0; i < m_vConfigFileList.size(); i++)
	{
		CString strOriFilePath = m_vConfigFileList[i];
		CString strDir, strTest, strFile;

		if(strOriFilePath.Find('\\') == -1 && strOriFilePath=="")
		{
			AfxExtractSubString(strTest, strOriFilePath, 0, ':');
			AfxExtractSubString(strFile, strOriFilePath, 1, ':');
		}
		else
		{
			AfxExtractSubString(strTEMPs, strOriFilePath, 1, '\\');
			AfxExtractSubString(strTest, strTEMPs, 0, ':');
			AfxExtractSubString(strFile, strTEMPs, 1, ':');

			if(strTEMPs == "")	// 확인하자
			{
				AfxExtractSubString(strTest, strOriFilePath, 2, ':');
				if(strTest != "")
				{
					AfxExtractSubString(strDir, strOriFilePath, 0, ':');
					AfxExtractSubString(strTest, strOriFilePath, 1, ':');
					strTest = strDir + "-" + strTest;
					AfxExtractSubString(strFile, strOriFilePath, 2, ':');
				}
				else
				{
					AfxExtractSubString(strTest, strOriFilePath, 0, ':');
					AfxExtractSubString(strFile, strOriFilePath, 1, ':');
				}
			}
		}
		CString strCompare;
		bool bResult = false;

		if(incTarget.GetCount() > 0 && i != 0)	
			strCompare = incTarget.GetItemText(h_Child);	// Serach in h_Child level in tree

		if(strTest != strCompare)
			h_Child = incTarget.InsertItem(strTest, TVI_ROOT, TVI_LAST);

		h_2Child = incTarget.InsertItem(strFile, h_Child, NULL);
	}
}

void CheckingFileList::AddFileNameToListview()
{
	m_ListctrlFileList.DeleteAllItems(); 
	CString strTEMPs;

	for(int i = 0; i < m_vSettingFileList.size(); i++)
	{
		CString strOriFilePath = m_vSettingFileList[i];
		CString strDir, strTest, strFile;
		if(strOriFilePath.Find('\\') == -1 && strOriFilePath=="")
		{
			AfxExtractSubString(strTest, strOriFilePath, 0, ':');
			AfxExtractSubString(strFile, strOriFilePath, 1, ':');
		}
		else
		{
			AfxExtractSubString(strTEMPs, strOriFilePath, 1, '\\');
			AfxExtractSubString(strTest, strTEMPs, 0, ':');
			AfxExtractSubString(strFile, strTEMPs, 1, ':');

			if(strTEMPs == "")	// 확인하자
			{
				AfxExtractSubString(strTest, strOriFilePath, 2, ':');
				if(strTest != "")
				{
					AfxExtractSubString(strDir, strOriFilePath, 0, ':');
					AfxExtractSubString(strTest, strOriFilePath, 1, ':');
					strTest = strDir + "-" + strTest;
					AfxExtractSubString(strFile, strOriFilePath, 2, ':');
				}
				else
				{
					AfxExtractSubString(strTest, strOriFilePath, 0, ':');
					AfxExtractSubString(strFile, strOriFilePath, 1, ':');
				}
			}
		}
		CString strCompare;
		bool bResult = false;

		int nIndex;
		CString strTempTest;
		CString strTempFile;

		for (nIndex = 0; m_ListctrlFileList.GetItemCount() > nIndex; nIndex++ )
		{
			strTempTest = m_ListctrlFileList.GetItemText(nIndex,0);
			strTempFile = m_ListctrlFileList.GetItemText(nIndex,1);
			if(strTempFile == strFile && strTempTest == strTest)
			{
				bResult = true;
				break;
			}
		}

		if(!bResult)
		{
			m_ListctrlFileList.InsertItem(nIndex, strTest);
			m_ListctrlFileList.SetItem(nIndex, 1,LVIF_TEXT,  strFile ,0,0,0,NULL);
		}
	}
	
}

void CheckingFileList::OnBnClickedButtonLsfl()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 세팅 파일 읽어오기
}


void CheckingFileList::OnBnClickedButtonAdditem()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// tree에서 체크 된 아이템들 가지고 오기
	
	UINT uCount = m_treectrlFileList.GetVisibleCount();
	HTREEITEM hItem = m_treectrlFileList.GetFirstVisibleItem();

	// Toggle the check state of all the visible items.
	for (UINT i = 0; i < uCount; i++)
	{
		ASSERT(hItem != NULL);
		m_treectrlFileList.SetCheck(hItem, !m_treectrlFileList.GetCheck(hItem));
		hItem = m_treectrlFileList.GetNextVisibleItem(hItem);
	}
	
	// tree에 체크 해제하기
	

	// listctrl에 아이템 추가하기
}


void CheckingFileList::OnBnClickedButtonDeleteitem()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// listctrl에서 아이템 삭제
}
