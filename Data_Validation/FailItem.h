#pragma once
#include "afxcmn.h"


// FailItem ��ȭ �����Դϴ�.

class FailItem : public CDialogEx
{
	DECLARE_DYNAMIC(FailItem)

public:
	FailItem(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~FailItem();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_FAILITEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void AddFailItem(CString inConfig,CString inTest, CString inFileName, CString inItem, CString inPath);
	void ClearItems();
	void SetRootPath(CString inData);
	bool SearchFailItem(CString inTargetConfig, CString inTargetTest);


	afx_msg void OnNMDblclkListFailitem(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListFailitem(NMHDR *pNMHDR, LRESULT *pResult);
public:
	CListCtrl m_ListCtrl_FailItem;
	CString m_strRootPath;
};
