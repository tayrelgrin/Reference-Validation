
// Data_ValidationDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "LogInDlg.h"
#include "DataController.h"

// CData_ValidationDlg ��ȭ ����
class CData_ValidationDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CData_ValidationDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DATA_VALIDATION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
