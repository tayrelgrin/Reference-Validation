// Register.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Data_Manager.h"
#include "Register.h"
#include "afxdialogex.h"


// Register ��ȭ �����Դϴ�.

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


// Register �޽��� ó�����Դϴ�.


BOOL Register::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

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
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
