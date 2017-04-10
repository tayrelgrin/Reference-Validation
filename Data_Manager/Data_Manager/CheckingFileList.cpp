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


	m_cButton_LoadSetting.LoadBitmaps(IDB_BITMAP_LOADSETTING,IDB_BITMAP_LOADSETTINGPUSH,NULL,NULL);
	m_cButton_LoadSetting.SizeToContent();
	
	m_cButton_Add.LoadBitmaps(IDB_BITMAP_RIGHT,IDB_BITMAP_RIGHTPUSH,NULL,NULL);
	m_cButton_Add.SizeToContent();
	m_cButton_Remove.LoadBitmaps(IDB_BITMAP_LEFT,IDB_BITMAP_LEFTPUSH,NULL,NULL);
	m_cButton_Remove.SizeToContent();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CheckingFileList::OnBnClickedButtonLsfl()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CheckingFileList::OnBnClickedButtonAdditem()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CheckingFileList::OnBnClickedButtonDeleteitem()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
