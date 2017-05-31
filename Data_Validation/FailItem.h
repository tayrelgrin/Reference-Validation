#pragma once
#include "afxcmn.h"


// FailItem 대화 상자입니다.

class FailItem : public CDialogEx
{
	DECLARE_DYNAMIC(FailItem)

public:
	FailItem(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~FailItem();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_FAILITEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void AddFailItem(CString inItem, CString inPath);
public:
	CListCtrl m_ListCtrl_FailItem;
	
};
