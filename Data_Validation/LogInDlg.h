#pragma once


// LogInDlg ��ȭ �����Դϴ�.

class LogInDlg : public CDialogEx
{
	DECLARE_DYNAMIC(LogInDlg)

public:
	LogInDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~LogInDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
