
// Data_ValidationDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "LogInDlg.h"
#include "DataController.h"
#include "ListLogTab.h"
#include "FailItem.h"
#include "Config_Select_Dlg.h"
#include "ListLog.h"

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
	afx_msg void OnBnClickedButtonRefSelect();
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickTreeMain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnCustomdrawMainList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawTestList(NMHDR *pNMHDR, LRESULT *pResult);
public:
	void AddConfigAndTestToListControl(CString inConfig ,std::vector<CString> vTestName);
	void AddToTreeRefName(CString inData);
	BOOL CheckExistDataInTree(CString strRefName);	
	void CreateProgressBar(int nIndex, int nSubIndex);
	void AddToTreeTestName(std::vector<CString> vTestDirPath);
	void InitListCtrl();
	void AddReference(char* Pathname);
	bool GetTreeItemstatus(HTREEITEM hItem);
private:
	CString m_strOutPath;
	LogInDlg m_LogInDlg;
	ListLogTab m_ListLogDlg;
	FailItem m_FailItemDlg;
	ListLog* m_ListLog;
	DataController m_TotalData;
	CWnd* m_pwndShow;
	Config_Select_Dlg m_ConfigSelectDlg;
	CList<CompareResult*> m_ListDefferent;
public:
	CTabCtrl m_TabCtrl_Main;	
	CListCtrl m_ListCtrl_Main;
	CTreeCtrl m_TreeMain;
	virtual void PostNcDestroy();
	afx_msg void OnBnClickedButtonListlog();
	afx_msg void OnBnClickedButtonResultlog();
	CProgressCtrl m_Progressctrl;
	CListCtrl m_ListCtrl_Test;
	afx_msg void OnTvnSelchangedTreeMain(NMHDR *pNMHDR, LRESULT *pResult);
	CBitmapButton m_Button_Login;
	CBitmapButton m_Button_RefSel;
	CBitmapButton m_Button_Delete;
	CBitmapButton m_Button_Start;
	CBitmapButton m_Button_Stop;
	CStatic m_BaseRefText;
	CButton m_BasicCheckBox;

	CFont m_font;
	CBrush m_brush;
	CStatic m_FinalResult;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
//	afx_msg void OnTvnBegindragTreeMain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnNMCustomdrawTreeMain(NMHDR *pNMHDR, LRESULT *pResult);
};
