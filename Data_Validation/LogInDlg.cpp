// LogInDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Data_Validation.h"
#include "LogInDlg.h"
#include "afxdialogex.h"


// LogInDlg ��ȭ �����Դϴ�.

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


// LogInDlg �޽��� ó�����Դϴ�.


void LogInDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnOK();
}


void LogInDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnCancel();
}
