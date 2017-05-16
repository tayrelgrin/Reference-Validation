#pragma once


// LogInDlg 대화 상자입니다.

class LogInDlg : public CDialogEx
{
	DECLARE_DYNAMIC(LogInDlg)

public:
	LogInDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~LogInDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
