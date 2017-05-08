// SettingBaseInfo.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Data_Manager.h"
#include "SettingBaseInfo.h"
#include "afxdialogex.h"


// SettingBaseInfo 대화 상자입니다.

IMPLEMENT_DYNAMIC(SettingBaseInfo, CDialogEx)

SettingBaseInfo::SettingBaseInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(SettingBaseInfo::IDD, pParent)
{
	m_pwndShow = NULL;
}

SettingBaseInfo::~SettingBaseInfo()
{
}

void SettingBaseInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_cButton_Save);
	DDX_Control(pDX, IDC_BUTTON_EXIT, m_cButton_EXIT);
}


BEGIN_MESSAGE_MAP(SettingBaseInfo, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &SettingBaseInfo::OnBnClickedButtonSave)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &SettingBaseInfo::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &SettingBaseInfo::OnBnClickedButtonExit)
END_MESSAGE_MAP()


// SettingBaseInfo 메시지 처리기입니다.




BOOL SettingBaseInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_cButton_Save.LoadBitmaps(IDB_BITMAP_SAVE, IDB_BITMAP_SAVEPUSH, NULL, NULL);
	m_cButton_Save.SizeToContent();

	CString strTarget;

	strTarget.Format("%s%s","Setting : ", m_strSettingText );

	SetDlgItemText(IDC_STATIC_SETTING, strTarget);

	m_cButton_EXIT.LoadBitmaps(IDB_BITMAP_EXIT, IDB_BITMAP_EXITPUSH, NULL, NULL);
	m_cButton_EXIT.SizeToContent();
	m_Tab.InsertItem(1,_T("Base Info Items"));
// 	m_Tab.InsertItem(2,_T("Register"));
// 	m_Tab.InsertItem(3,_T("File List"));
 	
	m_bModifyFlag = false;

	CRect rect;

	m_Tab.GetClientRect(&rect);

	m_TabBaseInfo.m_pData = m_pData;

	m_TabBaseInfo.Create(IDD_DIALOG_BASEITEM, &m_Tab);

	//////////////////////////////////////////////////////////////////////////
	// Base Info Items Tab init

	AddFileNameToComboBox(m_TabBaseInfo.m_cComboFiles);
	
	CString strTemp = m_vConfigFileList[0];
	CString strTestName;

	AfxExtractSubString(strTestName, strTemp, 0, ':');
	m_TabBaseInfo.m_strFirstTestName = strTestName;

	m_TabBaseInfo.SetWindowPos(NULL, 5, 25, rect.Width()-10, rect.Height()-30, SWP_SHOWWINDOW | SWP_NOZORDER);
	m_pwndShow = &m_TabBaseInfo;
	//////////////////////////////////////////////////////////////////////////

	m_TabRegister.Create(IDD_DIALOG_REGISTER, &m_Tab);
	m_TabRegister.SetWindowPos(NULL, 5, 25, rect.Width()-10, rect.Height()-30, SWP_NOZORDER);

	m_TabFileList.m_pData = m_pData;
	m_TabFileList.m_vConfigFileList = m_vConfigFileList;		// Ref 파일 전부 사용
	m_TabFileList.m_vSettingFileList = m_vSettingFileList;		// 기본 세팅 파일 목록

	m_TabFileList.Create(IDD_DIALOG_FILELIST, &m_Tab);
	m_TabFileList.SetWindowPos(NULL, 5, 25, rect.Width()-10, rect.Height()-30, SWP_NOZORDER);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void SettingBaseInfo::AddFileNameToComboBox(CComboBox& incTarget)
{
	incTarget.InsertString(0, "ItemVersion");
	//incTarget.InsertString(1, "Reference");
}


void SettingBaseInfo::OnBnClickedButtonSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 각 List ctrl에 있는 데이터들 저장할 것
	if(m_TabBaseInfo.m_bModifyFlag)
	{
		m_TabBaseInfo.AddBaseInfoItemToList();
		m_TabBaseInfo.m_bModifyFlag = false;
		m_bModifyFlag = true;
	}
	if (m_TabFileList.m_bModifyFlag)
	{
		m_TabFileList.SaveFileListInListctrlToList();
		m_vSettingFileList = m_TabFileList.m_vSettingFileList;
		m_TabFileList.m_bModifyFlag = false;
		m_bModifyFlag = true;
	}
}


void SettingBaseInfo::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	if (m_pwndShow != NULL)
	{
		m_pwndShow->ShowWindow(SW_HIDE);
		m_pwndShow = NULL;
	}

	int nIndex = m_Tab.GetCurSel();

	switch (nIndex)
	{
	case 0:
		m_TabBaseInfo.ShowWindow(SW_SHOW);
		m_pwndShow = &m_TabBaseInfo;
		break;
// 	case 1:
// 		m_TabRegister.ShowWindow(SW_SHOW);
// 		m_pwndShow = &m_TabRegister;
// 		break;
// 	case 2:
// 		m_TabFileList.ShowWindow(SW_SHOW);
// 		m_pwndShow = &m_TabFileList;
// 		break;
	}
}


void SettingBaseInfo::OnBnClickedButtonExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(m_TabBaseInfo.m_bModifyFlag || m_TabFileList.m_bModifyFlag)
	{
		if(AfxMessageBox("Exit without saving?",MB_OKCANCEL) == true)
		{
			::SendMessage(this->m_hWnd, WM_CLOSE,NULL,NULL);
		}
	}
	else
		::SendMessage(this->m_hWnd, WM_CLOSE,NULL,NULL);
}
