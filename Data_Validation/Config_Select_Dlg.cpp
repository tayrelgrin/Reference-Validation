// Config_Select_Dlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Data_Validation.h"
#include "Config_Select_Dlg.h"
#include "afxdialogex.h"


// Config_Select_Dlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(Config_Select_Dlg, CDialogEx)

Config_Select_Dlg::Config_Select_Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Config_Select_Dlg::IDD, pParent)
{

}

Config_Select_Dlg::~Config_Select_Dlg()
{
}

void Config_Select_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Config_Select_Dlg, CDialogEx)
END_MESSAGE_MAP()


// Config_Select_Dlg �޽��� ó�����Դϴ�.


BOOL Config_Select_Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_strProject.Format("");
	m_strBuild.Format("");
	m_strConfig.Format("");
	m_strDOE.Format("");

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
