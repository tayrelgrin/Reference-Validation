// LogInDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Data_Validation.h"
#include "LogInDlg.h"
#include "afxdialogex.h"


// LogInDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(LogInDlg, CDialogEx)

LogInDlg::LogInDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(LogInDlg::IDD, pParent)
{

}

LogInDlg::~LogInDlg()
{
}

void LogInDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(LogInDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &LogInDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &LogInDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// LogInDlg 메시지 처리기입니다.


void LogInDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


void LogInDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}
