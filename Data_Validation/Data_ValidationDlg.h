
// Data_ValidationDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "LogInDlg.h"
#include "DataController.h"

// CData_ValidationDlg 대화 상자
class CData_ValidationDlg : public CDialogEx
{
// 생성입니다.
public:
	CData_ValidationDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DATA_VALIDATION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
	CButton m_ButtonStart;
	CButton m_ButtonStop;
	CListCtrl m_ListCtrl_Main;
	afx_msg void OnBnClickedButtonRefSelect();

private:
	CString m_strOutPath;
	LogInDlg m_LogInDlg;
	DataController m_TotalData;
	std::vector<CString> m_vFileVector;
	std::vector<CString> m_vDirVector;
public:
	CTabCtrl m_TabCtrl_Main;
	afx_msg void OnBnClickedButtonLogin();
};
