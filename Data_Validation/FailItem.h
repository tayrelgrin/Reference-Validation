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
	void AddFailItem(CString inItem, CString inPath);
public:
	CListCtrl m_ListCtrl_FailItem;
	
};
