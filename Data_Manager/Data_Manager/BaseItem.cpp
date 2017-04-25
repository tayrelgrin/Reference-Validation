// BaseItem.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Data_Manager.h"
#include "BaseItem.h"
#include "afxdialogex.h"


// BaseItem 대화 상자입니다.

IMPLEMENT_DYNAMIC(BaseItem, CDialogEx)

BaseItem::BaseItem(CWnd* pParent /*=NULL*/)
	: CDialogEx(BaseItem::IDD, pParent)
{

}

BaseItem::~BaseItem()
{
}

void BaseItem::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_ADDITEMBI, m_cButton_BI_Add);
	DDX_Control(pDX, IDC_BUTTON_DELETEITEMBI, m_cButton_BI_Remove);
	DDX_Control(pDX, IDC_BUTTON_BILS, m_cButton_BI_LoadSetting);
	DDX_Control(pDX, IDC_BUTTON_BIRL, m_cButton_BI_Reload);
	DDX_Control(pDX, IDC_COMBO1, m_cComboFiles);
}


BEGIN_MESSAGE_MAP(BaseItem, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_BIRL, &BaseItem::OnBnClickedButtonBirl)
END_MESSAGE_MAP()


// BaseItem 메시지 처리기입니다.


BOOL BaseItem::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_cButton_BI_Reload.LoadBitmaps(IDB_BITMAP_RELOAD,IDB_BITMAP_RELOADPUSH,NULL,NULL);
	m_cButton_BI_Reload.SizeToContent();

	m_cButton_BI_LoadSetting.LoadBitmaps(IDB_BITMAP_LOADSETTING,IDB_BITMAP_LOADSETTINGPUSH,NULL,NULL);
	m_cButton_BI_LoadSetting.SizeToContent();

	m_cButton_BI_Add.LoadBitmaps(IDB_BITMAP_RIGHT,IDB_BITMAP_RIGHTPUSH,NULL,NULL);
	m_cButton_BI_Add.SizeToContent();
	m_cButton_BI_Remove.LoadBitmaps(IDB_BITMAP_LEFT,IDB_BITMAP_LEFTPUSH,NULL,NULL);
	m_cButton_BI_Remove.SizeToContent();



	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void BaseItem::OnBnClickedButtonBirl()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	
}
