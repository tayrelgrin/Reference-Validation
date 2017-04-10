// Register.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Data_Manager.h"
#include "Register.h"
#include "afxdialogex.h"


// Register 대화 상자입니다.

IMPLEMENT_DYNAMIC(Register, CDialogEx)

Register::Register(CWnd* pParent /*=NULL*/)
	: CDialogEx(Register::IDD, pParent)
{

}

Register::~Register()
{
}

void Register::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST6, m_listRegister);
}


BEGIN_MESSAGE_MAP(Register, CDialogEx)
END_MESSAGE_MAP()


// Register 메시지 처리기입니다.


BOOL Register::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	// init List
	m_listRegister.DeleteAllItems();

	// List style
	m_listRegister.SetExtendedStyle(LVS_EX_GRIDLINES);


	m_listRegister.InsertColumn(0, _T("Item"),		LVCFMT_CENTER, 40,  -1);
	m_listRegister.InsertColumn(1, _T("Value"),		LVCFMT_CENTER, 80, -1);
	m_listRegister.InsertColumn(2, _T("Model"),		LVCFMT_CENTER, 100, -1);
	m_listRegister.InsertColumn(3, _T("Rev."),		LVCFMT_CENTER, 120, -1);
	m_listRegister.InsertColumn(4, _T("History"),	LVCFMT_CENTER, 120, -1);
	m_listRegister.InsertColumn(5, _T("File Path"),	LVCFMT_CENTER, 160, -1);
	m_listRegister.InsertColumn(6, _T("Menu"),		LVCFMT_CENTER, 70, -1);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
