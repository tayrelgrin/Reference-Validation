// Config_Select_Dlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Data_Validation.h"
#include "Config_Select_Dlg.h"
#include "afxdialogex.h"


// Config_Select_Dlg 대화 상자입니다.

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


// Config_Select_Dlg 메시지 처리기입니다.


BOOL Config_Select_Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_strProject.Format("");
	m_strBuild.Format("");
	m_strConfig.Format("");
	m_strDOE.Format("");

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
